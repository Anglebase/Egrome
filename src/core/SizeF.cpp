#include "core/SizeF.h"
#include "core/Size.h"

SizeF::SizeF(double w, double h) : width(w), height(h) {}

double SizeF::getWidth() const
{
    return this->width;
}

double SizeF::getHeight() const
{
    return this->height;
}

void SizeF::setWidth(double w)
{
    this->width = w;
}

void SizeF::setHeight(double h)
{
    this->height = h;
}

bool SizeF::operator==(const SizeF &other) const
{
    return this->width == other.width && this->height == other.height;
}

bool SizeF::operator!=(const SizeF &other) const
{
    return !(*this == other);
}

SizeF SizeF::operator+(const SizeF &other) const
{
    return SizeF(this->width + other.width, this->height + other.height);
}

SizeF SizeF::operator-(const SizeF &other) const
{
    return SizeF(this->width - other.width, this->height - other.height);
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
    return SizeF(this->width * factor, this->height * factor);
}

SizeF SizeF::operator/(double factor) const
{
    return SizeF(this->width / factor, this->height / factor);
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
    return Size(static_cast<long>(this->width), static_cast<long>(this->height));
}

std::ostream &operator<<(std::ostream &os, const SizeF &sizeF)
{
    return os << "[" << sizeF.width << ", " << sizeF.height << "]";
}
