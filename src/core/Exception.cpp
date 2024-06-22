#include "Exception.h"
#include <cwchar>

Exception::Exception(const wchar_t* message) {
    this->message_ = new wchar_t[std::wcslen(message) + 1];
    std::wcscpy(this->message_, message);
}
Exception::~Exception(){
    delete[] this->message_;
}

const wchar_t* Exception::getMessage() const {
    return this->message_;
}
