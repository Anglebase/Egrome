#include "core/Point.h"
#include "core/PointF.h"
#include "core/Rect.h"
#include "core/RectF.h"

Point::Point(long x, long y) : x(x), y(y) {}

long Point::getX() const
{
    return this->x;
}

long Point::getY() const
{
    return this->y;
}

void Point::setX(long x)
{
    this->x = x;
}

void Point::setY(long y)
{
    this->y = y;
}


bool Point::inside(const Rect &rect) const
{
    return (rect.left() <= this->x && this->x < rect.right() &&
            rect.top() <= this->y && this->y < rect.bottom());
}

bool Point::inside(const RectF &rect) const
{
    return (rect.left() <= this->x && this->x < rect.right() &&
            rect.top() <= this->y && this->y < rect.bottom());
}

bool Point::operator==(const Point &other) const
{
    return this->x == other.x && this->y == other.y;
}

bool Point::operator!=(const Point &other) const
{
    return !(*this == other);
}

Point Point::operator+(const Point &other) const
{
    return Point(this->x + other.x, this->y + other.y);
}

Point Point::operator-(const Point &other) const
{
    return Point(this->x - other.x, this->y - other.y);
}

Point &Point::operator+=(const Point &other)
{  
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Point &Point::operator-=(const Point &other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Point::operator PointF() const
{
    return PointF(static_cast<double>(this->x), static_cast<double>(this->y));
}

std::ostream &operator<<(std::ostream &os, const Point &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
