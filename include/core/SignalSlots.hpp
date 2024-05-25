#pragma once
/**
 * @file SignalSlots.hpp
 * @brief 信号-槽机制
 */

#include <map>
#include <functional>

/**
 * @brief 信号类，是信号槽机制的核心类
 * @note 此类是无特化的类，并无实现，定义信号时模板参数必须指定为void(Args...)或void()，具体用法请参考 Signal<void(Args...)> 或 Signal<void()>
 */
template <typename... Args>
class Signal;

/**
 * @brief 信号类的有参特化
 * @brief 信号类的有参特化
 * @tparam ...Args 槽函数参数类型列表
 */
template <typename... Args>
class Signal<void(Args...)>
{
private:
    std::map<unsigned long long, std::function<void(Args...)>> slots;
    unsigned long long slotId = 0;

public:
    /**
     * @brief 将 \a slot 添加到槽函数列表
     * @param slot 槽函数
     * @return 此槽函数的 ID
     */
    unsigned long long connect(const std::function<void(Args...)> &slot)
    {
        slots[slotId] = slot;
        return slotId++;
    }

    /**
     * @brief connect函数的重载，用于绑定对象的成员函数
     * @tparam T
     * @param obj 对象指针
     * @param func 成员函数指针
     * @return 此槽函数的 ID
     */
    template <typename T>
    unsigned long long connect(T *obj, void (T::*func)(Args...))
    {
        return this->connect([obj, func](Args &&...args)
                             { (obj->*func)(std::forward<Args>(args)...); });
    }

    /**
     * @brief 移除槽函数
     * @param slotId 要移除的槽函数 ID
     */
    void disconnect(unsigned long long slotId)
    {
        if (slots.find(slotId) != slots.end())
            slots.erase(slotId);
    }

    /**
     * @brief 发送信号，调用所有槽函数
     * @param ...args 槽函数参数列表
     */
    void emit(Args &&...args)
    {
        for (auto &slot : slots)
            slot.second(std::forward<Args>(args)...);
    }
};

/**
 * @brief 信号类的无参特化
 */
template <>
class Signal<void()>
{
    std::map<unsigned long long, std::function<void()>> slots;
    unsigned long long slotId = 0;

public:
    /**
     * @brief 将 \a slot 添加到槽函数列表
     * @param slot 槽函数
     * @return 此槽函数的 ID
     */
    unsigned long long connect(const std::function<void()> &slot)
    {
        slots[slotId] = slot;
        return slotId++;
    }

    /**
     * @brief connect函数的重载，将成员函数作为槽函数
     * @tparam T
     * @param obj 对象指针
     * @param func 成员函数指针
     * @return 此槽函数的 ID
     */
    template <typename T>
    unsigned long long connect(T *obj, void (T::*func)())
    {
        return this->connect([obj, func]()
                             { (obj->*func)(); });
    }

    /**
     * @brief 移除槽函数
     * @param slotId 要移除的槽函数 ID
     */
    void disconnect(unsigned long long slotId)
    {
        if (slots.find(slotId) != slots.end())
            slots.erase(slotId);
    }

    /**
     * @brief 发送信号，调用所有槽函数
     * @param ...args 槽函数参数列表
     */
    void emit()
    {
        for (auto &slot : slots)
            slot.second();
    }
};