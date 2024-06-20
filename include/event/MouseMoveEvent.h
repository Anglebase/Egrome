#pragma once

#include "./MouseEvent.h"

class MouseMoveEvent final : public MouseEvent {
public:
    MouseMoveEvent(const Point& position);
    virtual ~MouseMoveEvent();
};