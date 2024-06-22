#pragma once

#include "./Object.h"

class Exception : public Object {
protected:
    wchar_t* message_;
public:
    Exception(const wchar_t* message);
    virtual ~Exception();

    virtual const wchar_t* getMessage() const;
};