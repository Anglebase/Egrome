#include "checkbox.h"
#include "Painter.h"
#include "Size.h"

void Checkbox::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);
    Rect textrect = painter.rect().adjusted(
        4 + this->boxSize_, 0, 0, 0);
    Rect boxrect = painter.rect().adjusted(
        0, 0,
        -textrect.width(), 0);
    painter.setPenColor(this->textColor_);
    painter.setTextAlign(TextHAlign::Left, TextVAlign::Center);
    painter.drawText(textrect, this->text_);
    Rect paintrect = boxrect.centerWith(Size{this->boxSize_, this->boxSize_});
    if (this->hovered_)
    {
        painter.setPenStyle(PenStyle::Dash);
        painter.setPenColor(Color::Gray);
        painter.drawRect(painter.rect());
        painter.setPenStyle(PenStyle::Solid);
    }
    if (this->checked_)
    {
        painter.setBrushColor(this->checkColor_);
        painter.drawFillRect(paintrect);
    }
    painter.setPenColor(this->borderColor_);
    painter.setPenWidth(this->borderWidth_);
    painter.drawRect(paintrect);
    event.endPaint();
}

void Checkbox::mousePressEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left && this->rect().contains(pos))
    {
        this->checked_ = !this->checked_;
        this->checkedChanged.emit(this->checked_);
    }
    return Block::mousePressEvent(pos, button);
}

Checkbox::Checkbox(const Rect &rect, Block *parent)
    : Block(rect, parent),
      checked_(false),
      checkColor_(Color::White),
      borderColor_(Color::White),
      borderWidth_(1),
      textColor_(Color::White),
      boxSize_(10),
      text_(L"Checkbox")
{
    this->onEnter.connect([this]()
                          { this->hovered_ = true; });
    this->onLeave.connect([this]()
                          { this->hovered_ = false; });
}

bool Checkbox::isChecked() const
{
    return this->checked_;
}

void Checkbox::setChecked(bool checked)
{
    this->checked_ = checked;
}

void Checkbox::setText(const std::wstring &text)
{
    this->text_ = text;
}

void Checkbox::setTextColor(const Color &color)
{
    this->textColor_ = color;
}

void Checkbox::setCheckColor(const Color &color)
{
    this->checkColor_ = color;
}

void Checkbox::setBorderColor(const Color &color)
{
    this->borderColor_ = color;
}

void Checkbox::setBorderWidth(int width)
{
    this->borderWidth_ = width;
}

void Checkbox::setBoxSize(int size)
{
    this->boxSize_ = size;
}