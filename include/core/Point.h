#pragma once

#include <iostream>
class PointF;
class Rect;
class RectF;

/**
 * @addtogroup 核心
 * @{
 */

/**
 * @brief 此类定义二维坐标点
 */
class Point
{
    friend class Painter;

private:
    long x_;
    long y_;

public:
    /**
     * @brief 构造函数
     * @param x x坐标
     * @param y y坐标
     */
    Point(long x = 0, long y = 0);

    long &x();
    long &y();
    const long &x() const;
    const long &y() const;

    /**
     * @brief 判断点是否在矩形(Rect)内
     * @param rect 矩形
     * @return 如果点在矩形内返回 \a true ，否则返回 \a false
     * @note 矩形的边界被视为矩形内
     */
    bool inside(const Rect &rect) const;

    /**
     * @brief 这是一个重载，判断点是否在浮点矩形(RectF)内
     * @param rect 矩形
     * @return 如果点在矩形内返回 \a true ，否则返回 \a false
     * @note 矩形的边界被视为矩形内
     */
    bool inside(const RectF &rect) const;

    /**
     * @brief 判断两点是否相同
     * @param other 另一个点
     * @return 如果两点相同返回 \a true ，否则返回 \a false
     */
    bool operator==(const Point &other) const;

    /**
     * @brief 判断两点是否不同
     * @param other 另一个点
     * @return 如果两点不同返回 \a true ，否则返回 \a false
     */
    bool operator!=(const Point &other) const;

    /**
     * @brief 点加法
     * @brief 该函数返回一个新的点，其坐标为两坐标点的x、y分别求和
     * @param other 另一个点
     * @return 点的和
     */
    Point operator+(const Point &other) const;

    /**
     * @brief 点减法
     * @brief 该函数返回一个新的点，其坐标为两坐标点的x、y分别求差
     * @param other 另一个点
     * @return 点的差
     */
    Point operator-(const Point &other) const;

    /**
     * @brief +=运算符重载
     * @note 计算方式参考 operator+(const Point &other) const
     * @param other 另一个点
     * @return 点本身
     */
    Point &operator+=(const Point &other);

    /**
     * @brief -=运算符重载
     * @note 计算方式参考 operator-(const Point &other) const
     * @param other 另一个点
     * @return 点本身
     */
    Point &operator-=(const Point &other);

    /**
     * @brief 针对于流输出的运算符重载
     * @param os 输出流
     * @param p 点
     * @return 输出流
     */
    friend std::ostream &operator<<(std::ostream &os, const Point &p);

    /**
     * @brief 转换为PointF类型
     * @return 转换后的PointF类型
     */
    operator PointF() const;
};

/**
 * @}
 */