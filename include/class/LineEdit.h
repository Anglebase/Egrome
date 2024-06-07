#pragma once

#include <string>
#include "../view/Block.h"
#include "../core/SignalSlots.hpp"
#include "../core/Var.hpp"

/**
 * @brief 行文本编辑框
 */
class LineEdit : public Block
{
private:
    std::wstring text_;
    std::wstring fontName_{L"宋体"};
    long fontSize_{36};

    bool isPressed_{false};

    Var<int> cursorPos_{0};
    bool cursorVisible_{false};
    bool hasSelect_{false};
    int selectPos_{0};

    int offsetX_{5};
    int offsetY_{5};
    int clipOffsetX_{0};
    int clipWidth_;
    std::vector<int> widths_;
    bool viewChangedFlag_{false};

    std::function<void()> updateCursorPosition{([]() -> void {})};
signals:
    Signal<void(const std::wstring &text)> textChanged;
    Signal<void()> cursorShow;
    Signal<void()> cursorHide;
    Signal<void(const std::wstring &text)> textEnter;

protected:
    void paintEvent(const PaintEvent &event) override;
    void mousePressEvent(const Point &pos, MouseButton button) override;
    void keyPressEvent(Key key, KeyFlag flag) override;
    void InputTextEvent(wchar_t inputChar) override;
    void mouseMoveEvent(const Point &pos) override;
    void mouseReleaseEvent(const Point &pos, MouseButton button) override;

public:
    LineEdit(const Rect &rect, Block *parent = nullptr);
    void setText(const std::wstring &text);
    void setFont(const std::wstring &fontName, long fontSize);
};
