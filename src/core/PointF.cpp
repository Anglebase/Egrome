#include "core/PointF.h"
#include "core/Point.h"
#include "core/Rect.h"
#include "core/RectF.h"

PointF::PointF(double x, double y) : x_(x), y_(y) {}

double &PointF::x() { return x_; }
double &PointF::y() { return y_; }
const double &PointF::x() const { return x_; }
const double &PointF::y() const { return y_; }

bool PointF::inside(const Rect &rect) const
{
    return (rect.left() <= this->x_ && this->x_ < rect.right() &&
            rect.top() <= this->y_ && this->y_ < rect.bottom());
}

bool PointF::inside(const RectF &rect) const
{
    return (rect.left() <= this->x_ && this->x_ < rect.right() &&
            rect.top() <= this->y_ && this->y_ < rect.bottom());
}

bool PointF::operator==(const PointF &other) const
{
    return this->x_ == other.x_ && this->y_ == other.y_;
}

bool PointF::operator!=(const PointF &other) const
{
    return !(*this == other);
}

PointF PointF::operator+(const PointF &other) const
{
    return PointF(this->x_ + other.x_, this->y_ + other.y_);
}

PointF PointF::operator-(const PointF &other) const
{
    return PointF(this->x_ - other.x_, this->y_ - other.y_);
}

PointF &PointF::operator+=(const PointF &other)
{
    this->x_ += other.x_;
    this->y_ += other.y_;
    return *this;
}

PointF &PointF::operator-=(const PointF &other)
{
    this->x_ -= other.x_;
    this->y_ -= other.y_;
    return *this;
}

PointF::operator Point() const
{
    return Point(static_cast<double>(this->x_), static_cast<double>(this->y_));
}

std::ostream &operator<<(std::ostream &os, const PointF &p)
{
    os << "(" << p.x_ << ", " << p.y_ << ")";
    return os;
}
