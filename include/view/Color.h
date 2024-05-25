#pragma once

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