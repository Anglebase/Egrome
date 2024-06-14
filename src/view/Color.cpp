#include "Color.h"
#include <ege.h>

/// 黑色
const Color Color::Black{0x000000_rgb};
/// 白色
const Color Color::White{0xFFFFFF_rgb};
/// 红色
const Color Color::Red{0xFF0000_rgb};
/// 绿色
const Color Color::Green{0x00FF00_rgb};
/// 蓝色
const Color Color::Blue{0x0000FF_rgb};
/// 灰色
const Color Color::Gray{0x808080_rgb};
/// 亮灰色
const Color Color::LightGray{0xC0C0C0_rgb};
/// 深灰色
const Color Color::DarkGray{0x404040_rgb};
/// 紫色
const Color Color::Purple{0xFF00FF_rgb};
/// 黄色
const Color Color::Yellow{0xFFFF00_rgb};
/// 青色
const Color Color::Cyan{0x00FEC0_rgb};
/// 粉色
const Color Color::Pink{0xFFC0CB_rgb};
/// 亮红色
const Color Color::LightRed{0xFFA07A_rgb};
/// 亮绿色
const Color Color::LightGreen{0x90EE90_rgb};
/// 亮蓝色
const Color Color::LightBlue{0xADD8E6_rgb};
/// 亮黄色
const Color Color::LightYellow{0xFFFFE0_rgb};
/// 亮青色
const Color Color::LightCyan{0x00FFFF_rgb};
/// 亮粉色
const Color Color::LightPink{0xFFB6C1_rgb};

Color Color::lerp(Color start, Color end, double t)
{
    auto f = [](int a, int b, double t) -> int
    { return a + (b - a) * t; };
    return Color{
        f(start.getRed(), end.getRed(), t),
        f(start.getGreen(), end.getGreen(), t),
        f(start.getBlue(), end.getBlue(), t),
        f(start.getAlpha(), end.getAlpha(), t),
    };
}

Color::Color(int r, int g, int b, int a) : red(r), green(g), blue(b), alpha(a) {}

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
    this->alpha = other.alpha;
    return *this;
}

const Color &Color::operator=(Color &&other)
{
    red = other.red;
    green = other.green;
    blue = other.blue;
    alpha = other.alpha;
    return *this;
}

const Color &Color::operator=(const HSV &hsv)
{
    auto rgb = ege::hsv2rgb(hsv.hue, hsv.saturation, hsv.value);
    red = EGEGET_R(rgb);
    green = EGEGET_G(rgb);
    blue = EGEGET_B(rgb);
    alpha = 0xFF;
    return *this;
}

const Color &Color::operator=(const HSL &hsl)
{
    auto rgb = ege::hsl2rgb(hsl.hue, hsl.saturation, hsl.lightness);
    red = EGEGET_R(rgb);
    green = EGEGET_G(rgb);
    blue = EGEGET_B(rgb);
    alpha = 0xFF;
    return *this;
}

bool Color::operator==(const Color &other) const
{
    return red == other.red && green == other.green && blue == other.blue && alpha == other.alpha;
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

int Color::getAlpha() const
{
    return this->alpha;
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

void Color::setAlpha(int a)
{
    this->alpha = a;
}

Color::operator HSV() const
{
    HSV hsv;
    ege::rgb2hsv(EGERGBA(red, green, blue, alpha),
                 &hsv.hue, &hsv.saturation, &hsv.value);
    return hsv;
}

Color::operator HSL() const
{
    HSL hsl;
    ege::rgb2hsl(EGERGBA(red, green, blue, alpha),
                 &hsl.hue, &hsl.saturation, &hsl.lightness);
    return hsl;
}

Color Color::withoutAlpha() const
{
    return Color{red, green, blue, 0xFF};
}

Color operator""_rgb(unsigned long long hex)
{
    return Color((hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF, 0xFF);
}

Color operator""_rgba(unsigned long long hex)
{
    return Color((hex >> 24) & 0xFF, (hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF);
}
