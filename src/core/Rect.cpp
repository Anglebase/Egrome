#include "core/Rect.h"
#include "core/Point.h"
#include "core/Size.h"
#include "core/RectF.h"

Rect::Rect(long x, long y, long width, long height)
    : x(x), y(y), width(width), height(height) {}

Rect::Rect(const Point &topLeft, const Size &size)
    : x(topLeft.getX()), y(topLeft.getY()), width(size.getWidth()), height(size.getHeight()) {}

Point Rect::getTopLeft() const
{
    return Point(x, y);
}

Point Rect::getTopRight() const
{
    return Point(x + width, y);
}

Point Rect::getBottomLeft() const
{
    return Point(x, y + height);
}

Point Rect::getBottomRight() const
{
    return Point(x + width, y + height);
}

long Rect::left() const
{
    return this->x;
}

long Rect::top() const
{
    return this->y;
}

long Rect::right() const
{
    return this->x + this->width;
}

long Rect::bottom() const
{
    return this->y + this->height;
}

void Rect::setTopLeft(const Point &topLeft)
{
    this->x = topLeft.getX();
    this->y = topLeft.getY();
}

void Rect::setTopRight(const Point &topRight)
{
    this->x = topRight.getX() - this->width;
    this->y = topRight.getY();
}

void Rect::setBottomLeft(const Point &bottomLeft)
{
    this->x = bottomLeft.getX();
    this->y = bottomLeft.getY() - this->height;
}

void Rect::setBottomRight(const Point &bottomRight)
{
    this->x = bottomRight.getX() - this->width;
    this->y = bottomRight.getY() - this->height;
}

Size Rect::getSize() const
{
    return Size(width, height);
}

void Rect::setSize(const Size &size)
{
    this->width = size.getWidth();
    this->height = size.getHeight();
}

bool Rect::contains(const Point &point) const
{
    return (point.getX() >= x && point.getX() <= x + width &&
            point.getY() >= y && point.getY() <= y + height);
}

bool Rect::contains(long x, long y) const
{
    return (x >= this->x && x <= this->x + this->width &&
            y >= this->y && y <= this->y + this->height);
}

bool Rect::intersects(const Rect &other) const
{
    return (x < other.x + other.width && x + width > other.x &&
            y < other.y + other.height && y + height > other.y);
}

void Rect::offset(long dx, long dy)
{
    x += dx;
    y += dy;
}

void Rect::offset(const Point &dpoint)
{
    x += dpoint.getX();
    y += dpoint.getY();
}

void Rect::inflate(long dx, long dy)
{
    width += dx;
    height += dy;
}

void Rect::inflate(const Size &dsize)
{
    width += dsize.getWidth();
    height += dsize.getHeight();
}

bool Rect::operator==(const Rect &other) const
{
    return (x == other.x && y == other.y &&
            width == other.width && height == other.height);
}

bool Rect::operator!=(const Rect &other) const
{
    return !(*this == other);
}

Rect::operator RectF() const
{
    return RectF(static_cast<double>(x), static_cast<double>(y),
                 static_cast<double>(width), static_cast<double>(height));
}

std::ostream &operator<<(std::ostream &os, const Rect &rect)
{
    return os << "{" << Point(rect.x, rect.y) << ", "
              << Size(rect.width, rect.height) << "}";
}
