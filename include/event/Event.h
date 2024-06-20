#pragma once

#include "../core/Object.h"

class Event : public Object {
    mutable bool accepted_;

public:
    Event();
    virtual ~Event();

    void accept() const;
    void reset() const;

    bool isAccepted() const;
};