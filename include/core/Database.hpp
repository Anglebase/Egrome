#pragma once

// 此功能需要C++17或更高版本
#if __cplusplus > 201700L

#include<tuple>
#include<vector>
#include<string>
#include<cstring>

template<typename T>
class Table;
/**
 * @brief 本地数据库类，支持千万级数据量的本地数据库
 * @details 数据库的存储格式为：
 * 1. 32字节的头部信息：
 *    - 8字节：文件长度信息
 *    - 8字节：一行数据长度
 *    - 8字节：表的数据量
 *    - 8字节：保留字节
 * 2. 若干行数据，每行数据长度为lenth字节，数据格式为用户自定义读写函数确定
 * @tparam ...Args 指定表的字段类型
 * @note 此功能需要C++17或更高版本
 */
template<typename...Args>
class Table<std::tuple<Args...>> {
    using _LINE_type = std::tuple<Args...>;
    const std::size_t header_lenth = 32ULL;

private:
    std::vector<_LINE_type> database; // 表的数据
    std::vector<bool> sign;
    std::size_t size_;           // 此表的数据量
    std::size_t count_;          // 已删除的数据量

protected:
    /**
     * @brief 行数据的长度，默认为对Args中所有类型的sizeof求和
     * @warning 若行数据中存在复杂类型(例如std::string, T*等)，则必须在子类中指定行数据的长度，否则无法正确读写数据
     */
    std::size_t lenth = (sizeof(Args) + ... + 0ULL);           // 一条数据的长度

    /**
     * @brief 读取数据的格式化函数
     * @param input 从文件中读取的一行数据
     * @param data 进行类型格式化后的结果
     * @details 在子类中，必须实现此函数
     */
    virtual void readLine(const void* input, _LINE_type& data) = 0;
    /**
     * @brief 写入数据的格式化函数
     * @param output 要写入数据库的一行数据
     * @param data 将要写入数据库的具有类型的数据
     * @details 在子类中，必须实现此函数
     */
    virtual void writeLine(void* output, const _LINE_type& data) = 0;
    /**
     * @brief 打印一行数据的格式化函数
     * @param data 要打印的一行数据
     * @details 在子类中，必须实现此函数
     */
    virtual void printLine(const _LINE_type& data) const = 0;

public:
    /**
     * @brief 从文件加载数据库到内存
     * @param database_path 文件路径
     * @return 若加载失败，返回false；否则返回true
     */
    bool loadDatabase(const std::string_view& database_path) {
        std::FILE* input = std::fopen(database_path.data(), "r");
        if (!input) return false;

        // 读取文件长度信息
        std::size_t filelenth;
        std::fread(&filelenth, sizeof(std::size_t), 1, input);

        // 读取一行数据长度以及表的数据量
        std::fread(&this->lenth, sizeof(std::size_t), 1, input);
        std::fread(&this->size_, sizeof(std::size_t), 1, input);

        if (filelenth != this->lenth * this->size_ + this->header_lenth) return false;
        this->sign = std::vector<bool>(this->size_, true);

        // 读取数据
        std::fseek(input, this->header_lenth, SEEK_SET);
        void* data = (void*)new char[this->lenth];
        _LINE_type format_data;
        for (int count = 0; count < this->size_; ++count) {
            std::fseek(input, this->header_lenth + count * this->lenth, SEEK_SET);
            std::fread(data, this->lenth, 1, input);
            this->readLine(data, format_data);
            this->database.push_back(format_data);
        }

        delete[](char*)data;
        data = nullptr;
        std::fclose(input);
        return true;
    }
    /**
     * @brief 将内存中的数据保存至文件
     * @param database_path 文件路径
     * @param lenth 一行数据的长度(以字节计)，默认为对Args中所有类型的sizeof求和
     * @return 若保存失败，返回false；否则返回true
     */
    bool saveDatabase(const std::string_view& database_path) {
        std::FILE* output = std::fopen(database_path.data(), "w");
        if (!output) return false;

        char header[this->header_lenth];
        std::memset(header, 0, sizeof(header));

        this->size_ = this->database.size();
        std::size_t filelenth = this->size_ * lenth + this->header_lenth;

        std::memcpy(header, &filelenth, sizeof(std::size_t));
        std::memcpy(header + sizeof(std::size_t), &lenth, sizeof(std::size_t));
        std::memcpy(header + sizeof(std::size_t) * 2, &this->size_, sizeof(std::size_t));

        fwrite(header, sizeof(header), 1, output);
        void* data = (void*)new char[lenth];
        int count = -1;
        for (const auto& linedata : this->database) {
            ++count;
            if (!this->sign[count])
                continue;

            this->writeLine(data, linedata);
            std::fwrite(data, lenth, 1, output);
        }

        delete[](char*)data;
        data = nullptr;
        std::fclose(output);
        return true;
    }
    /**
     * @brief 向数据库中添加一行数据
     * @param line 要添加的数据
     * @details 时间复杂度:O(1)
     */
    void append(const _LINE_type& line) {
        this->database.push_back(line);
        this->sign.push_back(true);
    }
    /**
     * @brief 向数据库中移动一行数据
     * @param line 要移动的数据
     * @details 时间复杂度:O(1)
     */
    void append(_LINE_type&& line) {
        this->database.push_back(line);
        this->sign.push_back(true);
    }
    /**
     * @brief 将数据库中指定位置的数据设置为删除状态
     * @param index 索引
     * @details 调用此函数后，数据库中对应位置的数据将被标记为删除状态，被标记的数据不会再被保存至文件中
     * @details 时间复杂度:O(1)
     */
    void revoke(std::size_t index) { this->sign[index] = false; this->count_++; }
    /**
     * @brief 获取数据库中指定位置的数据
     * @param index 索引
     * @return 数据库中指定位置的数据
     * @details 时间复杂度:O(1)
     */
    _LINE_type& getline(std::size_t index) { return this->database[index]; }

