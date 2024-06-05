#pragma once

#include "./SignalSlots.hpp"

/**
 * @brief 可监测变量类
 * @tparam T 变量类型
 */
template <typename T>
class Var
{
private:
    T value_;

signals:
    /**
     * @brief 变量值改变信号，当变量值改变时发出此信号
     * @param value 变化后的变量值
     */
    Signal<void(T value)> valueChanged;

public:
    /**
     * @brief 默认构造函数
     */
    Var() : value_() {}
    /**
     * @brief 构造函数，初始化变量值为传入值
     * @param value 传入值
     */
    Var(T value) : value_(value) {}
    /**
     * @brief 获取变量值
     * @return 变量值
     */
    const T &get() const { return value_; }
    /**
     * @brief 设置变量值，并发出valueChanged信号
     * @param value 新值
     */
    void set(T value)
    {
        if (value_ != value)
        {
            value_ = value;
            valueChanged(value_);
        }
    }

    /**
     * @brief 重载赋值运算符
     * @param value 新值
     * @return 变量值
     */
    const T &operator=(T value)
    {
        set(value);
        return value_;
    }
};

