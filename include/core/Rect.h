#pragma once

#include <iostream>
class Point;
class Size;
class RectF;
/**
 * @brief 矩形类
 */
class Rect
{
private:
    long x;
    long y;
    long width;
    long height;

public:
    /**
     * @brief 构造函数
     * @param x 矩形左上角x坐标
     * @param y 矩形左上角y坐标
     * @param width 矩形宽度
     * @param height 矩形高度
     */
    Rect(long x, long y, long width, long height);

    /**
     * @brief 构造函数
     * @param topLeft 矩形左上角点
     * @param size 矩形大小
     */
    Rect(const Point &topLeft, const Size &size);

    /**
     * @brief 获取矩形左上角坐标
     * @return 矩形左上角坐标
     */
    Point getTopLeft() const;

    /**
     * @brief 获取矩形右上角坐标
     * @return 矩形右上角坐标
     */
    Point getTopRight() const;

    /**
     * @brief 获取矩形左下角坐标
     * @return 矩形左下角坐标
     */
    Point getBottomLeft() const;

    /**
     * @brief 获取矩形右下角坐标
     * @return 矩形右下角坐标
     */
    Point getBottomRight() const;

    /**
     * @brief 获取矩形左侧x坐标
     * @return 矩形左侧x坐标
     */
    long left() const;
    
    /**
     * @brief 获取矩形上侧y坐标
     * @return 矩形上侧y坐标
     */
    long top() const;

    /**
     * @brief 获取矩形右侧x坐标
     * @return 矩形右侧x坐标
     */
    long right() const;

    /**
     * @brief 获取矩形下侧y坐标
     * @return 矩形下侧y坐标
     */
    long bottom() const;

    /**
     * @brief 设置矩形左上角坐标
     * @param topLeft 矩形左上角坐标
     */
    void setTopLeft(const Point &topLeft);
    /**
     * @brief 设置矩形右上角坐标
     * @param topRight 矩形右上角坐标
     */
    void setTopRight(const Point &topRight);

    /**
     * @brief 设置矩形左下角坐标
     * @param bottomLeft 矩形左下角坐标
     */
    void setBottomLeft(const Point &bottomLeft);

    /**
     * @brief 设置矩形右下角坐标
     * @param bottomRight 矩形右下角坐标
     */
    void setBottomRight(const Point &bottomRight);

    /**
     * @brief 获取矩形大小
     * @return 矩形大小
     */
    Size getSize() const;

    /**
     * @brief 设置矩形大小
     * @param size 矩形大小
     */
    void setSize(const Size &size);

    /**
     * @brief 判断点是否在矩形内
     * @param point 点坐标
     * @return 如果点在矩形内，返回true，否则返回false
     */
    bool contains(const Point &point) const;

    /**
     * @brief 这是一个函数重载，判断点是否在矩形内
     * @param x 点x坐标
     * @param y 点y坐标
     * @return 如果点在矩形内，返回true，否则返回false
     */
    bool contains(long x, long y) const;

    /**
     * @brief 判断两个矩形是否相交
     * @param other 另一个矩形
     * @return 如果相交，返回true，否则返回false
     */
    bool intersects(const Rect &other) const;

    /**
     * @brief 偏移矩形位置
     * @param dx x方向偏移量
     * @param dy y方向偏移量
     */
    void offset(long dx, long dy);

    /**
     * @brief 这是一个函数重载，偏移矩形位置
     * @param dpoint 偏移量
     */
    void offset(const Point &dpoint);

    /**
     * @brief 增减矩形大小
     * @param dwidth 矩形宽度增减量
     * @param dheight 矩形高度增减量
     */
    void inflate(long dwidth, long dheight);

    /**
     * @brief 这是一个函数重载，增减矩形大小
     * @param dsize 矩形大小增减量
     */
    void inflate(const Size &dsize);

    /**
     * @brief 判断两个矩形是否相同
     * @param other 另一个矩形
     * @return 如果相同，返回true，否则返回false
     */
    bool operator==(const Rect &other) const;

    /**
     * @brief 判断两个矩形是否不同
     * @param other 另一个矩形
     * @return 如果不同，返回true，否则返回false
     */
    bool operator!=(const Rect &other) const;

    /**
     * @brief 针对于流输出的运算符重载
     * @param os 输出流
     * @param rect 矩形对象
     * @return 输出流
     */
    friend std::ostream &operator<<(std::ostream &os, const Rect &rect);

    /**
     * @brief 转换为RectF类型
     * @return RectF类型的矩形对象
     */
    operator RectF() const;
};