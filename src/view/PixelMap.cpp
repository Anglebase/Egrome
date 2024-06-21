#include "PixelMap.h"
#include "Size.h"
#include "Painter.h"

#include <ege.h>

Size PixelMap::SizeData::operator=(const Size& size) noexcept {
    if (!this->map_->image_)return Size();
    ege::resize((ege::PIMAGE)this->map_->image_, size.width(), size.height());
    return size;
}
PixelMap::SizeData::operator Size() const noexcept {
    if (!this->map_->image_)return Size();
    return Size{
        ege::getwidth((ege::PIMAGE)this->map_->image_),
        ege::getheight((ege::PIMAGE)this->map_->image_),
    };
}

PixelMap::SizeData PixelMap::size() noexcept {
    return SizeData(this);
}

Size PixelMap::size() const noexcept {
    if (!this->image_)return Size();
    return Size{
        ege::getwidth((ege::PIMAGE)this->image_),
        ege::getheight((ege::PIMAGE)this->image_),
    };
}

PixelMap::PixelMap() noexcept
    : image_(nullptr), painter_(nullptr) {}

PixelMap::PixelMap(int width, int height) noexcept
    :painter_(nullptr) {
    this->image_ = ege::newimage(width, height);
}

PixelMap::PixelMap(const PixelMap& other) noexcept
    : painter_(nullptr) {
    this->image_ = ege::newimage(other.size().width(), other.size().height());
    ege::putimage((ege::PIMAGE)this->image_, 0, 0,
        (ege::PIMAGE)other.image_);
}

PixelMap::PixelMap(PixelMap&& other) noexcept
    :painter_(nullptr) {
    this->image_ = other.image_;
    other.image_ = nullptr;
}

PixelMap::~PixelMap() noexcept {
    if (this->image_) {
        ege::delimage((ege::PIMAGE)this->image_);
        this->image_ = nullptr;
    }
}

PixelMap& PixelMap::operator=(const PixelMap& other) noexcept {
    if (this == &other)return *this;
    if (this->image_) {
        ege::delimage((ege::PIMAGE)this->image_);
        this->image_ = nullptr;
    }
    this->image_ = ege::newimage(other.size().width(), other.size().height());
    ege::putimage((ege::PIMAGE)this->image_, 0, 0,
        (ege::PIMAGE)other.image_);
    return *this;
}

PixelMap& PixelMap::operator=(PixelMap&& other) noexcept {
    if (this == &other)return *this;
    if (this->image_) {
        ege::delimage((ege::PIMAGE)this->image_);
        this->image_ = nullptr;
    }
    this->image_ = other.image_;
    other.image_ = nullptr;
    return *this;
}

const Painter& PixelMap::beginPaint() noexcept {
    if (this->painter_)return *this->painter_;
    this->painter_ = new Painter(this);
    return *this->painter_;
}

void PixelMap::endPaint() noexcept {
    if (this->painter_) {
        delete this->painter_;
        this->painter_ = nullptr;
    }
}
