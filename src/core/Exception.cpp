#include "Exception.h"

Exception::Exception(const std::string &message) noexcept
    : message_(message) {}

const char *Exception::what() const noexcept {
    return message_.c_str();
}