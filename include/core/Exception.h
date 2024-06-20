#pragma once

#include "./Object.h"
#include "./String.h"

class Exception : public Object {
protected:
    String message_;
public:
    Exception(const String& message);
    virtual ~Exception();

    virtual const String& getMessage() const;
};