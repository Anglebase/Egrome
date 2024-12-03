#pragma once

#include "./Block.h"
#include "../event/MouseKeyEvent.h"
#include "../core/SignalSlots.hpp"

/**
 * @brief 点击行为基类，通过继承此类可以使得Block具有处理点击事件的能力
 */
class Click : virtual public Block {
protected:
    MouseButton button_;
    ButtonState state_;

protected:
    void mousePressEvent(MousePressEvent* event) override;
    void mouseReleaseEvent(MouseReleaseEvent* event) override;
    
    virtual void mouseClickEvent(MouseKeyEvent* event);
    /**
     * @brief 判断点是否在此区域内
     * @param point 点
     * @return true 点在区域内，false 点不在区域内
     * @note 子类可以重载此函数实现自定义可点击区域
     */
    virtual bool isContains(const Point& point) const;

public:
    Click(const Rect& rect, Block* parent = nullptr);
    ~Click() override;

    /**
     * @brief 设置触发点击的鼠标按钮
     * @param button 鼠标按钮
     */
    void setTriggerButton(MouseButton button);
    /**
     * @brief 设置触发点击的鼠标按钮状态
     * @param state 鼠标按钮状态
     */
    void setTriggerState(ButtonState state);

public:
    Signal<void(const Point& pos)> clicked;
};