#include "MouseKeyEvent.h"

MouseKeyEvent::MouseKeyEvent(const Point& pos, MouseButton button, ButtonState state)
    : MouseEvent(pos), button_(button), state_(state) {}

MouseKeyEvent::~MouseKeyEvent() = default;

MouseButton MouseKeyEvent::button() const {
    return this->button_;
}

ButtonState MouseKeyEvent::state() const {
    return this->state_;
}
