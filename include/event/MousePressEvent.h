#pragma once

#include "./MouseKeyEvent.h"

class MousePressEvent final : public MouseKeyEvent {
public:
    MousePressEvent(const Point& pos, MouseButton button);
    virtual ~MousePressEvent();
};