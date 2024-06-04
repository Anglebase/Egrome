#pragma once

/**
 * @file Color.h
 * @brief 颜色类
 */

/**
 * @addtogroup 视图
 * @{
 */

/**
 * @brief HSV (Hue, Saturation, Value) 颜色模型
 */
struct HSV
{
    float hue;
    float saturation;
    float value;
};

/**
 * @brief HSL (Hue, Saturation, Lightness) 颜色模型
 */
struct HSL
{
    float hue;
    float saturation;
    float lightness;
};

/**
 * @brief 此类以 RGB 颜色模型对颜色进行存储
 */
class Color
{
    friend class Painter;

public:
    /**
     * @brief 常用颜色
     * @addtogroup 常用颜色
     * @{
     */

    /// 黑色
    static const Color Black;
    /// 白色
    static const Color White;
    /// 红色
    static const Color Red;
    /// 绿色
    static const Color Green;
    /// 蓝色
    static const Color Blue;
    /// 灰色
    static const Color Gray;
    /// 亮灰色
    static const Color LightGray;
    /// 深灰色
    static const Color DarkGray;
    /// 紫色
    static const Color Purple;
    /// 黄色
    static const Color Yellow;
    /// 青色
    static const Color Cyan;
    /// 粉色
    static const Color Pink;
    /// 亮红色
    static const Color LightRed;
    /// 亮绿色
    static const Color LightGreen;
    /// 亮蓝色
    static const Color LightBlue;
    /// 亮黄色
    static const Color LightYellow;
    /// 亮青色
    static const Color LightCyan;
    /// 亮粉色
    static const Color LightPink;




    /** @} */

    /**
     * @brief 颜色的线性插值函数
     * @param start 起始值
     * @param end 终止值
     * @param t 插值比例，取值范围为 [0, 1]
     * @return 插值结果
     */
    static Color color_lerp(Color start, Color end, double t);

private:
    int red;
    int green;
    int blue;

public:
    /**
     * @brief 构造函数
     * @param r 红色分量
     * @param g 绿色分量
     * @param b 蓝色分量
     */
    Color(int r, int g, int b);

    /**
     * @brief 构造函数
     * @param hex 颜色的十六进制表示，以0xRRGGBB的形式，如 0xFF0000 表示红色，0x00FF00 表示绿色，0x0000FF 表示蓝色
     */
    Color(long hex);

    /**
     * @brief 以 HSV 颜色模型构造
     * @param hsv HSV 颜色模型
     */
    Color(const HSV &hsv);

    /**
     * @brief 以 HSL 颜色模型构造
     * @param hsl HSL 颜色模型
     */
    Color(const HSL &hsl);

    Color(const Color &other) = default;
    const Color &operator=(const Color &other);
    const Color &operator=(Color &&value);
    const Color &operator=(const HSV &hsv);
    const Color &operator=(const HSL &hsl);

    bool operator==(const Color &other) const;
    bool operator!=(const Color &other) const;

    /**
     * @brief 获取颜色的红色分量
     * @return 红色分量
     */
    int getRed() const;
    /**
     * @brief 获取颜色的绿色分量
     * @return 绿色分量
     */
    int getGreen() const;
    /**
     * @brief 获取颜色的蓝色分量
     * @return 蓝色分量
     */
    int getBlue() const;
    /**
     * @brief 获取颜色的十六进制表示
     * @return 颜色的十六进制表示，以0xRRGGBB的形式
     */
    long getHex() const;

    /**
     * @brief 设置颜色的红色分量
     * @param r 红色分量
     */
    void setRed(int r);
    /**
     * @brief 设置颜色的绿色分量
     * @param g 绿色分量
     */
    void setGreen(int g);
    /**
     * @brief 设置颜色的蓝色分量
     * @param b 蓝色分量
     */
    void setBlue(int b);
    /**
     * @brief 设置颜色的十六进制表示
     * @param hex 颜色的十六进制表示，以0xRRGGBB的形式
     */
    void setHex(long hex);

    /**
     * @brief 转换为 HSV 颜色模型
     * @return HSV 颜色模型
     */
    operator HSV() const;
    /**
     * @brief 转换为 HSL 颜色模型
     * @return HSL 颜色模型
     */
    operator HSL() const;
};

/**
 * @brief 颜色的字面量形式
 * @param hex 十六进制颜色
 * @return 颜色对象
 * @note 该函数的作用是方便地用颜色字面量来表示颜色，例如：
 * @code
 * auto w = 0xFFFFFF_$; // 白色
 * auto r = 0xFF0000_$; // 红色
 * auto g = 0x00FF00_$; // 绿色
 * @endcode
 * @see Color
 */
Color operator""_$(unsigned long long hex);

/** @} */