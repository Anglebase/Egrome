#pragma once

#include "../core/XString.h"
#include "../view/Click.h"
#include "../view/Hover.h"

/**
 * @brief 按钮控件
 */
class Button : public Click, public Hover {
private:
    String text_;
    bool isPressed_;
    bool isHovered_;

protected:
    void paintEvent(PaintEvent* event) override;
    void mousePressEvent(MousePressEvent* event) override;
    void mouseReleaseEvent(MouseReleaseEvent* event) override;
    void mouseMoveEvent(MouseMoveEvent* event) override;
    
public:
    Button(const Rect& rect, Block* parent = nullptr);
    ~Button() override;
    /**
     * @brief 设置按钮的文本内容
     * @param text 按钮的文本内容
     */
    void setText(const String& text);
};