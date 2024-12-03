#include "MouseWheelEvent.h"

MouseWheelEvent::MouseWheelEvent(const Point& pos, MouseWheel wheel)
    :MouseEvent(pos), wheel_(wheel) {}
MouseWheelEvent::~MouseWheelEvent() = default;

MouseWheel MouseWheelEvent::wheel() const {
    return this->wheel_;
}
