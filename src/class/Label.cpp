#include "Label.h"
#include "Painter.h"
#include "PixelMap.h"
#include "Size.h"

void Label::paintEvent(const PaintEvent &event)
{
    PixelMap pm(this->getRect().getSize());
    auto &painter = pm.beginPaint();

    // 绘制位图内容
    painter.setPenColor(Color::White);
    painter.setFont(style.fontName, style.fontSize);
    painter.setFontItalic(style.italic);
    painter.setFontWeight(style.weight);
    auto textRect = painter.rect().adjusted(
        leftpadding_, toppadding_,
        -rightpadding_, -bottompadding_);
    TextHAlign hAlign;
    TextVAlign vAlign;
    if (alignment_ & Label::Left && !(alignment_ & Label::Right))
        hAlign = TextHAlign::Left;
    else if (alignment_ & Label::Right && !(alignment_ & Label::Left))
        hAlign = TextHAlign::Right;
    else if (alignment_ & Label::Center)
        hAlign = TextHAlign::Center;
    else
        hAlign = TextHAlign::Left;
    if (alignment_ & Label::Top && !(alignment_ & Label::Bottom))
        vAlign = TextVAlign::Top;
    else if (alignment_ & Label::Bottom && !(alignment_ & Label::Top))
        vAlign = TextVAlign::Bottom;
    else if (alignment_ & Label::Middle)
        vAlign = TextVAlign::Middle;
    else
        vAlign = TextVAlign::Middle;
    painter.setTextAlign(hAlign, vAlign);
    painter.drawText(textRect, text_);

    pm.endPaint();

    // 将位图绘制到屏幕上
    auto &painter2 = event.beginPaint(this);
    painter2.setBrushColor(style.textColor);
    painter2.drawPixelMap(
        painter2.rect().getTopLeft(), pm, BlendMode::DSna);
    painter2.drawPixelMap(
        painter2.rect().getTopLeft(),pm,BlendMode::DPSao);
    event.endPaint();
}

Label::Label(const Rect &rect, Block *parent)
    : Block(rect, parent), text_(L"Label"),
      alignment_(Label::Left | Label::Middle),
      leftpadding_(0), toppadding_(0),
      rightpadding_(0), bottompadding_(0)
{
}

void Label::setText(const std::wstring &text)
{
    text_ = text;
}

const std::wstring &Label::getText() const
{
    return text_;
}

void Label::setAlignment(int alignment)
{
    alignment_ = alignment;
}

int Label::getAlignment() const
{
    return alignment_;
}

void Label::setPadding(int left, int top, int right, int bottom)
{
    this->leftpadding_ = left;
    this->toppadding_ = top;
    this->rightpadding_ = right;
    this->bottompadding_ = bottom;
}

int &Label::leftPadding()
{
    return leftpadding_;
}

int &Label::topPadding()
{
    return toppadding_;
}

int &Label::rightPadding()
{
    return rightpadding_;
}

int &Label::bottomPadding()
{
    return bottompadding_;
}

const int &Label::leftPadding() const
{
    return leftpadding_;
}

const int &Label::topPadding() const
{
    return toppadding_;
}

const int &Label::rightPadding() const
{
    return rightpadding_;
}

const int &Label::bottomPadding() const
{
    return bottompadding_;
}