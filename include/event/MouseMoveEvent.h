#pragma once

#include "./MouseEvent.h"

/**
 * @brief 鼠标移动事件类
 */
class MouseMoveEvent final : public MouseEvent {
public:
    MouseMoveEvent(const Point& position);
    virtual ~MouseMoveEvent();
};