#include "Point.h"
#include <cmath>

Point::Point(float x, float y) : x_(x), y_(y) {}
Point::~Point() {}

float &Point::x() { return x_; }
float &Point::y() { return y_; }
const float &Point::x() const { return x_; }
const float &Point::y() const { return y_; }

Point &Point::operator=(const Point &other)
{
    x_ = other.x_;
    y_ = other.y_;
    return *this;
}
Point Point::operator+(const Point &other) const
{
    Point result;
    result.x_ = x_ + other.x_;
    result.y_ = y_ + other.y_;
    return result;
}
Point Point::operator-(const Point &other) const
{
    Point result;
    result.x_ = x_ - other.x_;
    result.y_ = y_ - other.y_;
    return result;
}
Point Point::operator*(const float &scale) const
{
    Point result;
    result.x_ = x_ * scale;
    result.y_ = y_ * scale;
    return result;
}
Point Point::operator/(const float &scale) const
{
    Point result;
    result.x_ = x_ / scale;
    result.y_ = y_ / scale;
    return result;
}
Point &Point::operator+=(const Point &other)
{
    x_ += other.x_;
    y_ += other.y_;
    return *this;
}
Point &Point::operator-=(const Point &other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
}
Point &Point::operator*=(const float &scale)
{
    x_ *= scale;
    y_ *= scale;
    return *this;
}
Point &Point::operator/=(const float &scale)
{
    x_ /= scale;
    y_ /= scale;
    return *this;
}

bool Point::operator==(const Point &other) const
{
    return (x_ == other.x_) && (y_ == other.y_);
}
bool Point::operator!=(const Point &other) const
{
    return (x_ != other.x_) || (y_ != other.y_);
}

float Point::distance(const Point &other) const
{
    float dx = x_ - other.x_;
    float dy = y_ - other.y_;
    return std::sqrt(dx * dx + dy * dy);
}