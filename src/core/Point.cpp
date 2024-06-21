#include "Point.h"
#include <cmath>

Point::Point(float x, float y) noexcept
 : x_(x), y_(y) {}
Point::~Point() noexcept{}

float &Point::x() noexcept { return x_; }
float &Point::y() noexcept { return y_; }
const float &Point::x() const noexcept { return x_; }
const float &Point::y() const noexcept { return y_; }

Point &Point::operator=(const Point &other) noexcept
{
    x_ = other.x_;
    y_ = other.y_;
    return *this;
}
Point Point::operator+(const Point &other) const noexcept
{
    Point result;
    result.x_ = x_ + other.x_;
    result.y_ = y_ + other.y_;
    return result;
}
Point Point::operator-(const Point &other) const noexcept
{
    Point result;
    result.x_ = x_ - other.x_;
    result.y_ = y_ - other.y_;
    return result;
}
Point Point::operator*(const float &scale) const noexcept
{
    Point result;
    result.x_ = x_ * scale;
    result.y_ = y_ * scale;
    return result;
}
Point Point::operator/(const float &scale) const noexcept
{
    Point result;
    result.x_ = x_ / scale;
    result.y_ = y_ / scale;
    return result;
}
Point &Point::operator+=(const Point &other) noexcept
{
    x_ += other.x_;
    y_ += other.y_;
    return *this;
}
Point &Point::operator-=(const Point &other) noexcept
{
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
}
Point &Point::operator*=(const float &scale) noexcept
{
    x_ *= scale;
    y_ *= scale;
    return *this;
}
Point &Point::operator/=(const float &scale) noexcept
{
    x_ /= scale;
    y_ /= scale;
    return *this;
}

bool Point::operator==(const Point &other) const noexcept
{
    return (x_ == other.x_) && (y_ == other.y_);
}
bool Point::operator!=(const Point &other) const noexcept
{
    return (x_ != other.x_) || (y_ != other.y_);
}

float Point::distance(const Point &other) const noexcept
{
    float dx = x_ - other.x_;
    float dy = y_ - other.y_;
    return std::sqrt(dx * dx + dy * dy);
}