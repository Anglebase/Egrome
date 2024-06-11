#include "Painter.h"
#include "Button.h"

void Button::paintEvent(const PaintEvent &event)
{
    // 绘制按钮
    auto &painter = event.beginPaint(this);
    painter.setTextAlign(TextHAlign::Center, TextVAlign::Middle);
    // 状态判断与显示
    if (this->isDisabled)
    {
        painter.setBrushColor(this->style.disabledColor);
        painter.setPenColor(this->style.textColor);
    }
    else if (this->isPressed || this->pressedColorAnim->isRunning())
    {
        painter.setBrushColor(this->pressedColorAnim->value());
        painter.setPenColor(this->style.textColor);
    }
    else if (this->isHovered || this->hoverColorAnim->isRunning())
    {
        painter.setBrushColor(this->hoverColorAnim->value());
        painter.setPenColor(this->style.textColor);
    }
    else
    {
        painter.setBrushColor(this->style.backgroundColor);
        painter.setPenColor(this->style.textColor);
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
      isDisabled(false),
      isPressed(false),
      isHovered(false),
      text(L"Button")
{
    using namespace std::chrono_literals;
    // 注册颜色过渡动画
    this->hoverColorAnim = new Animation<Color>({
        .startValue = this->style.backgroundColor,
        .endValue = this->style.hoverColor,
        .duration = 300ms,
        .function = Color::color_lerp,
    });
    this->pressedColorAnim = new Animation<Color>({
        .startValue = this->style.hoverColor,
        .endValue = this->style.pressedColor,
        .duration = 100ms,
        .function = Color::color_lerp,
    });
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

void Button::setDisabled(bool disabled)
{
    this->isDisabled = disabled;
}

void Button::setText(const std::wstring &text)
{
    this->text = text;
}

void Button::updateAnimations()
{
    using namespace std::chrono_literals;
    if (this->hoverColorAnim)
        delete this->hoverColorAnim;
    if (this->pressedColorAnim)
        delete this->pressedColorAnim;
    this->hoverColorAnim = new Animation<Color>({
        .startValue = this->style.backgroundColor,
        .endValue = this->style.hoverColor,
        .duration = 300ms,
        .function = Color::color_lerp,
    });
    this->pressedColorAnim = new Animation<Color>({
        .startValue = this->style.hoverColor,
        .endValue = this->style.pressedColor,
        .duration = 100ms,
        .function = Color::color_lerp,
    });
}
