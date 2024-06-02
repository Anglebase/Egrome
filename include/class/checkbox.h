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
    
    Color textColor_;
    Color checkColor_;
    Color borderColor_;
    int borderWidth_;
    int boxSize_;

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
    /**
     * @brief 设置复选框的文字颜色
     * @param color 文字颜色
     */
    void setTextColor(const Color &color);
    /**
     * @brief 设置复选框的勾选框颜色
     * @param color 勾选框颜色
     */
    void setCheckColor(const Color &color);
    /**
     * @brief 设置复选框的边框颜色
     * @param color 边框颜色
     */
    void setBorderColor(const Color &color);
    /**
     * @brief 设置复选框的边框宽度
     * @param width 边框宽度
     */
    void setBorderWidth(int width);
    /**
     * @brief 设置复选框的尺寸
     * @details 这里的尺寸指的是勾选框的大小，单位为像素
     * @param size 尺寸
     */
    void setBoxSize(int size);
};

/** @} */