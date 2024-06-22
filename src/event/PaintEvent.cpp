#include "PaintEvent.h"
#include "Exception.h"
#include "Painter.h"


PaintEvent::PaintEvent() noexcept
    :painter_(nullptr) {}

PaintEvent::~PaintEvent() noexcept = default;

Painter& PaintEvent::beginPaint(Block* block) {
    if (!block) {
        throw InvalidBlock(L"Invalid block");
    }
    this->painter_ = new Painter(block);
    return *this->painter_;
}

void PaintEvent::endPaint(const Painter& painter) {
    if (this->painter_ != &painter)
        throw WrongPainter(L"Wrong painter");
    if (this->painter_) {
        delete this->painter_;
        this->painter_ = nullptr;
    }
}

PaintEvent::InvalidBlock::InvalidBlock(const wchar_t* message) noexcept
    :Exception(message) {}

PaintEvent::WrongPainter::WrongPainter(const wchar_t* message) noexcept
    :Exception(message) {}
