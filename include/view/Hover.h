#pragma once

#include "./Block.h"
#include "../core/SignalSlots.hpp"

class Hover : public Block {
private:
    Point lastPos;
    bool hasPos;

protected:
    void mouseMoveEvent(MouseMoveEvent* event) override;

    virtual bool isContains(const Point& point);
public:
    Hover(const Rect& rect, Block* parent = nullptr);
    ~Hover() override;

public:
    Signal<void(const Point& pos)> entered;
    Signal<void(const Point& pos)> leaved;
};