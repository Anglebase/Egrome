#pragma once

#include "./MouseEvent.h"

enum class MouseWheel {
    Up,
    Down,
    None,
};

class MouseWheelEvent : public MouseEvent {
private:
    MouseWheel wheel_;
public:
    MouseWheelEvent(const Point& pos, MouseWheel wheel);
    virtual ~MouseWheelEvent();

    MouseWheel wheel() const;
};