#include "RadioBox.h"
#include "Painter.h"

void RadioBox::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);
    auto textrect = painter.rect().adjusted(
        4 + 2 * style.borderRadius_, 0, 0, 0);
    painter.setPenColor(style.textColor_);
    painter.setTextAlign(TextHAlign::Left, TextVAlign::Middle);
    painter.drawText(textrect, text_);
    auto selectrect = painter.rect().adjusted(
        0, 0, -textrect.width(), 0);
    painter.setPenWidth(style.borderWidth_);
    painter.setPenColor(style.borderColor_);
    painter.drawCircle(selectrect.center(), style.borderRadius_);
    if (hovered_)
    {
        painter.setPenColor(this->style.hoverColor_);
        painter.drawRect(painter.rect());
    }
    if (isSelected())
    {
        painter.setBrushColor(style.selectedColor_);
        painter.drawFillCircle(selectrect.center(), style.borderRadius_);
    }
    event.endPaint();
}

void RadioBox::mousePressEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left && this->rect().contains(pos))
    {
        this->setSelected(true);
    }
    return Block::mousePressEvent(pos, button);
}

RadioBox::RadioBox(const Rect &rect, RadioBoxGroup &group, Block *parent)
    : Block(rect, parent), group_(&group),
      text_(L"RadioBox"), hovered_(false)
{
    this->onEnter.connect([this]()
                          { this->hovered_ = true; });
    this->onLeave.connect([this]()
                          { this->hovered_ = false; });
}

void RadioBox::setText(const std::wstring &text)
{
    text_ = text;
}

void RadioBox::setRadioBoxGroup(RadioBoxGroup &group)
{
    group_ = &group;
}

void RadioBox::setSelected(bool selected)
{
    if (selected == this->isSelected())
        return;
    if (selected)
    {
        this->selectedChanged.emit(true);
        if (this->group_->selected_)
            this->group_->selected_->selectedChanged.emit(false);
        this->group_->selectedChanged.emit(this->group_->selected_, this);
        this->group_->selected_ = this;
    }
}

bool RadioBox::isSelected() const
{
    return this->group_->selected_ == this;
}

RadioBox *RadioBoxGroup::selected() const
{
    return selected_;
}
