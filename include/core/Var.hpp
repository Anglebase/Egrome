#pragma once

#include "./SignalSlots.hpp"

/**
 * @addtogroup 封装变量
 * @{
 */

/**
 * @brief 变量类基类
 * @tparam T 变量类型
 * @note 此类提供变量的基础封装，包括变量值的读取和修改，该基类提供了对变量值的监听，当变量值发生变化时，会触发信号，子类也可以通过重写getter和setter方法来实现变量值的自定义获取和修改。
 */
template <typename T>
class Var
{
private:
    T value_;
signals:
    /**
     * @brief 当变量值发生变化时触发此信号
     * @param value 修改后的变量值
     */
    Signal<void(const T &value)> valueChanged;

public:
    /**
     * @brief 默认构造函数
     */
    Var() = default;
    /**
     * @brief 构造函数
     * @param value 变量初始值
     */
    Var(const T &value) : value_(value) {}
    /**
     * @brief 获取变量值
     * @return 变量值
     * @note 子类可以重写getter方法来实现自定义的变量值获取方式
     */
    virtual T getter() const { return this->value_; }
    /**
     * @brief 设置变量值
     * @param value 变量值
     * @note 子类可以重写setter方法来实现自定义的变量值修改方式
     */
    virtual void setter(const T &value)
    {
        if (value_ != value)
        {
            this->value_ = value;
            this->valueChanged.emit(value_);
        }
    }
    /**
     * @brief 隐式类型转换运算符
     * @return 变量值
     * @note 子类可以重写operator T() const方法来实现自定义的类型转换方式
     * @note 该方法可以使得封装变量具有与基本类型相似的操作符，方便使用
     */
    virtual operator T() const { return this->getter(); }
};

/**
 * @brief 布尔变量类
 * @note 布尔变量类继承自Var类，它封装了布尔类型变量的赋值操作
 */
class Bool : public Var<bool>
{
public:
    Bool() = default;
    Bool(bool value) : Var<bool>(value) {}
    bool operator=(bool value)
    {
        this->setter(value);
        return *this;
    }
};

/**
 * @brief 数值变量类
 * @tparam T 变量类型
 * @note 数值变量类继承自Var类，它封装了浮点数类型变量的赋值操作，包括+=、-=、*=、/=、=
 */
template <typename T>
class Number : public Var<T>
{
public:
    Number() = default;
    Number(T value) : Var<T>(value) {}
    T operator=(T value)
    {
        this->setter(value);
        return *this;
    }
    T operator+=(T value)
    {
        this->setter(this->getter() + value);
        return *this;
    }
    T operator-=(T value)
    {
        this->setter(this->getter() - value);
        return *this;
    }
    T operator*=(T value)
    {
        this->setter(this->getter() * value);
        return *this;
    }
    T operator/=(T value)
    {
        this->setter(this->getter() / value);
        return *this;
    }
};
/**
 * @brief 整数变量类
 * @tparam T 变量类型
 * @note 整数变量类继承自Number类，它封装了整数类型变量的自增、自减、赋值、位运算、移位运算等操作
 */
template <typename T>
class Integer : public Number<T>
{
public:
    Integer() = default;
    Integer(T value) : Number<T>(value) {}

    T operator++()
    {
        this->setter(this->getter() + 1);
        return *this;
    }
    T operator++(int)
    {
        T temp = this->getter();
        this->setter(temp + 1);
        return temp;
    }
    T operator--()
    {
        this->setter(this->getter() - 1);
        return *this;
    }
    T operator--(int)
    {
        T temp = this->getter();
        this->setter(temp - 1);
        return temp;
    }
    T operator%=(T value)
    {
        this->setter(this->getter() % value);
        return *this;
    }
    T operator<<=(T value)
    {
        this->setter(this->getter() << value);
        return *this;
    }
    T operator>>=(T value)
    {
        this->setter(this->getter() >> value);
        return *this;
    }
    T operator&=(T value)
    {
        this->setter(this->getter() & value);
        return *this;
    }
    T operator|=(T value)
    {
        this->setter(this->getter() | value);
        return *this;
    }
    T operator^=(T value)
    {
        this->setter(this->getter() ^ value);
        return *this;
    }
};

/**
 * @addtogroup 预定义封装变量类型
 * @{
 */

using Float = Number<float>;
using Double = Number<double>;
using LongDouble = Number<long double>;

using float32 = Float;
using float64 = Double;
using float128 = LongDouble;

using UnsignedChar = Integer<unsigned char>;
using UnsignedShort = Integer<unsigned short>;
using UnsignedInt = Integer<unsigned int>;
using UnsignedLong = Integer<unsigned long>;
using UnsignedLongLong = Integer<unsigned long long>;

using uint8 = UnsignedChar;
using uint16 = UnsignedShort;
using uint32 = UnsignedLong;
using uint64 = UnsignedLongLong;

using Char = Integer<char>;
using Short = Integer<short>;
using Int = Integer<int>;
using Long = Integer<long>;
using LongLong = Integer<long long>;

using int8 = Char;
using int16 = Short;
using int32 = Long;
using int64 = LongLong;

/** @} */
/** @} */