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

    void clear() noexcept;
    void strip() noexcept;
    void toLower() noexcept;
    void toUpper() noexcept;

    std::vector<String> split(const String& delimiter) const noexcept;
    String join(const std::vector<String>& strs) const noexcept;
    // void replace(const String& oldStr, const String& newStr) noexcept;
    // void remove(const String& str) noexcept;
};

String operator""_string(const wchar_t* str, size_t len) noexcept;