#pragma once

#include "core.h"
#include "view.h"

class Button : public Block
{
    bool isPressed;
    bool isHovered;
    bool isDisabled;

    // Styles
    Color textColor;
    Color backgroundColor;
    Color hoverColor;
    Color pressedColor;
    Color disabledColor;

    Animation<Color> *textColorAnim;
    Animation<Color> *backgroundColorAnim;
    Animation<Color> *hoverColorAnim;
    Animation<Color> *pressedColorAnim;

    std::wstring text;

protected:
    void paintEvent(const PaintEvent &event) override;
    void mousePressEvent(const Point& pos, MouseButton button) override;
    void mouseReleaseEvent(const Point& pos, MouseButton button) override;

signals:
    Signal<void()> clicked;
    Signal<void()> hovered;
    Signal<void()> pressed;
    Signal<void()> released;

public:
    Button(const Rect &rect, Block *parent = nullptr);
    ~Button() override;

    void setTextColor(const Color &color);
    void setBackgroundColor(const Color &color);
    void setHoverColor(const Color &color);
    void setPressedColor(const Color &color);
    void setDisabledColor(const Color &color);

    void setDisabled(bool disabled);

    void setText(const std::wstring &text);
};