#pragma once

#include "./Event.h"

class Block;
class Painter;

class PaintEvent final : public Event {
public:
    const Painter& beginPaint(Block* block) const;
    void endPaint() const;
};