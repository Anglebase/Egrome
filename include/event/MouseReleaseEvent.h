#pragma once

#include "./MouseKeyEvent.h"

/**
 * @brief 鼠标按钮弹起事件
 */
class MouseReleaseEvent final : public MouseKeyEvent {
public:
    MouseReleaseEvent(const Point& pos, MouseButton button);
    virtual ~MouseReleaseEvent();
};