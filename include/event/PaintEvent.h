#pragma once

#include "./Event.h"
#include "../core/Exception.h"

class Block;
class Painter;

/**
 * @brief 视图绘制事件
 */
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
    /**
     * @brief 开始绘制
     * @param block 需要绘制的块
     * @return 针对于所给block的Painter对象
     */
    Painter& beginPaint(Block* block);
    /**
     * @brief 结束绘制
     * @param painter beginPaint返回的绘制器对象
     */
    void endPaint(const Painter& painter);
};