#include "Color.h"
#include <ege.h>

Color::Color(int r, int g, int b) : red(r), green(g), blue(b) {}

Color::Color(long hex)
    : red((hex >> 16) & 0xFF), green((hex >> 8) & 0xFF), blue(hex & 0xFF) {}

Color::Color(const HSV &hsv)
{
    auto rgb = ege::hsv2rgb(hsv.hue, hsv.saturation, hsv.value);
    red = EGEGET_R(rgb);
    green = EGEGET_G(rgb);
    blue = EGEGET_B(rgb);
}

Color::Color(const HSL &hsl)
{
    auto rgb = ege::hsl2rgb(hsl.hue, hsl.saturation, hsl.lightness);
    red = EGEGET_R(rgb);
    green = EGEGET_G(rgb);
    blue = EGEGET_B(rgb);
}

bool Color::operator==(const Color &other) const
{
    return red == other.red && green == other.green && blue == other.blue;
}

bool Color::operator!=(const Color &other) const
{
    return !(*this == other);
}

int Color::getRed() const
{
    return red;
}

int Color::getGreen() const
{
    return green;
}

int Color::getBlue() const
{
    return blue;
}

long Color::getHex() const
{
    return (red << 16) | (green << 8) | blue;
}

void Color::setRed(int r)
{
    red = r;
}

void Color::setGreen(int g)
{
    green = g;
}

void Color::setBlue(int b)
{
    blue = b;
}

void Color::setHex(long hex)
{
    red = (hex >> 16) & 0xFF;
    green = (hex >> 8) & 0xFF;
    blue = hex & 0xFF;
}

Color::operator HSV() const
{
    HSV hsv;
    ege::rgb2hsv(EGERGB(red, green, blue),
                 &hsv.hue, &hsv.saturation, &hsv.value);
    return hsv;
}

Color::operator HSL() const
{
    HSL hsl;
    ege::rgb2hsl(EGERGB(red, green, blue),
                 &hsl.hue, &hsl.saturation, &hsl.lightness);
    return hsl;
}
