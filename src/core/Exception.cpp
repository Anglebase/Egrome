#include "Exception.h"

Exception::Exception(const String& message) : message_(message) {}
Exception::~Exception() = default;

const String& Exception::getMessage() const {
    return this->message_;
}
