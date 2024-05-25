#include "core/Size.h"
#include "core/SizeF.h"

Size::Size(long w, long h) : width(w), height(h) {}

long Size::getWidth() const {
    return this->width;
}

long Size::getHeight() const {
    return this->height;
}

void Size::setWidth(long w)
{
    this->width = w;
}

void Size::setHeight(long h)
{
    this->height = h;
}

bool Size::operator==(const Size& other) const
{
    return this->width == other.width && this->height == other.height;
}

bool Size::operator!=(const Size& other) const
{
    return !(*this == other);
}

Size Size::operator+(const Size &other) const
{
    return Size(this->width + other.width, this->height + other.height);
}

Size Size::operator-(const Size &other) const
{
    return Size(this->width - other.width, this->height - other.height);
}

Size &Size::operator+=(const Size &other)
{
    return *this = *this + other;
}

Size &Size::operator-=(const Size &other)
{
    return *this = *this - other;
}

Size Size::operator*(double factor) const
{
    return Size(static_cast<long>(this->width * factor), static_cast<long>(this->height * factor));
}

Size Size::operator/(double factor) const
{
    return Size(static_cast<long>(this->width / factor), static_cast<long>(this->height / factor));
}

Size &Size::operator*=(double factor)
{
    return *this = *this * factor;
}


Size &Size::operator/=(double factor)
{
    return *this = *this / factor;
}

Size::operator SizeF() const
{
    return SizeF(static_cast<double>(this->width), static_cast<double>(this->height));
}

std::ostream &operator<<(std::ostream &os, const Size &size)
{
    return os << "[" << size.width << ", " << size.height << "]";
}
