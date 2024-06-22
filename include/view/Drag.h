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
    
protected:
    void mousePressEvent(MousePressEvent* event) override;
    void mouseMoveEvent(MouseMoveEvent* event) override;
    void mouseReleaseEvent(MouseReleaseEvent* event) override;

    virtual bool isContains(Point point) const;
public:
    Drag(const Rect& rect, Block* parent = nullptr);
    ~Drag() override;

    bool isDragging() const;
    void setTriggerButton(MouseButton button);

public:
    Signal<void(const Point&)> dragged;
    Signal<void(const Point&)> released;
};