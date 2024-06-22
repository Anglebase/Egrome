#pragma once

#include "../core/Point.h"
#include "./Event.h"

/**
 * @brief 鼠标事件基类
 */
class MouseEvent : public Event {
protected:
    Point position_;
public:
    MouseEvent(Point position);
    virtual ~MouseEvent();

    /**
     * @brief 获取鼠标位置
     * @return 鼠标位置
     */
    const Point& position() const;
};