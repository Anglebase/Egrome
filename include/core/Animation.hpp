#pragma once

#include <chrono>
#include <functional>
#include "./SignalSlots.hpp"

template <typename T>
class Animation
{
public:
    struct Args
    {
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
signals:
    Signal<void()> finished;  // 动画结束信号
    Signal<void()> started;   // 动画开始信号
    Signal<void()> stopted;   // 动画停止信号
    Signal<void()> continued; // 动画继续信号

protected:
    std::function<T(T start, T end, double t)> valueComputer_;

public:

    Animation()
        : startValue_(0), endValue_(0), time_(0),
          valueComputer_([](T start, T end, double t)
                         { return start + (end - start) * t; }) {}

    Animation(Args args)
        : startValue_(args.startValue), endValue_(args.endValue), time_(args.duration),
          valueComputer_(args.function) {}

    bool isRunning() const
    {
        return running_;
    }

    void set(T startValue, T endValue, std::chrono::milliseconds time)
    {
        startValue_ = startValue;
        endValue_ = endValue;
        time_ = time;
    }

    void set(std::function<T(T, T, double)> valueComputer)
    {
        valueComputer_ = valueComputer;
    }

    void start()
    {
        running_ = true;
        startTime_ = std::chrono::steady_clock::now();
        this->started.emit();
    }

    void stop()
    {
        running_ = false;
        this->stopted.emit();
    }

    void run(bool is_reverse = false)
    {
        running_ = true;
        this->is_reverse_ = is_reverse;
        this->continued.emit();
        if (is_reverse)
        {
            t_ = 1.0 - t_;
        }
        this->startTime_ = std::chrono::steady_clock::now() - std::chrono::duration_cast<std::chrono::milliseconds>(time_ * t_);
    }

    void reset()
    {
        startTime_ = std::chrono::steady_clock::now();
        running_ = false;
    }

    T value()
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
                this->finished.emit();
            }
            else if (t_ < 0.0)
            {
                t_ = 0.0;
                running_ = false;
                this->finished.emit();
            }
        }
        return valueComputer_(startValue_, endValue_, this->t_);
    }

    operator T(){
        return this->value();
    }
};
/** @} */