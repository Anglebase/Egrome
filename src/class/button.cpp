#include "button.h"

void Button::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);
    painter.setTextAlign(TextHAlign::Center, TextVAlign::Center);
    if (this->isDisabled)
    {
        painter.setBrushColor(this->disabledColor);
        painter.drawFillRect(painter.rect());
        painter.setPenColor(this->textColor);
        painter.drawText(painter.rect(), this->text);
    }
    else if (this->isPressed)
    {
        painter.setBrushColor(this->pressedColor);
        painter.drawFillRect(painter.rect());
        painter.setPenColor(this->textColor);
        painter.drawText(painter.rect(), this->text);
    }
    else if (this->isHovered)
    {
        painter.setBrushColor(this->hoverColor);
        painter.drawFillRect(painter.rect());
        painter.setPenColor(this->textColor);
        painter.drawText(painter.rect(), this->text);
    }
    else
    {
        painter.setBrushColor(this->backgroundColor);
        painter.drawFillRect(painter.rect());
        painter.setPenColor(this->textColor);
        painter.drawText(painter.rect(), this->text);
    }
    event.endPaint();
}

void Button::mousePressEvent(const Point &pos, MouseButton button)
{
    using namespace std::chrono_literals;
    if (button == MouseButton::Left)
    {
        this->isPressed = true;
        this->backgroundColorAnim->set(this->backgroundColor,
                                       this->pressedColor,
                                       500ms);
        this->textColorAnim->run();
        this->clicked.emit();
    }
    return Block::mousePressEvent(pos, button);
}

void Button::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    using namespace std::chrono_literals;
    if (button == MouseButton::Left)
    {
        this->isPressed = false;
        this->backgroundColorAnim->set(this->backgroundColor,
                                       this->backgroundColor,
                                       500ms);
        this->backgroundColorAnim->run(true);
    }
    return Block::mouseReleaseEvent(pos, button);
}

void Button::mouseMoveEvent(const Point &pos)
{
    using namespace std::chrono_literals;
    if (this->rect().contains(pos))
    {
        this->isHovered = true;
    }
    else
    {
        this->isHovered = false;
    }
    return Block::mouseMoveEvent(pos);
}

Button::Button(const Rect &rect, Block *parent)
    : Block(rect, parent),
      textColor(Color::Black),
      backgroundColor(Color::White),
      hoverColor(Color::LightGray),
      disabledColor(Color::DarkGray),
      pressedColor(Color::Gray),
      isDisabled(false),
      isPressed(false),
      isHovered(false),
      text(L"Button")
{
    auto color_lerp = [](Color start, Color end, double t) -> Color
    {
        auto f = [](int a, int b, double t) -> int
        { return a + (b - a) * t; };
        return Color{
            f(start.getRed(), end.getRed(), t),
            f(start.getGreen(), end.getGreen(), t),
            f(start.getBlue(), end.getBlue(), t),
        };
    };
    this->backgroundColorAnim = new Animation<Color>{color_lerp};
    this->hoverColorAnim = new Animation<Color>{color_lerp};
    this->pressedColorAnim = new Animation<Color>{color_lerp};
    this->textColorAnim = new Animation<Color>{color_lerp};

}

Button::~Button()
{
    delete this->backgroundColorAnim;
    delete this->hoverColorAnim;
    delete this->pressedColorAnim;
    delete this->textColorAnim;
}

void Button::setTextColor(const Color &color)
{
    this->textColor = color;
}

void Button::setBackgroundColor(const Color &color)
{
    this->backgroundColor = color;
}

void Button::setHoverColor(const Color &color)
{
    this->hoverColor = color;
}

void Button::setPressedColor(const Color &color)
{
    this->pressedColor = color;
}

void Button::setDisabledColor(const Color &color)
{
    this->disabledColor = color;
}

void Button::setDisabled(bool disabled)
{
    this->isDisabled = disabled;
}

void Button::setText(const std::wstring &text)
{
    this->text = text;
}
