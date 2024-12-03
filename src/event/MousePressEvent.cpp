#include "MousePressEvent.h"

MousePressEvent::MousePressEvent(const Point& pos, MouseButton button)
    :MouseKeyEvent(pos, button, ButtonState::Pressed) {}

MousePressEvent::~MousePressEvent() = default;
