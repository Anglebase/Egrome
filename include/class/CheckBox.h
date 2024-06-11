#pragma once
/**
 * @file checkbox.h
 * @brief 复选框控件
 * @details 继承自 Block 类，实现了鼠标点击事件，以及信号槽机制
 */
#include <string>
#include "../view/Block.h"
#include "../view/Color.h"
#include "../core/SignalSlots.hpp"

/**
 * @addtogroup 控件
 * @{
 */

/**
 * @brief 复选框控件
 * @details 继承自 Block 类，实现了鼠标点击事件，以及信号槽机制
 * @details 此类所提供的复选框具有基本交互功能，包括选中和取消选中，以及鼠标悬停状态的变化
 */
class CheckBox : public Block
{
private:
    bool checked_;
    bool hovered_;
    std::wstring text_;

public:
    struct StyleSheet
    {
        Color textColor{Color::White};
        Color checkColor{Color::White};
        Color borderColor{Color::White};
        Color hoverColor{Color::LightGray};
        int borderWidth{1};
        int boxSize{10};
    } style;

protected:
    /**
     * @brief 重写 paintEvent() 函数，绘制复选框
     * @details 这里绘制将整个复选框控件视为一个默认不可见的矩形，在其内部绘制文本和勾选框
     * @param event PaintEvent 事件
     */
    void paintEvent(const PaintEvent &event) override;
    /**
     * @brief 重写 mousePressEvent() 函数，响应鼠标点击事件
     * @details 这里响应鼠标点击事件，当鼠标点击在复选框内部时，将其选中或取消选中，并发出信号
     * @param pos 鼠标点击位置
     * @param button 鼠标按键
     */
    void mousePressEvent(const Point &pos, MouseButton button) override;

signals:
    /**
     * @brief 复选框状态改变信号
     * @details 当复选框状态改变时，发出此信号，并带有新的状态值
     */
    Signal<void(bool)> checkedChanged;

public:
    /**
     * @brief 构造函数
     * @param rect 复选框的矩形区域
     * @param parent 父控件指针
     */
    CheckBox(const Rect &rect, Block *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~CheckBox() override = default;

    /**
     * @brief 获取复选框是否被选中
     * @return true 表示被选中，false 表示未被选中
     */
    bool isChecked() const;
    /**
     * @brief 设置复选框是否被选中
     * @param checked true 表示被选中，false 表示未被选中
     */
    void setChecked(bool checked);
    /**
     * @brief 设置复选框的文本内容
     * @param text 文本内容
     */
    void setText(const std::wstring &text);
};

/** @} */
