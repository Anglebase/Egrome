#pragma once

#include "../core/Object.h"

/**
 * @brief 颜色类
 */
class Color final : public Object {
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
        Hue hue; /// @brief 色相
        Saturation saturation; /// @brief 饱和度
        Value value; /// @brief 亮度
    }hsv; /// @brief HSV颜色修改器
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
        Hue hue; /// @brief 色相
        Saturation saturation; /// @brief 饱和度
        Lightness lightness; /// @brief 亮度
    }hsl; /// @brief HSL颜色修改器
#pragma endregion

public:
    /**
     * @brief 对于颜色的线性插值函数
     */
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

    /**
     * @brief 获取移除了alpha通道的颜色
     * @return 移除了alpha通道的颜色
     */
    Color withoutAlpha() const noexcept;
    /**
     * @brief 获取灰度颜色
     * @return 灰度颜色
     */
    Color gray() const noexcept;

    bool operator==(const Color& other) const noexcept;
    bool operator!=(const Color& other) const noexcept;
};

/**
 * @brief 将不带alpha通道的十六进制颜色码转换为Color对象
 * @param hex 十六进制颜色码
 * @return Color对象
 */
Color operator""_rgb(unsigned long long int hex) noexcept;
/**
 * @brief 将带alpha通道的十六进制颜色码转换为Color对象
 * @param hex 十六进制颜色码
 * @return Color对象
 */
Color operator""_rgba(unsigned long long int hex) noexcept;