#pragma once

#include <iostream>
class PointF;
class SizeF;
class Rect;
/**
 * @brief 矩形类
 */
class RectF
{
private:
    double x;
    double y;
    double width;
    double height;

public:
    /**
     * @brief 构造函数
     * @param x 矩形左上角x坐标
     * @param y 矩形左上角y坐标
     * @param width 矩形宽度
     * @param height 矩形高度
     */
    RectF(double x, double y, double width, double height);

    /**
     * @brief 构造函数
     * @param topLeft 矩形左上角点
     * @param sizeF 矩形大小
     */
    RectF(const PointF &topLeft, const SizeF &sizeF);

    /**
     * @brief 获取矩形左上角坐标
     * @return 矩形左上角坐标
     */
    PointF getTopLeft() const;

    /**
     * @brief 获取矩形右上角坐标
     * @return 矩形右上角坐标
     */
    PointF getTopRight() const;

    /**
     * @brief 获取矩形左下角坐标
     * @return 矩形左下角坐标
     */
    PointF getBottomLeft() const;

    /**
     * @brief 获取矩形右下角坐标
     * @return 矩形右下角坐标
     */
    PointF getBottomRight() const;

    /**
     * @brief 获取矩形左侧x坐标
     * @return 矩形左侧x坐标
     */
    double left() const;

    /**
     * @brief 获取矩形上侧y坐标
     * @return 矩形上侧y坐标
     */
    double top() const;

    /**
     * @brief 获取矩形右侧x坐标
     * @return 矩形右侧x坐标
     */
    double right() const;

    /**
     * @brief 获取矩形下侧y坐标
     * @return 矩形下侧y坐标
     */
    double bottom() const;

    /**
     * @brief 设置矩形左上角坐标
     * @param topLeft 矩形左上角坐标
     */
    void setTopLeft(const PointF &topLeft);
    /**
     * @brief 设置矩形右上角坐标
     * @param topRight 矩形右上角坐标
     */
    void setTopRight(const PointF &topRight);

    /**
     * @brief 设置矩形左下角坐标
     * @param bottomLeft 矩形左下角坐标
     */
    void setBottomLeft(const PointF &bottomLeft);

    /**
     * @brief 设置矩形右下角坐标
     * @param bottomRight 矩形右下角坐标
     */
    void setBottomRight(const PointF &bottomRight);

    /**
     * @brief 获取矩形大小
     * @return 矩形大小
     */
    SizeF getSizeF() const;

    /**
     * @brief 设置矩形大小
     * @param sizeF 矩形大小
     */
    void setSizeF(const SizeF &sizeF);

    /**
     * @brief 判断点是否在矩形内
     * @param pointF 点坐标
     * @return 如果点在矩形内，返回true，否则返回false
     */
    bool contains(const PointF &pointF) const;

    /**
     * @brief 这是一个函数重载，判断点是否在矩形内
     * @param x 点x坐标
     * @param y 点y坐标
     * @return 如果点在矩形内，返回true，否则返回false
     */
    bool contains(double x, double y) const;

    /**
     * @brief 判断两个矩形是否相交
     * @param other 另一个矩形
     * @return 如果相交，返回true，否则返回false
     */
    bool intersects(const RectF &other) const;

    /**
     * @brief 偏移矩形位置
     * @param dx x方向偏移量
     * @param dy y方向偏移量
     */
    void offset(double dx, double dy);

    /**
     * @brief 这是一个函数重载，偏移矩形位置
     * @param dpointF 偏移量
     */
    void offset(const PointF &dpointF);

    /**
     * @brief 增减矩形大小
     * @param dwidth 矩形宽度增减量
     * @param dheight 矩形高度增减量
     */
    void inflate(double dwidth, double dheight);

    /**
     * @brief 这是一个函数重载，增减矩形大小
     * @param dsizeF 矩形大小增减量
     */
    void inflate(const SizeF &dsizeF);

    /**
     * @brief 判断两个矩形是否相同
     * @param other 另一个矩形
     * @return 如果相同，返回true，否则返回false
     */
    bool operator==(const RectF &other) const;

    /**
     * @brief 判断两个矩形是否不同
     * @param other 另一个矩形
     * @return 如果不同，返回true，否则返回false
     */
    bool operator!=(const RectF &other) const;

    /**
     * @brief 针对于流输出的运算符重载
     * @param os 输出流
     * @param rectF 矩形对象
     * @return 输出流
     */
    friend std::ostream &operator<<(std::ostream &os, const RectF &rectF);

    /**
     * @brief 转换为Rect类型
     * @return Rect类型的矩形对象
     */
    operator Rect() const;
};