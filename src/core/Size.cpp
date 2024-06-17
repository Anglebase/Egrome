#include "Size.h"

Size::Size(float w, float h) : width_(w), height_(h) {}

float &Size::width()
{
    return this->width_;
}

float &Size::height()
{
    return this->height_;
}

const float &Size::width() const
{
    return this->width_;
}

const float &Size::height() const
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
    return Size(static_cast<float>(this->width_ * factor), static_cast<float>(this->height_ * factor));
}

Size Size::operator/(double factor) const
{
    return Size(static_cast<float>(this->width_ / factor), static_cast<float>(this->height_ / factor));
}

Size &Size::operator*=(double factor)
{
    return *this = *this * factor;
}

Size &Size::operator/=(double factor)
{
    return *this = *this / factor;
}

std::ostream &operator<<(std::ostream &os, const Size &size)
{
    return os << "[" << size.width_ << ", " << size.height_ << "]";
}
