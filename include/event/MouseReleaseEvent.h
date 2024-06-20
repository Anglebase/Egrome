#pragma once

#include "./MouseKeyEvent.h"

class MouseReleaseEvent final : public MouseKeyEvent {
public:
    MouseReleaseEvent(const Point& pos, MouseButton button);
    virtual ~MouseReleaseEvent();
};