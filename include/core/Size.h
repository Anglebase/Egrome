#pragma once

#include <iostream>

class SizeF;
/**
 * @brief 二维尺寸类
 */
class Size
{
private:
    long width_;
    long height_;

public:
    /**
     * @brief 构造函数
     */
    Size(long w = 0, long h = 0);

    long &width();
    long &height();
    const long &width() const;
    const long &height() const;

    /**
     * @brief 判断两个Size是否相同
     * @param other 另一个Size
     * @return 如果相等返回true，否则返回false
     */
    bool operator==(const Size &other) const;

    /**
     * @brief 判断两个Size是否不同
     * @param other 另一个Size
     * @return 如果不同返回true，否则返回false
     */
    bool operator!=(const Size &other) const;

    /**
     * @brief 计算两个Size的和
     * @brief 此函数会对两Size的高度和宽度分别求和，并返回一个新的Size对象
     * @param other 另一个Size
     * @return 两个Size的和
     */
    Size operator+(const Size &other) const;

    /**
     * @brief 计算两个Size的差
     * @brief 此函数会对两Size的高度和宽度分别求差，并返回一个新的Size对象
     * @param other 另一个Size
     * @return 两个Size的差
     */
    Size operator-(const Size &other) const;

    /**
     * @brief +=运算符重载
     * @param other 另一个Size
     * @return Size对象本身
     * @note 计算方式参考 operator+(const Size &other) const
     */
    Size &operator+=(const Size &other);

    /**
     * @brief -=运算符重载
     * @param other 另一个Size
     * @return Size对象本身
     * @note 计算方式参考 operator-(const Size &other) const
     */
    Size &operator-=(const Size &other);

    /**
     * @brief 令Size对象的宽度和高度都乘以一个倍数
     * @param factor 倍数
     * @return 新的Size对象
     */
    Size operator*(double factor) const;

    /**
     * @brief 令Size对象的宽度和高度都除以一个倍数
     * @param factor 倍数
     * @return 新的Size对象
     * @warning 除数不能为0
     */
    Size operator/(double factor) const;

    /**
     * @brief *=运算符重载
     * @param factor 倍数
     * @return Size对象本身
     * @note 计算方式参考 operator*(double factor) const
     */
    Size &operator*=(double factor);

    /**
     * @brief /=运算符重载
     * @param factor 倍数
     * @return Size对象本身
     * @note 计算方式参考 operator/(double factor) const
     * @warning 除数不能为0
     */
    Size &operator/=(double factor);

    /**
     * @brief 针对于流输出的运算符重载
     * @param os 输出流
     * @param size Size 对象
     * @return  输出流
     */
    friend std::ostream &operator<<(std::ostream &os, const Size &size);

    /**
     * @brief 转换为SizeF类型
     * @return SizeF对象
     */
    operator SizeF() const;
};