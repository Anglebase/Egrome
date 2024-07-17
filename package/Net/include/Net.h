#pragma once

#include<string>
#include<tuple>

using byte = unsigned char;
enum NetType {
    TCP,
    UDP
};
template <NetType type> class Client;
template <NetType type> class Server;

/**
 * @brief 数据包
 */
class Data {
    template <NetType type> friend class Client;
    template <NetType type> friend class Server;
    int len = 0;
    byte* data = nullptr;

public:
    /**
     * @brief 构造函数
     * @param length 数据包长度
     */
    Data(int length = 0);
    Data(const Data& data);
    Data(Data&& data);
    const Data& operator = (const Data& data);
    const Data& operator = (Data&& data);
    ~Data();

    /**
     * @brief 读取数据
     * @param start 开始位置
     * @param size 读取大小
     * @param out 输出缓冲区
     * @return 实际读取大小
     */
    int read(int start, int size, byte* out);
    /**
     * @brief 写入数据
     * @param start 开始位置
     * @param size 写入大小
     * @param in 输入缓冲区
     * @return 实际写入大小
     */
    int write(int start, int size, const byte* in);
    /**
     * @brief 获取数据包长度
     * @return 数据包长度
     */
    int size() const;

    /**
     * @brief 读取数据包中的数据
     * @tparam T 数据类型
     * @param start 开始位置
     * @return 数据
     */
    template<typename T>
    T read(int start) {
        T result;
        this->read(start, sizeof(T), (byte*)&result);
        return result;
    }
    /**
     * @brief 读取数据包中的字符串
     * @param start 开始位置
     * @param size 读取最大长度
     * @return 字符串
     */
    std::string read(int start, int size) {
        char* result = new char[size];
        this->read(start, size, (byte*)result);
        return std::string(result);
    }
    /**
     * @brief 向数据包中写入数据
     * @tparam N 数据起始位置
     * @tparam T 数据类型
     * @param in 数据
     */
    template<std::size_t N, typename T>
    void write(const T& in) {
        this->write(N, sizeof(T), (const byte*)&in);
    }
    /**
     * @brief 向数据包中写入字符串
     * @tparam N 数据起始位置
     * @param in 字符串
     */
    template<std::size_t N>
    void write(const std::string& in) {
        this->write(N, in.length(), (const byte*)in.data());
    }
};

/**
 * @brief TCP服务端类
 */
template<>
class Server<TCP> {
    unsigned int* sock;
    int port;
    std::string ip;

public:
    Server();
    ~Server();

    /**
     * @brief 绑定端口
     * @param port 端口号
     * @param ip IP地址
     * @return 是否绑定成功
     * @note 如果ip为空，则绑定地址为“0.0.0.0”
     */
    bool bind(int port, const char* ip = nullptr);
    /**
     * @brief 监听连接
     * @param backlog 最大连接数(半连接池大小)
     * @return 是否监听成功
     */
    bool listen(int backlog);
    /**
     * @brief 从连接池中接收连接
     * @return 客户端对象
     */
    Client<TCP> accept();

    /**
     * @brief 关闭连接
     */
    void close();

    friend std::ostream& operator << (std::ostream& os, const Server<TCP>& server);
};

template<>
class Client<TCP> {
    friend class Server<TCP>;
    unsigned int* sock;

    bool onlyRS = false;
    std::string ip;
    int port;

    Client(int);
public:
    Client();
    ~Client();

    /**
     * @brief 连接到服务器
     * @param ip IP地址
     * @param port 端口号
     * @return 是否连接成功
     */
    bool connect(const char* ip, int port);
    /**
     * @brief 关闭连接
     */
    void close();

    /**
     * @brief 发送数据
     * @param data 数据包
     * @return 实际发送大小
     */
    int send(const Data& data);
    /**
     * @brief 接收数据
     * @param data 数据包
     * @return 实际接收大小
     */
    int recv(Data& data);

    /**
     * @brief 若为无效连接，返回false，否则返回true
     */
    operator bool() const;
    bool operator ! () const;

    friend std::ostream& operator << (std::ostream& os, const Client<TCP>& client);
};

// C++ IO流操作符重载
// 使用 >> 接收数据，使用 << 发送数据
// 若没有数据可被接收，则会阻塞
Client<TCP>& operator << (Client<TCP>& client, const Data& data);
Client<TCP>& operator >> (Client<TCP>& client, Data& data);
Client<TCP>& operator << (Client<TCP>& client, const std::string& str);
Client<TCP>& operator >> (Client<TCP>& client, std::string& str);
Client<TCP>& operator << (Client<TCP>& client, char str);
Client<TCP>& operator >> (Client<TCP>& client, char& str);
Client<TCP>& operator << (Client<TCP>& client, int num);
Client<TCP>& operator >> (Client<TCP>& client, int& num);
Client<TCP>& operator << (Client<TCP>& client, long long num);
Client<TCP>& operator >> (Client<TCP>& client, long long& num);
Client<TCP>& operator << (Client<TCP>& client, unsigned int num);
Client<TCP>& operator >> (Client<TCP>& client, unsigned int& num);
Client<TCP>& operator << (Client<TCP>& client, unsigned long long num);
Client<TCP>& operator >> (Client<TCP>& client, unsigned long long& num);
Client<TCP>& operator << (Client<TCP>& client, float num);
Client<TCP>& operator >> (Client<TCP>& client, float& num);
Client<TCP>& operator << (Client<TCP>& client, double num);
Client<TCP>& operator >> (Client<TCP>& client, double& num);
Client<TCP>& operator << (Client<TCP>& client, long double num);
Client<TCP>& operator >> (Client<TCP>& client, long double& num);

enum MsgType {
    IP,
    Port
};

/**
 * @brief UDP服务端类
 */
template<>
class Server<UDP> {
    unsigned int* sock;
    std::string ip;
    int port;

public:
    Server();
    ~Server();

    /**
     * @brief 绑定端口
     * @param port 端口号
     * @param ip IP地址
     * @return 是否绑定成功
     * @note 如果ip为空，则绑定地址为“0.0.0.0”
     */
    bool bind(int port, const char* ip = nullptr);

    /**
     * @brief 接收数据
     * @param data 数据包
     * @return 数据来源地址
     */
    std::tuple<std::string, int> recvfrom(Data& data);
    /**
     * @brief 发送数据
     * @param data 数据包
     * @param addr 数据目标地址
     * @return 实际发送大小
     */
    int sendto(const Data& data, std::tuple<std::string, int> addr);
};

/**
 * @brief UDP客户端类
 */
template<>
class Client<UDP> {
    unsigned int* sock;

public:
    Client();
    ~Client();

    /**
     * @brief 接收数据
     * @param data 数据包
     * @return 数据来源地址
     */
    std::tuple<std::string, int> recvfrom(Data& data);
    /**
     * @brief 发送数据
     * @param data 数据包
     * @param addr 数据目标地址
     * @return 实际发送大小
     */
    int sendto(const Data& data, std::tuple<std::string, int> addr);
};