#include "Size.h"
#include <cmath>

Size::Size(float x, float y) : width_(x), height_(y) {}
Size::~Size() {}

float &Size::width() { return this->width_; }
float &Size::height() { return this->height_; }
const float &Size::width() const { return this->width_; }
const float &Size::height() const { return this->height_; }

Size &Size::operator=(const Size &other)
{
    width_ = other.width_;
    height_ = other.height_;
    return *this;
}
Size Size::operator+(const Size &other) const
{
    Size result;
    result.width_ = width_ + other.width_;
    result.height_ = height_ + other.height_;
    return result;
}
Size Size::operator-(const Size &other) const
{
    Size result;
    result.width_ = width_ - other.width_;
    result.height_ = height_ - other.height_;
    return result;
}
Size Size::operator*(const float &scale) const
{
    Size result;
    result.width_ = width_ * scale;
    result.height_ = height_ * scale;
    return result;
}
Size Size::operator/(const float &scale) const
{
    Size result;
    result.width_ = width_ / scale;
    result.height_ = height_ / scale;
    return result;
}
Size &Size::operator+=(const Size &other)
{
    width_ += other.width_;
    height_ += other.height_;
    return *this;
}
Size &Size::operator-=(const Size &other)
{
    width_ -= other.width_;
    height_ -= other.height_;
    return *this;
}
Size &Size::operator*=(const float &scale)
{
    width_ *= scale;
    height_ *= scale;
    return *this;
}
Size &Size::operator/=(const float &scale)
{
    width_ /= scale;
    height_ /= scale;
    return *this;
}

bool Size::operator==(const Size &other) const
{
    return (width_ == other.width_) && (height_ == other.height_);
}
bool Size::operator!=(const Size &other) const
{
    return (width_ != other.width_) || (height_ != other.height_);
}