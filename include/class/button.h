#pragma once

#include "Block.h"
#include "Animation.hpp"
#include "SignalSlots.hpp"
#include "Color.h"

/**
 * @addtogroup 控件
 * @brief 常用控件封装类
 * @{
*/

/**
 * @brief 按钮控件
 * @details 按钮控件是一种基本的控件，可以响应鼠标点击、悬停、按下、释放等事件，并提供相关的信号
 * @details 按钮控件的样式可以通过设置文本颜色、背景颜色、悬停颜色、按下颜色、禁用颜色等属性来设置
 * @details 按钮控件还提供了动画功能，可以实现按钮悬停、按下时的颜色变化，以实现动态交互效果
 */
class Button : public Block
{
    bool isPressed;    // 是否被按下
    bool isHovered;    // 是否悬停
    bool isDisabled;   // 是否不可用
    std::wstring text; // 按钮文本内容

    // Styles
    Color textColor;       // 文本颜色
    Color backgroundColor; // 背景颜色
    Color hoverColor;      // 悬停颜色
    Color pressedColor;    // 按下颜色
    Color disabledColor;   // 禁用颜色

protected:
    // Animations
    /**
     * @brief 按钮悬停动画
     * @details 鼠标悬停于按钮上时，背景颜色逐渐由默认颜色变为悬停颜色
     */
    Animation<Color> *hoverColorAnim;
    /**
     * @brief 按钮按下动画
     * @details 按钮被按下时，背景颜色逐渐由默认颜色变为按下颜色
     */
    Animation<Color> *pressedColorAnim;

protected:
    /**
     * @brief 重写 paintEvent 方法，绘制按钮的背景、文本
     * @param event 全局绘制事件对象
     */
    void paintEvent(const PaintEvent &event) override;

    /**
     * @brief 重写 mousePressEvent 方法，响应鼠标点击事件
     * @param pos 鼠标位置
     * @param button 鼠标按键
     */
    void mousePressEvent(const Point &pos, MouseButton button) override;

    /**
     * @brief 重写 mouseReleaseEvent 方法，响应鼠标释放事件
     * @param pos 鼠标位置
     * @param button 鼠标按键
     */
    void mouseReleaseEvent(const Point &pos, MouseButton button) override;

signals:
    /**
     * @brief 按钮点击信号
     * @details 按钮被点击时发出该信号
     */
    Signal<void()> clicked;
    /**
     * @brief 按钮悬停信号
     * @details 鼠标悬停于按钮之上时发出该信号
     */
    Signal<void()> hovered;
    /**
     * @brief 按钮按下信号
     * @details 按钮被按下时发出该信号
     */
    Signal<void()> pressed;
    /**
     * @brief 按钮释放信号
     * @details 按钮被释放时发出该信号
     */
    Signal<void()> released;

public:
    Button(const Rect &rect, Block *parent = nullptr);
    ~Button() override;

    /**
     * @brief 设置按钮的文本颜色
     * @param color 按钮的文本颜色
     */
    void setTextColor(const Color &color);

    /**
     * @brief 设置按钮的默认背景颜色
     * @param color 按钮的默认背景颜色
     */
    void setBackgroundColor(const Color &color);

    /**
     * @brief 设置按钮悬停时的颜色
     * @param color 按钮悬停时的颜色
     */
    void setHoverColor(const Color &color);

    /**
     * @brief 设置按钮按下时的颜色
     * @param color 按钮按下时的颜色
     */
    void setPressedColor(const Color &color);

    /**
     * @brief 设置按钮不可用时的颜色
     * @param color 按钮不可用时的颜色
     */
    void setDisabledColor(const Color &color);

    /**
     * @brief 设置按钮是否可用
     * @param disabled 如果为true，则按钮不可用，否则可点击
     */
    void setDisabled(bool disabled);

    /**
     * @brief 设置按钮的文本内容
     * @param text 按钮的文本内容
     */
    void setText(const std::wstring &text);
};

/** @} */