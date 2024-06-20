#pragma once

#include "./MouseEvent.h"

enum class MouseButton {
    Left,
    Right,
    Middle,
    // XButton1,
    // XButton2,
};

enum class ButtonState {
    Pressed,
    Released,
};

class MouseKeyEvent : public MouseEvent {
private:
    MouseButton button_;
    ButtonState state_;

public:
    MouseKeyEvent(const Point& pos, MouseButton button, ButtonState state);
    virtual ~MouseKeyEvent();

    MouseButton button() const;
    ButtonState state() const;
};