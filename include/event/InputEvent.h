#pragma once

#include "./Event.h"

class InputEvent final : public Event {
private:
    wchar_t inputChar_;
public:
    InputEvent(const wchar_t inputChar);
    virtual ~InputEvent();

    wchar_t content() const;
};