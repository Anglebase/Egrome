#include "Color.h"
#include <ege.h>

/// 黑色
const Color Color::Black{0x000000};
/// 白色
const Color Color::White{0xFFFFFF};
/// 红色
const Color Color::Red{0xFF0000};
/// 绿色
const Color Color::Green{0x00FF00};
/// 蓝色
const Color Color::Blue{0x0000FF};
/// 灰色
const Color Color::Gray{0x808080};
/// 亮灰色
const Color Color::LightGray{0xC0C0C0};
/// 深灰色
const Color Color::DarkGray{0x404040};
/// 紫色
const Color Color::Purple{0xFF00FF};
/// 黄色
const Color Color::Yellow{0xFFFF00};
/// 青色
const Color Color::Cyan{0x00FEC0};
/// 粉色
const Color Color::Pink{0xFFC0CB};
/// 亮红色
const Color Color::LightRed{0xFFA07A};
/// 亮绿色
const Color Color::LightGreen{0x90EE90};
/// 亮蓝色
const Color Color::LightBlue{0xADD8E6};
/// 亮黄色
const Color Color::LightYellow{0xFFFFE0};
/// 亮青色
const Color Color::LightCyan{0x00FFFF};
/// 亮粉色
const Color Color::LightPink{0xFFB6C1};

Color Color::color_lerp(Color start, Color end, double t)
{
    auto f = [](int a, int b, double t) -> int
    { return a + (b - a) * t; };
    return Color{
        f(start.getRed(), end.getRed(), t),
        f(start.getGreen(), end.getGreen(), t),
        f(start.getBlue(), end.getBlue(), t),
    };
}

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
    this->red = EGEGET_R(rgb);
    this->green = EGEGET_G(rgb);
    this->blue = EGEGET_B(rgb);
}

const Color &Color::operator=(const Color &other)
{
    this->red = other.red;
    this->green = other.green;
    this->blue = other.blue;
    return *this;
}

const Color &Color::operator=(Color &&other)
{
    red = other.red;
    green = other.green;
    blue = other.blue;
    return *this;
}

const Color &Color::operator=(const HSV &hsv)
{
    auto rgb = ege::hsv2rgb(hsv.hue, hsv.saturation, hsv.value);
    red = EGEGET_R(rgb);
    green = EGEGET_G(rgb);
    blue = EGEGET_B(rgb);
    return *this;
}

const Color &Color::operator=(const HSL &hsl)
{
    auto rgb = ege::hsl2rgb(hsl.hue, hsl.saturation, hsl.lightness);
    red = EGEGET_R(rgb);
    green = EGEGET_G(rgb);
    blue = EGEGET_B(rgb);
    return *this;
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

Color operator""_$(unsigned long long hex)
{
    return Color(hex);
}
