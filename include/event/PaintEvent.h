#pragma once

#include "./Event.h"
#include "../core/Exception.h"

class Block;
class Painter;

class PaintEvent final : public Event {
private:
    mutable Painter* painter_;

    class InvalidBlock : public Exception {
    public:
        InvalidBlock(const String& message) noexcept;
    };
    class WrongPainter : public Exception {
    public:
        WrongPainter(const String& message) noexcept;
    };
public:
    PaintEvent() noexcept;
    ~PaintEvent() noexcept;
    Painter& beginPaint(Block* block);
    void endPaint(const Painter& painter);
};