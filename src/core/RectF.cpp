#include "RectF.h"
#include "PointF.h"
#include "SizeF.h"
#include "Rect.h"

RectF::RectF(double x, double y, double width, double height)
    : x_(x), y_(y), width_(width), height_(height) {}

RectF::RectF(const PointF &topLeft, const SizeF &sizeF)
    : x_(topLeft.x()), y_(topLeft.y()), width_(sizeF.width()), height_(sizeF.height()) {}

double &RectF::x() { return x_; }
double &RectF::y() { return y_; }
double &RectF::width() { return width_; }
double &RectF::height() { return height_; }

const double &RectF::x() const { return x_; }
const double &RectF::y() const { return y_; }
const double &RectF::width() const { return width_; }
const double &RectF::height() const { return height_; }

PointF RectF::getTopLeft() const
{
    return PointF(x_, y_);
}

PointF RectF::getTopRight() const
{
    return PointF(x_ + width_, y_);
}

PointF RectF::getBottomLeft() const
{
    return PointF(x_, y_ + height_);
}

PointF RectF::getBottomRight() const
{
    return PointF(x_ + width_, y_ + height_);
}

double RectF::left() const
{
    return this->x_;
}

double RectF::top() const
{
    return this->y_;
}

double RectF::right() const
{
    return this->x_ + this->width_;
}

double RectF::bottom() const
{
    return this->y_ + this->height_;
}

void RectF::setTopLeft(const PointF &topLeft)
{
    this->x_ = topLeft.x();
    this->y_ = topLeft.y();
}

void RectF::setTopRight(const PointF &topRight)
{
    this->x_ = topRight.x() - this->width_;
    this->y_ = topRight.y();
}

void RectF::setBottomLeft(const PointF &bottomLeft)
{
    this->x_ = bottomLeft.x();
    this->y_ = bottomLeft.y() - this->height_;
}

void RectF::setBottomRight(const PointF &bottomRight)
{
    this->x_ = bottomRight.x() - this->width_;
    this->y_ = bottomRight.y() - this->height_;
}

SizeF RectF::getSizeF() const
{
    return SizeF(width_, height_);
}

void RectF::setSizeF(const SizeF &sizeF)
{
    this->width_ = sizeF.width();
    this->height_ = sizeF.height();
}

bool RectF::contains(const PointF &pointF) const
{
    return (pointF.x() >= x_ && pointF.x() <= x_ + width_ &&
            pointF.y() >= y_ && pointF.y() <= y_ + height_);
}

bool RectF::contains(double x, double y) const
{
    return (x >= this->x_ && x <= this->x_ + this->width_ &&
            y >= this->y_ && y <= this->y_ + this->height_);
}

bool RectF::intersects(const RectF &other) const
{
    return (x_ < other.x_ + other.width_ && x_ + width_ > other.x_ &&
            y_ < other.y_ + other.height_ && y_ + height_ > other.y_);
}

void RectF::offset(double dx, double dy)
{
    x_ += dx;
    y_ += dy;
}

void RectF::offset(const PointF &dpointF)
{
    x_ += dpointF.x();
    y_ += dpointF.y();
}

void RectF::inflate(double dx, double dy)
{
    width_ += dx;
    height_ += dy;
}

void RectF::inflate(const SizeF &dsizeF)
{
    width_ += dsizeF.width();
    height_ += dsizeF.height();
}

bool RectF::operator==(const RectF &other) const
{
    return (x_ == other.x_ && y_ == other.y_ &&
            width_ == other.width_ && height_ == other.height_);
}

bool RectF::operator!=(const RectF &other) const
{
    return !(*this == other);
}

RectF::operator Rect() const
{
    return Rect(static_cast<long>(x_), static_cast<long>(y_),
                static_cast<long>(width_), static_cast<long>(height_));
}

std::ostream &operator<<(std::ostream &os, const RectF &rectF)
{
    return os << "{" << PointF(rectF.x_, rectF.y_) << ", "
              << SizeF(rectF.width_, rectF.height_) << "}";
}
