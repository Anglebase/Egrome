#include "core/Size.h"
#include "core/SizeF.h"
#include "Size.h"

Size::Size(long w, long h) : width_(w), height_(h) {}

long &Size::width()
{
    return this->width_;
}

long &Size::height()
{
    return this->height_;
}

const long &Size::width() const
{
    return this->width_;
}

const long &Size::height() const
{
    return this->height_;
}

bool Size::operator==(const Size &other) const
{
    return this->width_ == other.width_ && this->height_ == other.height_;
}

bool Size::operator!=(const Size &other) const
{
    return !(*this == other);
}

Size Size::operator+(const Size &other) const
{
    return Size(this->width_ + other.width_, this->height_ + other.height_);
}

Size Size::operator-(const Size &other) const
{
    return Size(this->width_ - other.width_, this->height_ - other.height_);
}

Size &Size::operator+=(const Size &other)
{
    return *this = *this + other;
}

Size &Size::operator-=(const Size &other)
{
    return *this = *this - other;
}

Size Size::operator*(double factor) const
{
    return Size(static_cast<long>(this->width_ * factor), static_cast<long>(this->height_ * factor));
}

Size Size::operator/(double factor) const
{
    return Size(static_cast<long>(this->width_ / factor), static_cast<long>(this->height_ / factor));
}

Size &Size::operator*=(double factor)
{
    return *this = *this * factor;
}

Size &Size::operator/=(double factor)
{
    return *this = *this / factor;
}

Size::operator SizeF() const
{
    return SizeF(static_cast<double>(this->width_), static_cast<double>(this->height_));
}

std::ostream &operator<<(std::ostream &os, const Size &size)
{
    return os << "[" << size.width_ << ", " << size.height_ << "]";
}
