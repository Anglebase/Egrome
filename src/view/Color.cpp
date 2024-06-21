#include "Color.h"

#include <ege.h>

Color Color::lerp(const Color& a, const Color& b, double t) noexcept {
    auto line_lerp = [](int a, int b, double t) { return a + (b - a) * t; };
    return Color{
        line_lerp(a.red_, b.red_, t),
        line_lerp(a.green_, b.green_, t),
        line_lerp(a.blue_, b.blue_, t),
        line_lerp(a.alpha_, b.alpha_, t),
    };
}

Color::HSV::HSV(Color* color) noexcept
    : parent_(color), hue(this), saturation(this), value(this) {}
Color::HSV::~HSV() noexcept = default;

Color::HSL::HSL(Color* color) noexcept
    : parent_(color), hue(this), saturation(this), lightness(this) {}
Color::HSL::~HSL() noexcept = default;

Color::Color(int r, int g, int b, int a) noexcept
    : red_(r), green_(g), blue_(b), alpha_(a), hsv(this), hsl(this) {}

Color::~Color() noexcept = default;

int& Color::red() noexcept { return this->red_; }
int& Color::green() noexcept { return this->green_; }
int& Color::blue() noexcept { return this->blue_; }
int& Color::alpha() noexcept { return this->alpha_; }

const int& Color::red() const noexcept { return this->red_; }
const int& Color::green() const noexcept { return this->green_; }
const int& Color::blue() const noexcept { return this->blue_; }
const int& Color::alpha() const noexcept { return this->alpha_; }

Color Color::withoutAlpha() const noexcept {
    return Color(this->red_, this->green_, this->blue_, 255);
}

Color Color::gray() const noexcept {
    auto gray = ege::rgb2gray(EGEARGB(this->alpha_, this->red_, this->green_, this->blue_));
    return Color(EGEGET_R(gray), EGEGET_G(gray), EGEGET_B(gray), EGEGET_A(gray));
}

bool Color::operator==(const Color& other) const noexcept {
    return this->red_ == other.red_ && this->green_ == other.green_ &&
        this->blue_ == other.blue_ && this->alpha_ == other.alpha_;
}

bool Color::operator!=(const Color& other) const noexcept {
    return !(*this == other);
}

Color operator""_rgb(unsigned long long int hex) noexcept {
    return Color{
        static_cast<int>((hex >> 16) & 0xFF),
        static_cast<int>((hex >> 8) & 0xFF),
        static_cast<int>(hex & 0xFF),
        255
    };
}

Color operator""_rgba(unsigned long long int hex) noexcept {
    return Color{
        static_cast<int>((hex >> 24) & 0xFF),
        static_cast<int>((hex >> 16) & 0xFF),
        static_cast<int>((hex >> 8) & 0xFF),
        static_cast<int>(hex & 0xFF)
    };
}

Color::HSV::Hue::Hue(HSV* parent) noexcept
    : parent_(parent) {}

float Color::HSV::Hue::operator=(float value) noexcept {
    float hsv[3];
    ege::rgb2hsv(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsv[0], &hsv[1], &hsv[2]);
    hsv[0] = value;
    auto rgba = ege::hsv2rgb(hsv[0], hsv[1], hsv[2]);
    this->parent_->parent_->red_ = EGEGET_R(rgba);
    this->parent_->parent_->green_ = EGEGET_G(rgba);
    this->parent_->parent_->blue_ = EGEGET_B(rgba);
    return value;
}

Color::HSV::Hue::operator float() const noexcept {
    float hsv[3];
    ege::rgb2hsv(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsv[0], &hsv[1], &hsv[2]);
    return hsv[0];
}

Color::HSV::Saturation::Saturation(HSV* parent) noexcept
    : parent_(parent) {}

