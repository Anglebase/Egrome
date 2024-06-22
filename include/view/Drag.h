#pragma once

#include "../core/SignalSlots.hpp"
#include "./Block.h"
#include "../event/MouseKeyEvent.h"

/**
 * @brief 拖动行为基类，通过继承此类可以使得Block具有拖动行为
 */
class Drag : public Block {
private:
    bool isDragging_;
    Point relativePos;

    MouseButton button_;

    bool xDraggable_;
    bool yDraggable_;
    
protected:
    void mousePressEvent(MousePressEvent* event) override;
    void mouseMoveEvent(MouseMoveEvent* event) override;
    void mouseReleaseEvent(MouseReleaseEvent* event) override;

    /**
     * @brief 判断点是否在此区域内
     * @param point 点
     * @return true 点在区域内，false 点不在区域内
     * @note 子类可以重载此函数实现自定义可点击区域
     */
    virtual bool isContains(Point point) const;
public:
    Drag(const Rect& rect, Block* parent = nullptr);
    ~Drag() override;

    /**
     * @brief 是否正在被拖动
     * @return true 正在被拖动，false 未被拖动
     */
    bool isDragging() const;
    /**
     * @brief 设置触发拖动的鼠标按键
     * @param button 鼠标按键
     */
    void setTriggerButton(MouseButton button);

    void setXDraggable(bool draggable);
    void setYDraggable(bool draggable);

public:
    Signal<void(const Point&)> dragged;
    Signal<void(const Point&)> released;
};