#include "MouseEvent.h"

MouseEvent::MouseEvent(Point position): position_(position) {}
MouseEvent::~MouseEvent() = default;

const Point& MouseEvent::position() const {
    return this->position_;
}