float Color::HSV::Saturation::operator=(float value) noexcept {
    float hsv[3];
    ege::rgb2hsv(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsv[0], &hsv[1], &hsv[2]);
    hsv[1] = value;
    auto rgba = ege::hsv2rgb(hsv[0], hsv[1], hsv[2]);
    this->parent_->parent_->red_ = EGEGET_R(rgba);
    this->parent_->parent_->green_ = EGEGET_G(rgba);
    this->parent_->parent_->blue_ = EGEGET_B(rgba);
    return value;
}

Color::HSV::Saturation::operator float() const noexcept {
    float hsv[3];
    ege::rgb2hsv(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsv[0], &hsv[1], &hsv[2]);
    return hsv[1];
}

Color::HSV::Value::Value(HSV* parent) noexcept
    : parent_(parent) {}

float Color::HSV::Value::operator=(float value) noexcept {
    float hsv[3];
    ege::rgb2hsv(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsv[0], &hsv[1], &hsv[2]);
    hsv[2] = value;
    auto rgba = ege::hsv2rgb(hsv[0], hsv[1], hsv[2]);
    this->parent_->parent_->red_ = EGEGET_R(rgba);
    this->parent_->parent_->green_ = EGEGET_G(rgba);
    this->parent_->parent_->blue_ = EGEGET_B(rgba);
    return value;
}

Color::HSV::Value::operator float() const noexcept {
    float hsv[3];
    ege::rgb2hsv(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsv[0], &hsv[1], &hsv[2]);
    return hsv[2];
}

Color::HSL::Hue::Hue(HSL* parent) noexcept
    : parent_(parent) {}

float Color::HSL::Hue::operator=(float value) noexcept {
    float hsl[3];
    ege::rgb2hsl(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsl[0], &hsl[1], &hsl[2]);
    hsl[0] = value;
    auto rgba = ege::hsl2rgb(hsl[0], hsl[1], hsl[2]);
    this->parent_->parent_->red_ = EGEGET_R(rgba);
    this->parent_->parent_->green_ = EGEGET_G(rgba);
    this->parent_->parent_->blue_ = EGEGET_B(rgba);
    return value;
}

Color::HSL::Hue::operator float() const noexcept {
    float hsl[3];
    ege::rgb2hsl(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsl[0], &hsl[1], &hsl[2]);
    return hsl[0];
}

Color::HSL::Saturation::Saturation(HSL* parent) noexcept
    : parent_(parent) {}

float Color::HSL::Saturation::operator=(float value) noexcept {
    float hsl[3];
    ege::rgb2hsl(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsl[0], &hsl[1], &hsl[2]);
    hsl[1] = value;
    auto rgba = ege::hsl2rgb(hsl[0], hsl[1], hsl[2]);
    this->parent_->parent_->red_ = EGEGET_R(rgba);
    this->parent_->parent_->green_ = EGEGET_G(rgba);
    this->parent_->parent_->blue_ = EGEGET_B(rgba);
    return value;
}

Color::HSL::Saturation::operator float() const noexcept {
    float hsl[3];
    ege::rgb2hsl(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsl[0], &hsl[1], &hsl[2]);
    return hsl[1];
}

Color::HSL::Lightness::Lightness(HSL* parent) noexcept
    : parent_(parent) {}

float Color::HSL::Lightness::operator=(float value) noexcept {
    float hsl[3];
    ege::rgb2hsl(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsl[0], &hsl[1], &hsl[2]);
    hsl[2] = value;
    auto rgba = ege::hsl2rgb(hsl[0], hsl[1], hsl[2]);
    this->parent_->parent_->red_ = EGEGET_R(rgba);
    this->parent_->parent_->green_ = EGEGET_G(rgba);
    this->parent_->parent_->blue_ = EGEGET_B(rgba);
    return value;
}

Color::HSL::Lightness::operator float() const noexcept {
    float hsl[3];
    ege::rgb2hsl(
        EGEARGB(this->parent_->parent_->alpha_,
            this->parent_->parent_->red_,
            this->parent_->parent_->green_,
            this->parent_->parent_->blue_),
        &hsl[0], &hsl[1], &hsl[2]);
    return hsl[2];
}