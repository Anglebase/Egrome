/**
 * @file Point.h
 * @author Anglebase[GitHub]
 * @brief 定义点类
 */

#pragma once
#include "./Object.h"

class Rect;
/**
 * @brief 点类
 */
class Point : public Object
{
private:
    float x_;
    float y_;

public:
    Point(float x = 0, float y = 0) noexcept;
    ~Point() noexcept;

    float &x() noexcept;
    float &y() noexcept;
    const float &x() const noexcept;
    const float &y() const noexcept;

    Point &operator=(const Point &other) noexcept;
    Point operator+(const Point &other) const noexcept;
    Point operator-(const Point &other) const noexcept;
    Point operator*(const float &scale) const noexcept;
    Point operator/(const float &scale) const noexcept;
    Point &operator+=(const Point &other) noexcept;
    Point &operator-=(const Point &other) noexcept;
    Point &operator*=(const float &scale) noexcept;
    Point &operator/=(const float &scale) noexcept;

    bool operator==(const Point &other) const noexcept;
    bool operator!=(const Point &other) const noexcept;

    /**
     * @brief 计算两点之间的距离
     * @param other 另一个点
     * @return 两点之间的距离
     */
    float distance(const Point &other) const noexcept;
    /**
     * @brief 判断点是否在矩形内，不包含边界
     * @param rect 矩形
     * @return 点是否在矩形内
     */
    bool inside(const Rect &rect) const noexcept;
};