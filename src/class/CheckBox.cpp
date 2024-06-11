#include "CheckBox.h"
#include "Painter.h"
#include "Size.h"

void CheckBox::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);
    Rect textrect = painter.rect().adjusted(
        4 + this->style.boxSize, 0, 0, 0);
    Rect boxrect = painter.rect().adjusted(
        0, 0,
        -textrect.width(), 0);
    painter.setPenColor(this->style.textColor);
    painter.setTextAlign(TextHAlign::Left, TextVAlign::Middle);
    painter.drawText(textrect, this->text_);
    Rect paintrect = boxrect.centerWith(Size{this->style.boxSize, this->style.boxSize});
    if (this->hovered_)
    {
        painter.setPenStyle(PenStyle::Dash);
        painter.setPenColor(this->style.hoverColor);
        painter.drawRect(painter.rect());
        painter.setPenStyle(PenStyle::Solid);
    }
    if (this->checked_)
    {
        painter.setBrushColor(this->style.checkColor);
        painter.drawFillRect(paintrect);
    }
    painter.setPenColor(this->style.borderColor);
    painter.setPenWidth(this->style.borderWidth);
    painter.drawRect(paintrect);
    event.endPaint();
}

void CheckBox::mousePressEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left && this->rect().contains(pos))
    {
        this->checked_ = !this->checked_;
        this->checkedChanged.emit(this->checked_);
    }
    return Block::mousePressEvent(pos, button);
}

CheckBox::CheckBox(const Rect &rect, Block *parent)
    : Block(rect, parent),
      checked_(false),
      text_(L"CheckBox")
{
    this->onEnter.connect([this]()
                          { this->hovered_ = true; });
    this->onLeave.connect([this]()
                          { this->hovered_ = false; });
}

bool CheckBox::isChecked() const
{
    return this->checked_;
}

void CheckBox::setChecked(bool checked)
{
    this->checked_ = checked;
}

void CheckBox::setText(const std::wstring &text)
{
    this->text_ = text;
}