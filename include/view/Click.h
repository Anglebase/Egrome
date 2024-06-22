#pragma once

#include "./Block.h"
#include "../event/MouseKeyEvent.h"
#include "../core/SignalSlots.hpp"

/**
 * @brief 点击行为基类，通过继承此类可以使得Block具有处理点击事件的能力
 */
class Click : public Block {
private:
    MouseButton button_;
    ButtonState state_;

protected:
    void mousePressEvent(MousePressEvent* event) override;
    void mouseReleaseEvent(MouseReleaseEvent* event) override;
    
    virtual void mouseClickEvent(MouseKeyEvent* event);
    virtual bool isContains(const Point& point) const;

public:
    Click(const Rect& rect, Block* parent = nullptr);
    ~Click() override;

    void setTriggerButton(MouseButton button);
    void setTriggerState(ButtonState state);

public:
    Signal<void(const Point& pos)> clicked;
};