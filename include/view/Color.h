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
 * @note 该模型中，H 表示色调，S 表示饱和度，V 表示明度
 */
struct HSV
{
    /// 色调，取值范围为 [0, 360]
    float hue;
    /// 饱和度，取值范围为 [0, 1]
    float saturation;
    /// 明度，取值范围为 [0, 1]
    float value;
};

/**
 * @brief HSL (Hue, Saturation, Lightness) 颜色模型
 * @note 该模型中，H 表示色调，S 表示饱和度，L 表示亮度
 */
struct HSL
{
    /// 色调，取值范围为 [0, 360]
    float hue;
    /// 饱和度，取值范围为 [0, 1]
    float saturation;
    /// 亮度，取值范围为 [0, 1]
    float lightness;
};

/**
 * @brief 此类以 RGB 颜色模型对颜色进行存储
 * @note 该类提供了常用颜色的预定义，以及颜色的线性插值函数
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
    static Color lerp(Color start, Color end, double t);

private:
    int red;
    int green;
    int blue;
    int alpha;

public:
    /**
     * @brief 构造函数
     * @param r 红色分量
     * @param g 绿色分量
     * @param b 蓝色分量
     */
    Color(int r, int g, int b, int a = 0xFF);

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
    /**
     * @brief 拷贝构造函数
     * @param other 要拷贝的颜色对象
     */
    Color(const Color &other) = default;
    /**
     * @brief 移动构造函数
     * @param value 要移动的颜色对象
     */
    Color(Color &&value) = default;

    const Color &operator=(const Color &other);
    const Color &operator=(Color &&value);
    const Color &operator=(const HSV &hsv);
    const Color &operator=(const HSL &hsl);
    /**
     * @brief 颜色相等比较
     * @param other 另一个颜色
     * @return 相等返回 true，否则返回 false
     */
    bool operator==(const Color &other) const;
    /**
     * @brief 颜色不等比较
     * @param other 另一个颜色
     * @return 不等返回 true，否则返回 false
     */
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
     * @brief 获取颜色的透明度
     * @return 透明度
     */
    int getAlpha() const;

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
     * @brief 设置颜色的透明度
     * @param a 透明度
     */
    void setAlpha(int a);

    /**
     * @brief 转换为 HSV 颜色模型
     * @return HSV 颜色模型
     * @note 该转换会丢失透明度信息
     */
    operator HSV() const;
    /**
     * @brief 转换为 HSL 颜色模型
     * @return HSL 颜色模型
     * @note 该转换会丢失透明度信息
     */
    operator HSL() const;

    /**
     * @brief 去除aplha通道值
     * @return 去除aplha通道值的颜色对象
     */
    Color withoutAlpha() const;
};

/**
 * @addtogroup 字面量
 * @{
 */
/**
 * @brief 颜色的字面量形式
 * @param hex 颜色的十六进制表示，以0xRRGGBB的形式
 * @return 颜色对象
 */
Color operator""_rgb(unsigned long long hex);
/**
 * @brief 颜色的字面量形式
 * @param hex 颜色的十六进制表示，以0xRRGGBBAA的形式
 * @return 颜色对象
 */
Color operator""_rgba(unsigned long long hex);
/** @} */

/** @} */