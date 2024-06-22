#pragma once

#include "./MouseKeyEvent.h"

/**
 * @brief 鼠标按下事件
 */
class MousePressEvent final : public MouseKeyEvent {
public:
    MousePressEvent(const Point& pos, MouseButton button);
    virtual ~MousePressEvent();
};