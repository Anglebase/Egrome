#pragma once


class Color {
private:
    int red_;
    int green_;
    int blue_;
    int alpha_;

public:
#pragma region HSV修改器
    struct HSV {
    private:
        Color* parent_;
    private:
        // 色相
        struct Hue {
            friend struct HSV;
        private:
            HSV* parent_;
            Hue(HSV* parent) noexcept;
        public:
            float operator=(float value) noexcept;
            operator float() const noexcept;
        };
        // 饱和度
        struct Saturation {
            friend struct HSV;
        private:
            HSV* parent_;
            Saturation(HSV* parent) noexcept;
        public:
            float operator=(float value) noexcept;
            operator float() const noexcept;
        };
        // 亮度
        struct Value {
            friend struct HSV;
        private:
            HSV* parent_;
            Value(HSV* parent) noexcept;
        public:
            float operator=(float value) noexcept;
            operator float() const noexcept;
        };
    private:
        friend class Color;
        HSV(Color* color) noexcept;
        ~HSV() noexcept;
    public:
        Hue hue;
        Saturation saturation;
        Value value;
    }hsv;
#pragma endregion

#pragma region HSL修改器
    struct HSL {
    private:
        Color* parent_;
    private:
        // 色相
        struct Hue {
            friend struct HSL;
        private:
            HSL* parent_;
            Hue(HSL* parent) noexcept;
        public:
            float operator=(float value) noexcept;
            operator float() const noexcept;
        };
        // 饱和度
        struct Saturation {
            friend struct HSL;
        private:
            HSL* parent_;
            Saturation(HSL* parent) noexcept;
        public:
            float operator=(float value) noexcept;
            operator float() const noexcept;
        };
        // 亮度
        struct Lightness {
            friend struct HSL;
        private:
            HSL* parent_;
            Lightness(HSL* parent) noexcept;
        public:
            float operator=(float value) noexcept;
            operator float() const noexcept;
        };
    private:
        friend class Color;
        HSL(Color* color) noexcept;
        ~HSL() noexcept;
    public:
        Hue hue;
        Saturation saturation;
        Lightness lightness;
    }hsl;
#pragma endregion

public:
    static Color lerp(const Color& a, const Color& b, double t) noexcept;

public:
    Color(int r, int g, int b, int a = 255) noexcept;
    ~Color() noexcept;

    int& red() noexcept;
    int& green() noexcept;
    int& blue() noexcept;
    int& alpha() noexcept;

    const int& red() const noexcept;
    const int& green() const noexcept;
    const int& blue() const noexcept;
    const int& alpha() const noexcept;

    Color withoutAlpha() const noexcept;
    Color gray() const noexcept;

    bool operator==(const Color& other) const noexcept;
    bool operator!=(const Color& other) const noexcept;
};

Color operator""_rgb(unsigned long long int hex) noexcept;
Color operator""_rgba(unsigned long long int hex) noexcept;