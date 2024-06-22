#pragma once

#include <string>
#include <vector>
#include "./Object.h"
#include "./Exception.h"

class String :public Object {
private:
    std::wstring string_;
public:
    class OutOfRange : public Exception {
    public:
        OutOfRange(const wchar_t* message);
    };
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
    /**
     * @brief 获取指定位置的字符
     * @param index 指定位置
     * @return 指定位置的字符
     * @throw OutOfRange 当索引越界时
     */
    wchar_t at(int index) const;
    wchar_t& operator[](int index) noexcept;
    /**
     * @brief 这是一个重载
     * @see at(int index) const
     */
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
     * @see join(const std::vector<String>& strs) const
     * @details 若分隔符不为空，join方法与split方法是互逆的
     */
    std::vector<String> split(const String& delimiter) const noexcept;
    /**
     * @brief 将此字符串作为分隔符，连接给定的字符串数组，返回连接后的字符串
     * @param strs 给定的字符串数组
     * @return 连接后的字符串
     * @see split(const String& delimiter) const
     * @details 若分隔符不为空，join方法与split方法是互逆的
     */
    String join(const std::vector<String>& strs) const noexcept;
    // void replace(const String& oldStr, const String& newStr) noexcept;
    // void remove(const String& str) noexcept;
};