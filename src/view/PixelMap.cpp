#include "PixelMap.h"
#include "Size.h"
#include "Painter.h"
#include "Rect.h"
#include <ege.h>

std::shared_ptr<PixelMap> PixelMap::FormScreen(const Rect &rect)
{
    auto result = std::make_shared<PixelMap>(rect.width(), rect.height());
    ege::getimage((ege::IMAGE *)result->image_,
                  0, 0,
                  rect.width(), rect.height());
    return result;
}

std::shared_ptr<PixelMap> PixelMap::FromFile(const std::string &filename)
{
    auto result = std::make_shared<PixelMap>(1, 1);
    ege::getimage((ege::IMAGE *)result->image_,
                  filename.c_str());
    result->width_ = ege::getwidth((ege::IMAGE *)result->image_);
    result->height_ = ege::getheight((ege::IMAGE *)result->image_);
    return result;
}

PixelMap::PixelMap(long width, long height)
    : width_(width), height_(height)
{
    this->image_ = ege::newimage(width, height);
}

PixelMap::PixelMap(const Size &size)
    : width_(size.width()), height_(size.height())
{
    this->image_ = ege::newimage(width_, height_);
}

PixelMap::~PixelMap()
{
    ege::delimage((ege::IMAGE *)this->image_);
    this->image_ = nullptr;
    this->endPaint();
}

Size PixelMap::getSize() const
{
    return Size(this->width_, this->height_);
}

void PixelMap::setSize(int width, int height)
{
    this->width_ = width;
    this->height_ = height;
    ege::resize((ege::IMAGE *)this->image_, width, height);
}

const Painter &PixelMap::beginPaint() const
{
    if (this->painter_ == nullptr)
        this->painter_ = new Painter(this);
    return *this->painter_;
}

void PixelMap::endPaint() const
{
    if (this->painter_ != nullptr)
    {
        delete this->painter_;
        this->painter_ = nullptr;
    }
}

std::shared_ptr<PixelMap> PixelMap::clone() const
{
    auto result = std::make_shared<PixelMap>(this->width_, this->height_);
    ege::putimage((ege::IMAGE *)result->image_,
                  0, 0, (ege::IMAGE *)this->image_,
                  SRCCOPY);
    return result;
}

std::shared_ptr<PixelMap> PixelMap::clip(const Rect &rect) const
{
    auto result = std::make_shared<PixelMap>(rect.width(), rect.height());
    ege::putimage((ege::IMAGE *)result->image_,
                  0, 0, rect.width(), rect.height(),
                  (ege::IMAGE *)this->image_,
                  rect.x(), rect.y(), SRCCOPY);
    return result;
}
