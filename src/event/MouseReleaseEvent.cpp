#include "MouseReleaseEvent.h"

MouseReleaseEvent::MouseReleaseEvent(const Point& pos, MouseButton button)
    : MouseKeyEvent(pos, button, ButtonState::Released) {}

MouseReleaseEvent::~MouseReleaseEvent() = default;
