#include "Rect.h"
#include "Point.h"
#include "Size.h"
#include "Rect.h"

Rect::Rect(float x, float y, float width, float height)
    : x_(x), y_(y), width_(width), height_(height) {}

Rect::Rect(const Point &topLeft, const Size &size)
    : x_(topLeft.x()), y_(topLeft.y()), width_(size.width()), height_(size.height()) {}

float &Rect::x() { return x_; }
float &Rect::y() { return y_; }
float &Rect::width() { return width_; }
float &Rect::height() { return height_; }

const float &Rect::x() const { return x_; }
const float &Rect::y() const { return y_; }
const float &Rect::width() const { return width_; }
const float &Rect::height() const { return height_; }

Point Rect::getTopLeft() const
{
    return Point(x_, y_);
}

Point Rect::getTopRight() const
{
    return Point(x_ + width_, y_);
}

Point Rect::getBottomLeft() const
{
    return Point(x_, y_ + height_);
}

Point Rect::getBottomRight() const
{
    return Point(x_ + width_, y_ + height_);
}

float Rect::left() const
{
    return this->x_;
}

float Rect::top() const
{
    return this->y_;
}

float Rect::right() const
{
    return this->x_ + this->width_;
}

float Rect::bottom() const
{
    return this->y_ + this->height_;
}

void Rect::setTopLeft(const Point &topLeft)
{
    this->x_ = topLeft.x();
    this->y_ = topLeft.y();
}

void Rect::setTopRight(const Point &topRight)
{
    this->x_ = topRight.x() - this->width_;
    this->y_ = topRight.y();
}

void Rect::setBottomLeft(const Point &bottomLeft)
{
    this->x_ = bottomLeft.x();
    this->y_ = bottomLeft.y() - this->height_;
}

void Rect::setBottomRight(const Point &bottomRight)
{
    this->x_ = bottomRight.x() - this->width_;
    this->y_ = bottomRight.y() - this->height_;
}

Size Rect::getSize() const
{
    return Size(width_, height_);
}

void Rect::setSize(const Size &size)
{
    this->width_ = size.width();
    this->height_ = size.height();
}

bool Rect::contains(const Point &point) const
{
    // std::cout << *this << " | " << point << std::endl;
    return (point.x() > x_ && point.x() < x_ + width_ &&
            point.y() > y_ && point.y() < y_ + height_);
}

bool Rect::contains(float x, float y) const
{
    return (x > this->x_ && x < this->x_ + this->width_ &&
            y > this->y_ && y < this->y_ + this->height_);
}

bool Rect::intersects(const Rect &other) const
{
    return (x_ < other.x_ + other.width_ && x_ + width_ > other.x_ &&
            y_ < other.y_ + other.height_ && y_ + height_ > other.y_);
}

void Rect::offset(float dx, float dy)
{
    x_ += dx;
    y_ += dy;
}

void Rect::offset(const Point &dpoint)
{
    x_ += dpoint.x();
    y_ += dpoint.y();
}

void Rect::inflate(float dx, float dy)
{
    width_ += dx;
    height_ += dy;
}

void Rect::inflate(const Size &dsize)
{
    width_ += dsize.width();
    height_ += dsize.height();
}

bool Rect::operator==(const Rect &other) const
{
    return (x_ == other.x_ && y_ == other.y_ &&
            width_ == other.width_ && height_ == other.height_);
}

bool Rect::operator!=(const Rect &other) const
{
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const Rect &rect)
{
    return os << "{" << Point(rect.x_, rect.y_) << ", "
              << Size(rect.width_, rect.height_) << "}";
}

Rect Rect::adjusted(float dleft, float dtop, float dright, float dbottom) const
{
    return Rect{
        x_ + dleft,
        y_ + dtop,
        width_ - dleft + dright,
        height_ - dtop + dbottom,
    };
}

Rect Rect::centerWith(const Size &size) const
{
    return Rect{
        x_ + (width_ - size.width()) / 2,
        y_ + (height_ - size.height()) / 2,
        size.width(),
        size.height(),
    };
}

Point Rect::center() const
{
    return Point(x_ + width_ / 2, y_ + height_ / 2);
}
