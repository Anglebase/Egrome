#include "PaintEvent.h"
#include "Exception.h"
#include "Painter.h"

class PaintEvent::InvalidBlock :public Exception {
public:
    InvalidBlock(const String& message)
        :Exception(message) {}
};

PaintEvent::PaintEvent() noexcept
    :painter_(nullptr) {}

PaintEvent::~PaintEvent() noexcept = default;

const Painter& PaintEvent::beginPaint(Block* block) const {
    if (!block) {
        throw InvalidBlock(L"Invalid block");
    }
    this->painter_ = new Painter(block);
    return *this->painter_;
}

void PaintEvent::endPaint() const noexcept {
    if (this->painter_) {
        delete this->painter_;
        this->painter_ = nullptr;
    }
}
