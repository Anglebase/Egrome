#pragma once

#include "./Event.h"

class Block;
class Painter;

class PaintEvent final : public Event {
private:
    mutable Painter* painter_;

    class InvalidBlock;
public:
    PaintEvent() noexcept;
    ~PaintEvent() noexcept;
    const Painter& beginPaint(Block* block) const;
    void endPaint() const noexcept;
};