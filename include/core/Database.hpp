#pragma once

// 此功能需要C++17或更高版本
#if __cplusplus > 201703L

#include<tuple>
#include<vector>
#include<string>
#include<cstring>

template<typename T>
class Table;
/**
 * @brief 本地数据库类
 * @tparam ...Args 指定表的字段类型
 */
template<typename...Args>
class Table<std::tuple<Args...>> {
    using Line = std::tuple<Args...>;
    const std::size_t header_lenth = 64ULL;

private:
    std::vector<Line> database; // 表的数据
    std::vector<bool> sign;

protected:
    std::size_t lenth;          // 一条数据的长度
    std::size_t size;           // 此表的数据量

    /**
     * @brief 读取数据的格式化函数
     * @param input 从文件中读取的一行数据
     * @param data 进行类型格式化后的结果
     * @details 在子类中，必须实现此函数
     */
    virtual void readLine(const void* input, Line& data) = 0;
    /**
     * @brief 写入数据的格式化函数
     * @param output 要写入数据库的一行数据
     * @param data 将要写入数据库的具有类型的数据
     * @details 在子类中，必须实现此函数
     */
    virtual void writeLine(void* output, const Line& data) = 0;

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
        std::fread(&this->size, sizeof(std::size_t), 1, input);

        if (filelenth != this->lenth * this->size + 64) return false;
        this->sign = std::vector<bool>(this->size, true);

        // 读取数据
        std::fseek(input, this->header_lenth, SEEK_SET);
        void* data = (void*)new char[this->lenth];
        Line format_data;
        for (int count = 0; count < this->size; ++count) {
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
    bool saveDatabase(const std::string_view& database_path, std::size_t lenth = (sizeof(Args) + ...)) {
        std::FILE* output = std::fopen(database_path.data(), "w");
        if (!output) return false;

        char header[this->header_lenth];
        std::memset(header, 0, sizeof(header));

        this->size = this->database.size();
        std::size_t filelenth = this->size * lenth + this->header_lenth;

        std::memcpy(header, &filelenth, sizeof(std::size_t));
        std::memcpy(header + sizeof(std::size_t), &lenth, sizeof(std::size_t));
        std::memcpy(header + sizeof(std::size_t) * 2, &this->size, sizeof(std::size_t));

        fwrite(header, sizeof(header), 1, output);
        void* data = (void*)new char[lenth];
        int count = -1;
        for (const auto& linedata : this->database) {
            ++count;
            if (!this->sign[count])
                continue;

            this->writeLine(data, linedata);
            fwrite(data, lenth, 1, output);
        }

        delete[](char*)data;
        data = nullptr;
        std::fclose(output);
        return true;
    }
    /**
     * @brief 向数据库中添加一行数据
     * @param line 要添加的数据
     */
    void append(const Line& line) {
        this->database.push_back(line);
        this->sign.push_back(true);
    }
    /**
     * @brief 向数据库中移动一行数据
     * @param line 要移动的数据
     */
    void append(Line&& line) {
        this->database.push_back(line);
        this->sign.push_back(true);
    }
    /**
     * @brief 将数据库中指定位置的数据设置为删除状态
     * @param index 索引
     * @details 调用此函数后，数据库中对应位置的数据将被标记为删除状态，不会被保存至文件中
     */
    void revoke(std::size_t index) { this->sign[index] = false; }
    /**
     * @brief 获取数据库中指定位置的数据
     * @param index 索引
     * @return 数据库中指定位置的数据
     */
    Line& getline(std::size_t index) { return this->database[index]; }

    /**
     * @brief 查找并返回所有满足condition的行
     * @tparam N 要比较的字段的索引
     * @tparam Func 条件函数类型
     * @param condition 条件函数
     * @return 所有满足condition的行数据和索引，即 condition(std::get<N>(line))==true
     */
    template<std::size_t N, class Func>
    std::vector<std::pair<const Line*, std::size_t>> find_if(Func condition) {
        std::vector<std::pair<const Line*, std::size_t>> results;
        std::size_t index = 0;
        for (const auto& line : this->database) {
            if (condition(std::get<N>(line)))
                results.push_back({ &line,index });
            ++index;
        }
        return results;
    }
};

#endif