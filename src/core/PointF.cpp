#include "core/PointF.h"
#include "core/Point.h"
#include "core/Rect.h"
#include "core/RectF.h"

PointF::PointF(double x, double y) : x(x), y(y) {}

double PointF::getX() const
{
    return this->x;
}

double PointF::getY() const
{
    return this->y;
}

void PointF::setX(double x)
{
    this->x = x;
}

void PointF::setY(double y)
{
    this->y = y;
}


bool PointF::inside(const Rect &rect) const
{
    return (rect.left() <= this->x && this->x < rect.right() &&
            rect.top() <= this->y && this->y < rect.bottom());
}

bool PointF::inside(const RectF &rect) const
{
    return (rect.left() <= this->x && this->x < rect.right() &&
            rect.top() <= this->y && this->y < rect.bottom());
}

bool PointF::operator==(const PointF &other) const
{
    return this->x == other.x && this->y == other.y;
}

bool PointF::operator!=(const PointF &other) const
{
    return !(*this == other);
}

PointF PointF::operator+(const PointF &other) const
{
    return PointF(this->x + other.x, this->y + other.y);
}

PointF PointF::operator-(const PointF &other) const
{
    return PointF(this->x - other.x, this->y - other.y);
}

PointF &PointF::operator+=(const PointF &other)
{  
    this->x += other.x;
    this->y += other.y;
    return *this;
}

PointF &PointF::operator-=(const PointF &other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

PointF::operator Point() const
{
    return Point(static_cast<double>(this->x), static_cast<double>(this->y));
}

std::ostream &operator<<(std::ostream &os, const PointF &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
