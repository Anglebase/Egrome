#include "XString.h"

#include <algorithm>

String::String() noexcept {}
String::String(const wchar_t* str) noexcept : string_(str) {}
String::String(const std::wstring& str) noexcept : string_(str) {}
String::String(const String& str) noexcept {
    this->string_ = str.string_;
}
String::String(String&& str) noexcept {
    this->string_ = std::move(str.string_);
}
String::~String() noexcept = default;

bool String::operator==(const String& str) const noexcept {
    return this->string_ == str.string_;
}

bool String::operator!=(const String& str) const noexcept {
    return this->string_ != str.string_;
}

String& String::operator=(const String& str) noexcept {
    this->string_ = str.string_;
    return *this;
}

String::operator const std::wstring& () const noexcept {
    return this->string_;
}

wchar_t String::operator[](int index) const noexcept {
    return this->string_[index];
}

wchar_t String::at(int index) const {
    if (index < 0 || index >= this->string_.size()) {
        throw String::OutOfRange(L"Index out of range");
    }
    return this->string_[index];
}

wchar_t& String::operator[](int index) noexcept {
    return this->string_[index];
}

wchar_t& String::at(int index) {
    if (index < 0 || index >= this->string_.size()) {
        throw String::OutOfRange(L"Index out of range");
    }
    return this->string_[index];
}

int String::length() const noexcept {
    return this->string_.size();
}

String String::operator+(const String& str) const noexcept {
    return String(this->string_ + str.string_);
}

String& String::operator+=(const String& str) noexcept {
    this->string_ += str.string_;
    return *this;
}

void String::clear() noexcept {
    this->string_.clear();
}

void String::strip() noexcept {
    this->string_.erase(0, this->string_.find_first_not_of(L" \t\n\r\f\v"));
    this->string_.erase(this->string_.find_last_not_of(L" \t\n\r\f\v") + 1);
}

void String::toLower() noexcept {
    std::transform(
        this->string_.begin(), this->string_.end(),
        this->string_.begin(), ::tolower);
}

void String::toUpper() noexcept {
    std::transform(
        this->string_.begin(), this->string_.end(),
        this->string_.begin(), ::toupper);
}

/**
 * @note 如给定分隔符为空，则不会对字符串进行分割操作，直接返回原字符串
 */
std::vector<String> String::split(const String& delimiter) const noexcept {
    if(((std::wstring)delimiter).empty()){
        return { *this };
    }
    std::vector<String> result;
    std::wstring::size_type pos = 0;
    while (true) {
        std::wstring::size_type found = this->string_.find(delimiter, pos);
        if (found == std::wstring::npos) {
            result.emplace_back(this->string_.substr(pos));
            break;
        }
        result.emplace_back(this->string_.substr(pos, found - pos));
        pos = found + delimiter.length();
    }
    return result;
}

String String::join(const std::vector<String>& strs) const noexcept {
    String result = strs[0];
    for (int i = 1; i < strs.size(); i++) {
        result += *this + strs[i];
    }
    return result;
}

String::OutOfRange::OutOfRange(const wchar_t* message) 
    : Exception(message) {}
