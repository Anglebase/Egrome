#include "core/Point.h"
#include "core/PointF.h"
#include "core/Rect.h"
#include "core/RectF.h"

Point::Point(long x, long y) : x_(x), y_(y) {}

long &Point::x() { return x_; }
long &Point::y() { return y_; }
const long &Point::x() const { return x_; }
const long &Point::y() const { return y_; }

bool Point::inside(const Rect &rect) const
{
    // std::cout << "Rect:" << rect << " |Point:" << *this << std::endl;
    return (rect.left() <= this->x_ && this->x_ < rect.right() &&
            rect.top() <= this->y_ && this->y_ < rect.bottom());
}

bool Point::inside(const RectF &rect) const
{
    return (rect.left() <= this->x_ && this->x_ < rect.right() &&
            rect.top() <= this->y_ && this->y_ < rect.bottom());
}

bool Point::operator==(const Point &other) const
{
    return this->x_ == other.x_ && this->y_ == other.y_;
}

bool Point::operator!=(const Point &other) const
{
    return !(*this == other);
}

Point Point::operator+(const Point &other) const
{
    return Point(this->x_ + other.x_, this->y_ + other.y_);
}

Point Point::operator-(const Point &other) const
{
    return Point(this->x_ - other.x_, this->y_ - other.y_);
}

Point &Point::operator+=(const Point &other)
{
    this->x_ += other.x_;
    this->y_ += other.y_;
    return *this;
}

Point &Point::operator-=(const Point &other)
{
    this->x_ -= other.x_;
    this->y_ -= other.y_;
    return *this;
}

Point::operator PointF() const
{
    return PointF(static_cast<double>(this->x_), static_cast<double>(this->y_));
}

std::ostream &operator<<(std::ostream &os, const Point &p)
{
    os << "(" << p.x_ << ", " << p.y_ << ")";
    return os;
}
