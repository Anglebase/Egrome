#pragma once

#include <string>
#include <chrono>
#include "../view/Block.h"
#include "../core/SignalSlots.hpp"
#include "../core/Var.hpp"
#include "../view/Color.h"

/**
 * @addtogroup 控件
 * @{
 */

/**
 * @addtogroup 行文本输入框
 * @{
 */

/**
 * @brief 行文本编辑框
 */
class LineEdit : public Block
{
    std::chrono::steady_clock::time_point lastTime_;

private:
    std::wstring text_;

    bool isPressed_{false};

    Int cursorPos_{0};
    bool cursorVisible_{false};
    bool hasSelect_{false};
    bool finisedSelect_{false};
    int selectPos_{0};

    int offsetX_{5};
    int offsetY_{5};
    int clipOffsetX_{0};
    int clipWidth_;
    std::vector<int> widths_;
    bool viewChangedFlag_{false};
    bool showPlainText_{true};
signals:
    Signal<void(const std::wstring &text)> textChanged;
    Signal<void()> cursorShow;
    Signal<void()> cursorHide;
    Signal<void(const std::wstring &text)> textEnter;

protected:
    void paintText(const PaintEvent &event);
    void paintPassword(const PaintEvent &event);
    void paintEvent(const PaintEvent &event) override;
    void mousePressEvent(const Point &pos, MouseButton button) override;
    void keyPressEvent(Key key, KeyFlag flag) override;
    void InputTextEvent(wchar_t inputChar) override;
    void mouseMoveEvent(const Point &pos) override;
    void mouseReleaseEvent(const Point &pos, MouseButton button) override;

public:
    /**
     * @brief 样式表
     */
    struct StyleSheet
    {
        /// @brief 文本颜色
        Color textColor{Color::White};
        /// @brief 文本光标颜色
        Color cursorColor{Color::White};
        /// @brief 文本背景颜色
        Color backgroundColor{Color::Black};
        /// @brief 输入框聚焦时边框颜色
        Color onFocusBorderColor{Color::White};
        /// @brief 输入框失焦时边框颜色
        Color offFocusBorderColor{Color::Gray};
        /// @brief 边框宽度
        int borderWidth{1};
        /// @brief 边框圆角半径
        int borderRadius{0};
        /// @brief 文本光标宽度
        int cursorWidth{1};
        /// @brief 文本字体
        std::wstring fontName{L"宋体"};
        /// @brief 文本字号
        long fontSize{16};
    } style;

public:
    LineEdit(const Rect &rect, Block *parent = nullptr);
    ~LineEdit() override = default;

    /**
     * @brief 设置文本内容
     * @param text 文本内容
     */
    void setText(const std::wstring &text);
    /**
     * @brief 获取文本内容
     * @return 文本内容
     */
    const std::wstring &text() const;

    /**
     * @brief 设置是否展示明文
     * @param show 是否展示明文
     */
    void setShowPlainText(bool show);

    /**
     * @brief 获取是否展示明文
     * @return 是否展示明文
     */
    bool isShowPlainText() const;
};
/** @} */
/** @} */