#include "InputEvent.h"

InputEvent::InputEvent(const wchar_t inputChar) : inputChar_(inputChar) {}
InputEvent::~InputEvent() = default;

wchar_t InputEvent::content() const {
    return this->inputChar_;
}