    /**
     * @brief 查找并返回所有满足condition的行
     * @tparam N 要比较的字段的索引
     * @tparam Func 条件函数类型
     * @param condition 条件函数
     * @return 所有满足condition的行数据和索引，即满足 condition(std::get<N>(line))==true
     * @details 时间复杂度:O(n)
     */
    template<std::size_t N, class Func>
    std::vector<std::pair<const _LINE_type*, std::size_t>> find_index_if(Func condition) {
        std::vector<std::pair<const _LINE_type*, std::size_t>> results;
        std::size_t index = 0;
        for (const auto& line : this->database) {
            if (condition(std::get<N>(line)))
                results.push_back({ &line,index });
            ++index;
        }
        return results;
    }
    /**
     * @brief 查找并返回所有满足condition的行
     * @tparam N 要比较的字段的索引
     * @tparam Func 条件函数类型
     * @param condition 条件函数
     * @return 所有满足condition的行数据，即满足 condition(std::get<N>(line))==true
     * @details 时间复杂度:O(n)
     */
    template<std::size_t N, class Func>
    std::vector<const _LINE_type*> find_if(Func condition) {
        std::vector<const _LINE_type*> results;
        std::size_t index = 0;
        for (const auto& line : this->database) {
            if (condition(std::get<N>(line)))
                results.push_back(&line);
            ++index;
        }
        return results;
    }
    /**
     * @brief 查找所有满足condition的行的数量
     * @tparam N 要比较的字段的索引
     * @tparam Func 条件函数类型
     * @param condition 条件函数
     * @return 所有满足condition的行的数量
     * @details 时间复杂度:O(n)
     */
    template<std::size_t N, class Func>
    std::size_t count_if(Func condition) {
        std::size_t count = 0;
        for (const auto& line : this->database) {
            if (condition(std::get<N>(line)))
                ++count;
        }
        return count;
    }
    /**
     * @brief 查找所有满足condition的行并标记为删除状态
     * @tparam N 要比较的字段的索引
     * @tparam Func 条件函数类型
     * @param condition 条件函数
     * @return 所有满足condition的行的数量
     * @details 时间复杂度:O(n)
     */
    template<std::size_t N, class Func>
    std::size_t revoke_if(Func condition) {
        std::size_t index = 0, count = 0;
        for (const auto& line : this->database) {
            if (condition(std::get<N>(line))) {
                this->revoke(index);
                ++count;
                ++this->count_;
            }
            ++index;
        }
        return count;
    }
    /**
     * @brief 打印数据库中的前100条数据
     */
    void print() const {
        for (int i = 0; i < 100 && i < this->database.size(); ++i) {
            if (!this->sign[i])
                continue;
            this->printLine(this->database[i]);
        }
        if (this->database.size() > 100)
            std::cout << "..." << std::endl;
    }
    /**
     * @brief 清空内存中的数据库数据
     */
    void clear() {
        this->database.clear();
        this->sign.clear();
    }
    /**
     * @brief 获取当前数据库中数据总数量
     * @return 数据库中数据总数量
     * @details 时间复杂度:O(1)
     */
    std::size_t size() const { return this->size_; }
    /**
     * @brief 获取当前数据库中有效数据数量
     * @return 数据库中有效数据数量
     * @details 时间复杂度:O(1)
     */
    std::size_t count() const { return this->size_ - this->count_; }
};

#endif