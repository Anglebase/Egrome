#pragma once

#include "./MouseEvent.h"

enum class MouseWheel {
    Up,
    Down,
    None,
};

/**
 * @brief 鼠标滚轮事件
 */
class MouseWheelEvent : public MouseEvent {
private:
    MouseWheel wheel_;
public:
    MouseWheelEvent(const Point& pos, MouseWheel wheel);
    virtual ~MouseWheelEvent();

    /**
     * @brief 获取鼠标滚轮滚动方向
     * @return 鼠标滚轮滚动方向
     */
    MouseWheel wheel() const;
};