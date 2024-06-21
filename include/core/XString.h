#pragma once

#include <string>
#include <vector>
#include "./Object.h"

class String :public Object {
private:
    std::wstring string_;
public:
    class OutOfRange;
public:
    String() noexcept;
    String(const wchar_t* str) noexcept;
    String(const std::wstring& str) noexcept;
    String(const String& str) noexcept;
    String(String&& str) noexcept;
    ~String() noexcept;

    bool operator==(const String& str) const noexcept;
    bool operator!=(const String& str) const noexcept;

    String& operator=(const String& str) noexcept;
    operator const std::wstring& () const noexcept;

    wchar_t operator[](int index) const noexcept;
    wchar_t at(int index) const;
    wchar_t& operator[](int index) noexcept;
    wchar_t& at(int index);

    int length() const noexcept;

    String operator+(const String& str) const noexcept;
    String& operator+=(const String& str) noexcept;

    /**
     * @brief 清空字符串
     */
    void clear() noexcept;
    /**
     * @brief 删除字符串开头和结尾的空白字符
     */
    void strip() noexcept;
    /**
     * @brief 将字符串转换为小写
     */
    void toLower() noexcept;
    /**
     * @brief 将字符串转换为大写
     */
    void toUpper() noexcept;

    /**
     * @brief 按照给定的分隔符分割字符串，返回分割后的字符串数组
     * @param delimiter 指定的分隔符
     * @return 字符串数组
     */
    std::vector<String> split(const String& delimiter) const noexcept;
    /**
     * @brief 将此字符串作为分隔符，连接给定的字符串数组，返回连接后的字符串
     * @param strs 给定的字符串数组
     * @return 连接后的字符串
     */
    String join(const std::vector<String>& strs) const noexcept;
    // void replace(const String& oldStr, const String& newStr) noexcept;
    // void remove(const String& str) noexcept;
};