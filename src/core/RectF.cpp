#include "core/RectF.h"
#include "core/PointF.h"
#include "core/SizeF.h"
#include "core/Rect.h"

RectF::RectF(double x, double y, double width, double height)
    : x(x), y(y), width(width), height(height) {}

RectF::RectF(const PointF &topLeft, const SizeF &sizeF)
    : x(topLeft.getX()), y(topLeft.getY()), width(sizeF.getWidth()), height(sizeF.getHeight()) {}

PointF RectF::getTopLeft() const
{
    return PointF(x, y);
}

PointF RectF::getTopRight() const
{
    return PointF(x + width, y);
}

PointF RectF::getBottomLeft() const
{
    return PointF(x, y + height);
}

PointF RectF::getBottomRight() const
{
    return PointF(x + width, y + height);
}

double RectF::left() const
{
    return this->x;
}

double RectF::top() const
{
    return this->y;
}

double RectF::right() const
{
    return this->x + this->width;
}

double RectF::bottom() const
{
    return this->y + this->height;
}

void RectF::setTopLeft(const PointF &topLeft)
{
    this->x = topLeft.getX();
    this->y = topLeft.getY();
}

void RectF::setTopRight(const PointF &topRight)
{
    this->x = topRight.getX() - this->width;
    this->y = topRight.getY();
}

void RectF::setBottomLeft(const PointF &bottomLeft)
{
    this->x = bottomLeft.getX();
    this->y = bottomLeft.getY() - this->height;
}

void RectF::setBottomRight(const PointF &bottomRight)
{
    this->x = bottomRight.getX() - this->width;
    this->y = bottomRight.getY() - this->height;
}

SizeF RectF::getSizeF() const
{
    return SizeF(width, height);
}

void RectF::setSizeF(const SizeF &sizeF)
{
    this->width = sizeF.getWidth();
    this->height = sizeF.getHeight();
}

bool RectF::contains(const PointF &pointF) const
{
    return (pointF.getX() >= x && pointF.getX() <= x + width &&
            pointF.getY() >= y && pointF.getY() <= y + height);
}

bool RectF::contains(double x, double y) const
{
    return (x >= this->x && x <= this->x + this->width &&
            y >= this->y && y <= this->y + this->height);
}

bool RectF::intersects(const RectF &other) const
{
    return (x < other.x + other.width && x + width > other.x &&
            y < other.y + other.height && y + height > other.y);
}

void RectF::offset(double dx, double dy)
{
    x += dx;
    y += dy;
}

void RectF::offset(const PointF &dpointF)
{
    x += dpointF.getX();
    y += dpointF.getY();
}

void RectF::inflate(double dx, double dy)
{
    width += dx;
    height += dy;
}

void RectF::inflate(const SizeF &dsizeF)
{
    width += dsizeF.getWidth();
    height += dsizeF.getHeight();
}

bool RectF::operator==(const RectF &other) const
{
    return (x == other.x && y == other.y &&
            width == other.width && height == other.height);
}

bool RectF::operator!=(const RectF &other) const
{
    return !(*this == other);
}

RectF::operator Rect() const
{
    return Rect(static_cast<long>(x), static_cast<long>(y),
                 static_cast<long>(width), static_cast<long>(height));
}

std::ostream &operator<<(std::ostream &os, const RectF &rectF)
{
    return os << "{" << PointF(rectF.x, rectF.y) << ", "
              << SizeF(rectF.width, rectF.height) << "}";
}
