#include "PaintEvent.h"
#include "Painter.h"
#include <stdexcept>

PaintEvent::PaintEvent() noexcept
    :painter_(nullptr) {}

PaintEvent::~PaintEvent() noexcept = default;

Painter& PaintEvent::beginPaint(Block* block) {
    if (!block) {
        throw std::logic_error("Block is null");
    }
    this->painter_ = new Painter(block);
    return *this->painter_;
}

void PaintEvent::endPaint(const Painter& painter) {
    if (this->painter_ != &painter)
        throw std::logic_error("Wrong painter");
    if (this->painter_) {
        delete this->painter_;
        this->painter_ = nullptr;
    }
}
