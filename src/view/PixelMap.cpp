#include "PixelMap.h"
#include "Size.h"
#include "Painter.h"
#include "Rect.h"
#include <ege.h>

PixelMap PixelMap::FormScreen(const Rect &rect)
{
    PixelMap result({rect.width(), rect.height()});
    ege::getimage((ege::IMAGE *)result.image_,
                  rect.x(), rect.y(),
                  rect.width(), rect.height());
    return result;
}

PixelMap PixelMap::FromFile(const std::string &filename)
{
    PixelMap result;
    ege::IMAGE *image = ege::newimage(1, 1);
    ege::getimage((ege::IMAGE *)image, filename.c_str());
    result.image_ = image;
    result.width_ = ege::getwidth((ege::IMAGE *)result.image_);
    result.height_ = ege::getheight((ege::IMAGE *)result.image_);
    return result;
}

PixelMap PixelMap::FromFile(const std::wstring &filename)
{
    PixelMap result;
    ege::IMAGE *image = ege::newimage(1, 1);
    ege::getimage((ege::IMAGE *)image, filename.c_str());
    result.image_ = image;
    result.width_ = ege::getwidth((ege::IMAGE *)result.image_);
    result.height_ = ege::getheight((ege::IMAGE *)result.image_);
    return result;
}

PixelMap::PixelMap(const Size &size)
    : width_(size.width()), height_(size.height())
{
    this->image_ = ege::newimage(width_, height_);
}

PixelMap::PixelMap(const PixelMap &other)
{
    this->width_ = other.width_;
    this->height_ = other.height_;
    this->image_ = ege::newimage(width_, height_);
    ege::putimage((ege::IMAGE *)this->image_,
                  0, 0, (ege::IMAGE *)other.image_,
                  SRCCOPY);
}

PixelMap::PixelMap(PixelMap &&other)
{
    this->width_ = other.width_;
    this->height_ = other.height_;
    this->image_ = other.image_;
    other.image_ = nullptr;
}

PixelMap &PixelMap::operator=(const PixelMap &other)
{
    if (this != &other)
    {
        if (this->image_)
            ege::delimage((ege::IMAGE *)this->image_);
        this->width_ = other.width_;
        this->height_ = other.height_;
        ege::delimage((ege::IMAGE *)this->image_);
        this->image_ = ege::newimage(width_, height_);
        ege::putimage((ege::IMAGE *)this->image_,
                      0, 0, (ege::IMAGE *)other.image_,
                      SRCCOPY);
    }
    return *this;
}

PixelMap &PixelMap::operator=(PixelMap &&other)
{
    if (this != &other)
    {
        if (this->image_)
            ege::delimage((ege::IMAGE *)this->image_);
        this->width_ = other.width_;
        this->height_ = other.height_;
        this->image_ = other.image_;
        other.image_ = nullptr;
    }
    return *this;
}

PixelMap::~PixelMap()
{
    if (this->image_)
        ege::delimage((ege::IMAGE *)this->image_);
    this->image_ = nullptr;
    this->endPaint();
}

Size PixelMap::getSize() const
{
    return Size(this->width_, this->height_);
}

void PixelMap::setSize(const Size &size)
{
    ege::resize((ege::IMAGE *)this->image_,
                static_cast<int>(size.width()),
                static_cast<int>(size.height()));
    this->width_ = size.width();
    this->height_ = size.height();
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

PixelMap PixelMap::clip(const Rect &rect) const
{
    PixelMap result({rect.width(), rect.height()});
    ege::putimage((ege::IMAGE *)result.image_,
                  0, 0, rect.width(), rect.height(),
                  (ege::IMAGE *)this->image_,
                  rect.x(), rect.y(), SRCCOPY);
    return result;
}

bool PixelMap::isNull() const
{
    return this->image_ == nullptr;
}
