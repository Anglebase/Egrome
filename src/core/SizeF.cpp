#include "SizeF.h"
#include "Size.h"

SizeF::SizeF(double w, double h) : width_(w), height_(h) {}

double &SizeF::width()
{
    return width_;
}

double &SizeF::height()
{
    return height_;
}

const double &SizeF::width() const
{
    return width_;
}

const double &SizeF::height() const
{
    return height_;
}

bool SizeF::operator==(const SizeF &other) const
{
    return this->width_ == other.width_ && this->height_ == other.height_;
}

bool SizeF::operator!=(const SizeF &other) const
{
    return !(*this == other);
}

SizeF SizeF::operator+(const SizeF &other) const
{
    return SizeF(this->width_ + other.width_, this->height_ + other.height_);
}

SizeF SizeF::operator-(const SizeF &other) const
{
    return SizeF(this->width_ - other.width_, this->height_ - other.height_);
}

SizeF &SizeF::operator+=(const SizeF &other)
{
    return *this = *this + other;
}

SizeF &SizeF::operator-=(const SizeF &other)
{
    return *this = *this - other;
}

SizeF SizeF::operator*(double factor) const
{
    return SizeF(this->width_ * factor, this->height_ * factor);
}

SizeF SizeF::operator/(double factor) const
{
    return SizeF(this->width_ / factor, this->height_ / factor);
}

SizeF &SizeF::operator*=(double factor)
{
    return *this = *this * factor;
}

SizeF &SizeF::operator/=(double factor)
{
    return *this = *this / factor;
}

SizeF::operator Size() const
{
    return Size(static_cast<long>(this->width_), static_cast<long>(this->height_));
}

std::ostream &operator<<(std::ostream &os, const SizeF &sizeF)
{
    return os << "[" << sizeF.width_ << ", " << sizeF.height_ << "]";
}
