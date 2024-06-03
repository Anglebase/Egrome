#pragma once

#include "../view/Block.h"
#include "../core/SignalSlots.hpp"
#include "../core/Rect.h"
#include "../view/Color.h"

/**
 * @addtogroup 控件
 * @{
*/

/**
 * @brief 进度条控件
 */
class ProgressBar : public Block
{
    double progress{0.0};

    Color progressColor{Color::White};
    Color backgroundColor{Color::Black};
    Color borderColor{Color::White};

    int borderWidth{1};

protected:
    /**
     * @brief 重写 Block::paintEvent() 函数，绘制进度条
     * @param event 绘制事件
     */
    void paintEvent(const PaintEvent &event) override;

signals:
    /**
     * @brief 进度发生变化的信号
     * @param progress 进度值
    */
    Signal<void(double progress)> progressChanged;
    /**
     * @brief 进度条完成的信号
     */
    Signal<void()> finished;
    /**
     * @brief 进度条归零的信号
     */
    Signal<void()> beZero;

public:
    /**
     * @brief 构造函数
     * @param rect 进度条的矩形区域
     * @param parent 父控件
    */
    ProgressBar(const Rect &rect, Block *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~ProgressBar() override = default;

    /**
     * @brief 设置进度值
     * @param progress 进度值
     * @note 进度值范围为 [0, 1]，大于 1 则视为 1，小于 0 则视为 0
     */
    void setProgress(double progress);
    /**
     * @brief 获取进度值
     * @return 进度值
     */
    double getProgress() const;
};

/** @} */