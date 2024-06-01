#pragma once
/**
 * @file Label.h
 * @brief 标签控件
 * @details 继承自Block类，实现了文本标签的显示功能，包括文本内容、对齐方式、边距等属性
 * @details 显示的文本溢出控件范围时，默认行为是隐藏溢出内容
*/
#include "../view/Block.h"
#include "../view/Color.h"

/**
 * @addtogroup 控件
 * @{
*/

/**
 * @brief 标签控件
 * @details 继承自Block类，实现了文本标签的显示功能，包括文本内容、对齐方式、边距等属性
 * @details 显示的文本溢出控件范围时，默认行为是隐藏溢出内容
 */
class Label : public Block
{
public:
    /**
     * @brief 对齐方式
    */
    enum Alignment
    {
        /// 左对齐
        Left = 0x01,
        /// 水平居中对齐
        Center = 0x03,
        /// 右对齐
        Right = 0x02,
        /// 顶部对齐
        Top = 0x01 << 2,
        /// 垂直居中对齐
        Middle = 0x03 << 2,
        /// 底部对齐
        Bottom = 0x02 << 2
    };

private:
    std::wstring text_;
    Color textColor_;
    int alignment_;
    int leftpadding_{0};
    int rightpadding_{0};
    int toppadding_{0};
    int bottompadding_{0};

    std::wstring fontName_{L"宋体"};
    int fontSize_{16};
    bool italic_{false};
    int weight_{400};

protected:
    /**
     * @brief 重写 paintEvent() 函数，实现文本标签的显示
     * @param event PaintEvent 事件
     */
    void paintEvent(const PaintEvent &event) override;

public:
    /**
     * @brief 构造函数
     * @param rect 标签的显示范围
     * @param parent 父控件指针
     * @details 默认对齐方式为左对齐垂直居中对齐，文本颜色为白色，边距为0
     */
    Label(const Rect &rect, Block *parent);
    /**
     * @brief 析构函数
     */
    ~Label() override = default;

    /**
     * @brief 设置标签文本内容
     * @param text 标签文本内容
     */
    void setText(const std::wstring &text);
    /**
     * @brief 获取标签文本内容
     * @return 标签文本内容
     */
    const std::wstring &getText() const;
    /**
     * @brief 设置标签文本对齐方式
     * @param alignment 标签文本对齐方式，参考 Alignment 枚举定义，默认为左对齐垂直居中对齐，可以使用按位或运算符组合多个对齐方式
     */
    void setAlignment(int alignment);
    /**
     * @brief 获取标签文本对齐方式
     * @return 标签文本对齐方式
     */
    int getAlignment() const;
    /**
     * @brief 设置标签控件内边距
     * @param left 左边距
     * @param top 上边距
     * @param right 右边距
     * @param bottom 下边距
     */
    void setPadding(int left, int top, int right, int bottom);
    /**
     * @brief 访问标签控件左内边距
     * @return 标签控件左内边距值的引用
     */
    int &leftPadding();
    /**
     * @brief 访问标签控件上内边距
     * @return 标签控件上内边距值的引用
     */
    int &topPadding();
    /**
     * @brief 访问标签控件右内边距
     * @return 标签控件右内边距值的引用
     */
    int &rightPadding();
    /**
     * @brief 访问标签控件下内边距
     * @return 标签控件下内边距值的引用
    */
    int &bottomPadding();
    /**
     * @brief 获取标签控件左内边距
     * @return 标签控件左内边距值
     */
    const int &leftPadding() const;
    /**
     * @brief 获取标签控件上内边距
     * @return 标签控件上内边距值
     */
    const int &topPadding() const;
    /**
     * @brief 获取标签控件右内边距
     * @return 标签控件右内边距值
     */
    const int &rightPadding() const;
    /**
     * @brief 获取标签控件下内边距
     * @return 标签控件下内边距值
     */
    const int &bottomPadding() const;

    /**
     * @brief 设置标签文本颜色
     * @param color 标签文本颜色
     */
    void setTextColor(const Color &color);

    /**
     * @brief 设置标签字体
     * @param fontName 字体名称
     * @param size 字体大小
     */
    void setFont(const std::wstring &fontName, int size);
    /**
     * @brief 设置标签字体斜体
     * @param italic true 字体斜体，false 非斜体
     */
    void setItalic(bool italic);
    /**
     * @brief 设置标签字体粗细
     * @param weight 字体粗细，取值范围 100-900，数值越大字体越粗
     */
    void setWeight(int weight);
};

/** @} */