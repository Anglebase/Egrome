#pragma once
/**
 * @file SizeF.h
 * @brief 二维尺寸类
*/
#include <iostream>

class Size;
/**
 * @addtogroup 核心
 * @brief 核心模块
 * @details 该模块包含了一些基础类
 * @{
 */
/**
 * @brief 二维尺寸类
 */
class SizeF
{
private:
    double width_;
    double height_;

public:
    /**
     * @brief 构造函数
     */
    SizeF(double w = 0, double h = 0);

    double &width();
    double &height();
    const double &width() const;
    const double &height() const;

    /**
     * @brief 判断两个SizeF是否相同
     * @param other 另一个SizeF
     * @return 如果相等返回true，否则返回false
     */
    bool operator==(const SizeF &other) const;

    /**
     * @brief 判断两个SizeF是否不同
     * @param other 另一个SizeF
     * @return 如果不同返回true，否则返回false
     */
    bool operator!=(const SizeF &other) const;

    /**
     * @brief 计算两个SizeF的和
     * @brief 此函数会对两SizeF的高度和宽度分别求和，并返回一个新的SizeF对象
     * @param other 另一个SizeF
     * @return 两个SizeF的和
     */
    SizeF operator+(const SizeF &other) const;

    /**
     * @brief 计算两个SizeF的差
     * @brief 此函数会对两SizeF的高度和宽度分别求差，并返回一个新的SizeF对象
     * @param other 另一个SizeF
     * @return 两个SizeF的差
     */
    SizeF operator-(const SizeF &other) const;

    /**
     * @brief +=运算符重载
     * @param other 另一个SizeF
     * @return SizeF对象本身
     * @note 计算方式参考 operator+(const SizeF &other) const
     */
    SizeF &operator+=(const SizeF &other);

    /**
     * @brief -=运算符重载
     * @param other 另一个SizeF
     * @return SizeF对象本身
     * @note 计算方式参考 operator-(const SizeF &other) const
     */
    SizeF &operator-=(const SizeF &other);

    /**
     * @brief 令SizeF对象的宽度和高度都乘以一个倍数
     * @param factor 倍数
     * @return 新的SizeF对象
     */
    SizeF operator*(double factor) const;

    /**
     * @brief 令SizeF对象的宽度和高度都除以一个倍数
     * @param factor 倍数
     * @return 新的SizeF对象
     * @warning 除数不能为0
     */
    SizeF operator/(double factor) const;

    /**
     * @brief *=运算符重载
     * @param factor 倍数
     * @return SizeF对象本身
     * @note 计算方式参考 operator*(double factor) const
     */
    SizeF &operator*=(double factor);

    /**
     * @brief /=运算符重载
     * @param factor 倍数
     * @return SizeF对象本身
     * @note 计算方式参考 operator/(double factor) const
     * @warning 除数不能为0
     */
    SizeF &operator/=(double factor);

    /**
     * @brief 针对于流输出的运算符重载
     * @param os 输出流
     * @param sizeF SizeF 对象
     * @return  输出流
     */
    friend std::ostream &operator<<(std::ostream &os, const SizeF &sizeF);

    /**
     * @brief 转换为Size类型
     * @return Size对象
     */
    operator Size() const;
};
/** @} */