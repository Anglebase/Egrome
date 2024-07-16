#include<queue>
#include<mutex>

/**
 * @brief 缓冲区溢出策略指示符
 */
enum OverflowPolicy {
    /**
     * @brief 忽略溢出数据
     */
    ignore,
    /**
     * @brief 等待缓冲区空出空间再写入数据
     */
    wait,
};
/**
 * @brief 通道模板类
 * @tparam T 通道所传递的数据类型
 * @details 它是线程安全的，可以用于线程间的异步通信
 */
template<typename T>
class Channel {
private:
    std::queue<T> queue_;
    std::mutex mut;
    bool sign = true;
    std::size_t bf_size;
    OverflowPolicy policy{ wait };

public:
    /**
     * @brief 构造函数
     * @param buff_size 缓冲区大小，默认为0，表示不限制大小
     */
    Channel(std::size_t buff_size = 0) :bf_size(buff_size) {}
    Channel(const Channel<T>&) = delete;
    Channel(Channel<T>&&) = delete;
    const Channel<T>& operator=(const Channel<T>&) = delete;
    const Channel<T>& operator=(Channel<T>&&) = delete;

    /**
     * @brief 关闭通道
     * @details 关闭后，队列中未读取的数据将会被丢弃
     */
    void close() {
        this->sign = false;
        std::queue<T> temp;
        this->queue_.swap(temp);
    }
    
    /**
     * @brief 打开通道
     * @details 打开后，通道将重新开始工作
     */
    void open() {
        this->sign = true;
    }

    /**
     * @brief 设置缓冲区溢出策略
     * @param policy 策略，默认为wait，表示等待缓冲区被读取后再写入新数据
     * @details 当缓冲区满时，如果策略为ignore，则丢弃新数据；如果策略为wait，则等待缓冲区空出空间再写入数据
     */
    void setPolicy(OverflowPolicy policy) { this->policy = policy; }

    template<typename U>
    friend bool operator << (Channel<U>& channel, const U& var);
    template<typename U>
    friend bool operator << (U& var, Channel<U>& channel);
    template<typename U>
    friend bool operator >> (const U& var, Channel<U>& channel);
    template<typename U>
    friend bool operator >> (Channel<U>& channel, U& var);
};

/**
 * @brief 从通道读取数据
 * @tparam U 要读取的数据类型
 * @param var 要读取的变量
 * @param channel 要读取的通道
 * @return 若成功读取则返回true，否则返回false
 * @details 若通道已关闭，则直接返回false；若缓冲区为空，则会等待缓冲区有数据后再读取
 * @details 运算符中的箭头指向表示数据传递的方向
 * @example 示例：
 * @code
 * Channel<int> ch(10); // 创建缓冲区大小为10的通道
 * ...
 * ch << 10; // 向通道写入数据
 * 20 >> ch; // 向通道写入数据
 * ...
 * int var;
 * ch >> var; // 从通道读取数据，写入通道的数据在获取时是以队列顺序获取的
 * std::cout << var << std::endl; // 输出：10
 * var << ch; // 从通道读取数据
 * std::cout << var << std::endl; // 输出：20
 * ...
 * ch.close(); // 关闭通道
 *
 * @endcode
 */
template<typename U>
bool operator<<(U& var, Channel<U>& channel) {
    if (!channel.sign)
        return false;
    while (channel.queue_.empty()) {
        if (!channel.sign)
            return false;
    }
    channel.mut.lock();
    var = channel.queue_.front();
    channel.queue_.pop();
    channel.mut.unlock();
    return true;
}

/**
 * @brief 从通道读取数据
 * @tparam U 要读取的数据类型
 * @param var 要读取的变量
 * @param channel 要读取的通道
 * @return 若成功读取则返回true，否则返回false
 * @details 若通道已关闭，则直接返回false；若缓冲区为空，则会等待缓冲区有数据后再读取
 */
template<typename U>
bool operator>>(Channel<U>& channel, U& var) {
    return var << channel;
}

/**
 * @brief 向通道写入数据
 * @tparam U 要写入的数据类型
 * @param channel 要写入的通道
 * @param var 要写入的变量
 * @return 若成功写入则返回true，否则返回false
 * @details 若通道已关闭，则直接返回false；
 * @details 若缓冲区满且策略为ignore，则丢弃新数据；
 * @details 若缓冲区满且策略为wait，则等待缓冲区空出空间再写入数据
 */
template<typename U>
bool operator<<(Channel<U>& channel, const U& var) {
    if (!channel.sign)
        return false;
    if (channel.bf_size > 0) {
        if (channel.policy == wait)
            while (channel.queue_.size() > channel.bf_size) {
                if (!channel.sign)
                    return false;
            }
        else if (channel.queue_.size() >= channel.bf_size)
            return true;
    }
    channel.mut.lock();
    channel.queue_.push(var);
    channel.mut.unlock();
    return true;
}

/**
 * @brief 向通道写入数据
 * @tparam U 要写入的数据类型
 * @param channel 要写入的通道
 * @param var 要写入的变量
 * @return 若成功写入则返回true，否则返回false
 * @details 若通道已关闭，则直接返回false；
 * @details 若缓冲区满且策略为ignore，则丢弃新数据；
 * @details 若缓冲区满且策略为wait，则等待缓冲区空出空间再写入数据
 */
template<typename U>
bool operator>>(const U& var, Channel<U>& channel) {
    return channel << var;
}