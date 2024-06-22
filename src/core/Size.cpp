#include "Size.h"
#include <cmath>

Size::Size(float x, float y) noexcept
: width_(x), height_(y) {}
Size::~Size() noexcept {}

float &Size::width() noexcept { return this->width_; }
float &Size::height() noexcept { return this->height_; }
const float &Size::width() const noexcept { return this->width_; }
const float &Size::height() const noexcept { return this->height_; }

Size &Size::operator=(const Size &other) noexcept
{
    width_ = other.width_;
    height_ = other.height_;
    return *this;
}
Size Size::operator+(const Size &other) const noexcept
{
    Size result;
    result.width_ = width_ + other.width_;
    result.height_ = height_ + other.height_;
    return result;
}
Size Size::operator-(const Size &other) const noexcept
{
    Size result;
    result.width_ = width_ - other.width_;
    result.height_ = height_ - other.height_;
    return result;
}
Size Size::operator*(const float &scale) const noexcept
{
    Size result;
    result.width_ = width_ * scale;
    result.height_ = height_ * scale;
    return result;
}
Size Size::operator/(const float &scale) const noexcept
{
    Size result;
    result.width_ = width_ / scale;
    result.height_ = height_ / scale;
    return result;
}
Size &Size::operator+=(const Size &other) noexcept
{
    width_ += other.width_;
    height_ += other.height_;
    return *this;
}
Size &Size::operator-=(const Size &other) noexcept
{
    width_ -= other.width_;
    height_ -= other.height_;
    return *this;
}
Size &Size::operator*=(const float &scale) noexcept
{
    width_ *= scale;
    height_ *= scale;
    return *this;
}
Size &Size::operator/=(const float &scale) noexcept
{
    width_ /= scale;
    height_ /= scale;
    return *this;
}

bool Size::operator==(const Size &other) const noexcept
{
    return (width_ == other.width_) && (height_ == other.height_);
}
bool Size::operator!=(const Size &other) const noexcept
{
    return (width_ != other.width_) || (height_ != other.height_);
}