#pragma once

/**
 * @file Animation.hpp
 * @brief 动画支持类
*/

#include <chrono>
#include <functional>

/**
 * @addtogroup 核心
 * @{
 */

/**
 * @brief 动画支持类
 * @tparam T 要进行动画插值计算的类型
 * @note 该类支持对任意类型进行动画插值计算，只需要设置起始值、终止值、动画时间，以及插值计算函数即可
 * @note 对于未重载+、-以及*运算符的类型，必须提供自定义的插值计算函数，否则会导致编译错误
 */
template <typename T>
class Animation
{
    T startValue_;                                    // 起始值
    T endValue_;                                      // 终止值
    std::chrono::milliseconds time_;                  // 动画时间
    mutable bool running_ = false;                    // 动画是否正在运行
    mutable double t_ = 0.0;                          // 当前时长比例
    std::chrono::steady_clock::time_point startTime_; // 动画开始时间
    bool is_reverse_ = false;                         // 是否反向播放

protected:
    /**
     * @brief 该函数用于计算动画值
     * @param start 起始值
     * @param end 终止值
     * @param t 动画时间比例
     * @return 当前时长比例对应的动画值
     * @note 该函数可以自定义，以实现更复杂的动画效果，默认实现为线性插值，即 start + (end - start) * t，此值不应被直接修改
     * @see Animation::set()
     */
    std::function<T(T start, T end, double t)> valueComputer_;

public:
    /**
     * @brief 构造函数
     * @note 默认插值计算函数为线性插值
     */
    Animation()
        : startValue_(0), endValue_(0), time_(0),
          valueComputer_([](T start, T end, double t)
                         { return start + (end - start) * t; }) {}

    /**
     * @brief 构造函数
     * @param valueComputer 插值计算函数
     */
    Animation(std::function<T(T, T, double)> valueComputer)
        : startValue_(0), endValue_(0), time_(0),
          valueComputer_(valueComputer) {}

    /**
     * @brief 判断动画是否正在运行
     * @return true 正在运行，false 停止
     */
    bool isRunning() const
    {
        return running_;
    }

    /**
     * @brief 设置动画参数
     * @param startValue 起始值
     * @param endValue 终止值
     * @param time 动画时间
     */
    void set(T startValue, T endValue, std::chrono::milliseconds time)
    {
        startValue_ = startValue;
        endValue_ = endValue;
        time_ = time;
    }

    /**
     * @brief 设置插值计算函数
     * @param valueComputer 插值计算函数
     * @note 该函数可以设置自定义的插值计算函数，以实现更复杂的动画效果
     * @see Animation::valueComputer_
     */
    void set(std::function<T(T, T, double)> valueComputer)
    {
        valueComputer_ = valueComputer;
    }

    /**
     * @brief 开始动画
     * @note 调用该函数后，动画将开始运行，并在动画时间结束后停止
     */
    void start()
    {
        running_ = true;
        startTime_ = std::chrono::steady_clock::now();
    }
    /**
     * @brief 停止动画
     * @note 调用该函数后，动画将停止，此函数不会重置动画时间
     */
    void stop()
    {
        running_ = false;
    }
    /**
     * @brief 运行动画
     * @param is_reverse 是否反向播放，默认为 false，即正向播放，如果设置为 true，则反向播放
     * @note 此函数与 start() 函数的区别在于它不会重置动画时间，而是继续运行动画，直到动画时间结束
     */
    void run(bool is_reverse = false)
    {
        running_ = true;
        this->is_reverse_ = is_reverse;
        if (is_reverse)
        {
            t_ = 1.0 - t_;
        }
        this->startTime_ = std::chrono::steady_clock::now() - std::chrono::duration_cast<std::chrono::milliseconds>(time_ * t_);
    }
    /**
     * @brief 重置动画
     * @note 调用该函数后，动画将停止，并将动画时间重置为 0
     */
    void reset()
    {
        startTime_ = std::chrono::steady_clock::now();
        running_ = false;
    }

    /**
     * @brief 获取当前动画值
     * @note 该函数会根据当前动画时间和插值计算函数，计算当前动画值
     * @return 当前值
     */
    T value() const
    {
        if (running_)
        {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime_);
            t_ = elapsed.count() * 1. / time_.count();
            if (is_reverse_)
            {
                t_ = 1.0 - t_;
            }
            if (t_ > 1.0)
            {
                t_ = 1.0;
                running_ = false;
            }
            else if (t_ < 0.0)
            {
                t_ = 0.0;
                running_ = false;
            }
        }
        return valueComputer_(startValue_, endValue_, this->t_);
    }
};
/** @} */