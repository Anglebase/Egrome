#include "Painter.h"
#include "button.h"

void Button::paintEvent(const PaintEvent &event)
{
    // 绘制按钮
    auto &painter = event.beginPaint(this);
    painter.setTextAlign(TextHAlign::Center, TextVAlign::Center);
    // 状态判断与显示
    if (this->isDisabled)
    {
        painter.setBrushColor(this->disabledColor);
        painter.setPenColor(this->textColor);
    }
    else if (this->isPressed || this->pressedColorAnim->isRunning())
    {
        painter.setBrushColor(this->pressedColorAnim->value());
        painter.setPenColor(this->textColor);
    }
    else if (this->isHovered || this->hoverColorAnim->isRunning())
    {
        painter.setBrushColor(this->hoverColorAnim->value());
        painter.setPenColor(this->textColor);
    }
    else
    {
        painter.setBrushColor(this->backgroundColor);
        painter.setPenColor(this->textColor);
    }
    painter.drawFillRect(painter.rect());
    painter.drawText(painter.rect(), this->text);
    event.endPaint();
}

void Button::mousePressEvent(const Point &pos, MouseButton button)
{
    using namespace std::chrono_literals;
    // 监测点击
    if (this->rect().contains(pos) &&
        button == MouseButton::Left &&
        !this->isDisabled)
    {
        this->isPressed = true;
        this->pressedColorAnim->run();
        this->clicked.emit();
    }
    return Block::mousePressEvent(pos, button);
}

void Button::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    using namespace std::chrono_literals;
    if (button == MouseButton::Left &&
        !this->isDisabled)
    {
        if (this->isPressed)
            this->pressedColorAnim->run(true);
        this->isPressed = false;
    }
    return Block::mouseReleaseEvent(pos, button);
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
    using namespace std::chrono_literals;
    // 注册颜色过渡动画
    this->hoverColorAnim = new Animation<Color>{Color::color_lerp};
    this->hoverColorAnim->set(
        this->backgroundColor,
        this->hoverColor,
        300ms);
    this->pressedColorAnim = new Animation<Color>{Color::color_lerp};
    this->pressedColorAnim->set(
        this->hoverColor,
        this->pressedColor,
        100ms);
    // 连接槽函数
    this->onEnter.connect(
        [this]()
        {
            this->isHovered = true;
            this->hoverColorAnim->reset();
            this->hoverColorAnim->run();
        });
    this->onLeave.connect(
        [this]()
        {
            this->isHovered = false;
            this->hoverColorAnim->run(true);
        });
}

Button::~Button()
{
    delete this->hoverColorAnim;
    delete this->pressedColorAnim;
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
