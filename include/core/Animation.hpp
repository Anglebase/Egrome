#pragma once

#include <chrono>
#include <functional>
#include "./SignalSlots.hpp"

/**
 * @brief 动画插值类
 * @details 该类用于实现动画效果，支持插值计算函数的自定义，并提供信号槽机制用于通知动画状态变化
 * @tparam T 被插值的值类型
 */
template <typename T>
class Animation {
public:
    struct Args {
        /// 起始值
        T startValue;
        /// 终止值
        T endValue;
        /// 时长
        std::chrono::milliseconds duration;
        /// 插值计算函数
        std::function<T(T, T, double)> function;
    };

private:
    T startValue_;                                    // 起始值
    T endValue_;                                      // 终止值
    std::chrono::milliseconds time_;                  // 动画时间
    bool running_ = false;                            // 动画是否正在运行
    double t_ = 0.0;                                  // 当前时长比例
    std::chrono::steady_clock::time_point startTime_; // 动画开始时间
    bool is_reverse_ = false;                         // 是否反向播放

protected:
    std::function<T(T start, T end, double t)> valueComputer_;

public:
    /**
     * @brief 默认构造函数
     * @details 构造函数默认使用线性插值函数，该类型应确保提供了对于operator+(T, T)，operator-(T, T)，operator*(T, double)的支持，以及该类可以被零初始化
     */
    Animation()
        : startValue_(0), endValue_(0), time_(0),
        valueComputer_([](T start, T end, double t) { return start + (end - start) * t; }) {}

    Animation(Args args)
        : startValue_(args.startValue), endValue_(args.endValue), time_(args.duration),
        valueComputer_(args.function) {}

    /**
     * @brief 动画是否正在运行
     * @return true 正在运行，false 停止
     */
    bool isRunning() const {
        return running_;
    }

    /**
     * @brief 设置动画参数
     * @param startValue    起始值
     * @param endValue      终止值
     * @param time          时长
     */
    void set(T startValue, T endValue, std::chrono::milliseconds time) {
        startValue_ = startValue;
        endValue_ = endValue;
        time_ = time;
    }
    /**
     * @brief 设置动画参数
     * @param valueComputer 插值计算函数
     */
    void set(std::function<T(T, T, double)> valueComputer) {
        valueComputer_ = valueComputer;
    }
    /**
     * @brief 使动画开始运行，该函数会重置当前动画进度
     */
    void start() {
        running_ = true;
        startTime_ = std::chrono::steady_clock::now();
        this->started.emit();
    }
    /**
     * @brief 使动画停止运行
     */
    void stop() {
        running_ = false;
        this->stopted.emit();
    }
    /**
     * @brief 使动画开始运行，该函数不会重置当前动画进度
     * @param is_reverse 是否倒放
     */
    void run(bool is_reverse = false) {
        running_ = true;
        this->is_reverse_ = is_reverse;
        this->continued.emit();
        if (is_reverse) {
            t_ = 1.0 - t_;
        }
        this->startTime_ = std::chrono::steady_clock::now() - std::chrono::duration_cast<std::chrono::milliseconds>(time_ * t_);
    }
    /**
     * @brief 重置动画状态
     */
    void reset() {
        startTime_ = std::chrono::steady_clock::now();
        running_ = false;
    }
    /**
     * @brief 获取动画当前值
     * @return 当前值
     */
    T value() {
        if (running_) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime_);
            t_ = elapsed.count() * 1. / time_.count();
            if (is_reverse_) {
                t_ = 1.0 - t_;
            }
            if (t_ > 1.0) {
                t_ = 1.0;
                running_ = false;
                this->finished.emit();
            }
            else if (t_ < 0.0) {
                t_ = 0.0;
                running_ = false;
                this->finished.emit();
            }
        }
        return valueComputer_(startValue_, endValue_, this->t_);
    }
    /**
     * @brief 与Animation<T>::value()相同，用于方便调用
     * @return 当前值
     */
    operator T() {
        return this->value();
    }

public:
    Signal<void()> finished;  // 动画结束信号
    Signal<void()> started;   // 动画开始信号
    Signal<void()> stopted;   // 动画停止信号
    Signal<void()> continued; // 动画继续信号
};