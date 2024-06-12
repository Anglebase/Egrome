#include "LineEdit.h"
#include "Painter.h"
#include "Color.h"
#include "PixelMap.h"
#include "App.h"
#include "Size.h"

#include <chrono>

// 明文显示
void LineEdit::paintText(const PaintEvent &event)
{
    PixelMap pm(1, 1);
    auto &painter = pm.beginPaint();
    painter.setFont(this->style.fontName, this->style.fontSize);
    // 计算以及更新所有光标位置
    if (this->viewChangedFlag_)
    {
        this->viewChangedFlag_ = false;
        std::wstring text{L""};
        this->widths_.clear();
        this->widths_.push_back(-this->clipOffsetX_);
        for (int i = 0; i < this->text_.size(); i++)
        {
            text += this->text_[i];
            this->widths_.push_back(painter.getTextWidth(text) - this->clipOffsetX_);
        }
        auto pixelpos = this->widths_[this->cursorPos_];
        if (pixelpos > this->clipWidth_)
        {
            this->clipOffsetX_ += pixelpos - this->clipWidth_;
        }
        else if (pixelpos < 0)
        {
            this->clipOffsetX_ += pixelpos;
        }
        if (painter.getTextWidth(this->text_) > this->clipWidth_ &&
            painter.getTextWidth(this->text_) - this->widths_[this->cursorPos_] - this->clipOffsetX_ < this->clipWidth_)
        {
            this->clipOffsetX_ = painter.getTextWidth(this->text_) - this->clipWidth_;
        }
        text.clear();
        this->widths_.clear();
        this->widths_.push_back(-this->clipOffsetX_);
        for (int i = 0; i < this->text_.size(); i++)
        {
            text += this->text_[i];
            this->widths_.push_back(painter.getTextWidth(text) - this->clipOffsetX_);
        }
    }
    // 绘制内容
    pm.setSize(painter.getTextWidth(this->text_),
               painter.getTextHeight(L"_"));
    // painter.setBrushColor(this->style.backgroundColor);
    // painter.drawFillRect(painter.rect());
    painter.clear(this->style.backgroundColor);
    painter.setPenColor(this->style.textColor);
    painter.drawText(0, 0, this->text_);

    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch().count();

    // 绘制UI
    auto &paint = event.beginPaint(this);
    paint.setBrushColor(this->style.backgroundColor);
    paint.drawFillRoundRect(paint.rect(),
                            this->style.borderRadius,
                            this->style.borderRadius);
    if (App::getFocusBlock() == this)
        paint.setPenColor(this->style.onFocusBorderColor);
    else
        paint.setPenColor(this->style.offFocusBorderColor);
    paint.setPenWidth(this->style.borderWidth);
    paint.drawRoundRect(paint.rect(),
                        this->style.borderRadius,
                        this->style.borderRadius);
    // this->offsetX_ = (this->rect().width() - pm.getSize().width()) / 2;
    this->offsetY_ = (this->rect().height() - pm.getSize().height()) / 2;
    if (this->clipWidth_ > pm.getSize().width())
    {
        paint.drawPixelMap(offsetX_, offsetY_, pm);
    }
    else
    {
        auto viewPart = pm.clip(Rect{
            this->clipOffsetX_,
            0,
            this->clipWidth_,
            pm.getSize().height(),
        });
        paint.drawPixelMap(offsetX_, offsetY_, viewPart);
    }
    // 绘制光标
    static bool state{false};
    bool s = state;
    if (App::getFocusBlock() == this && ((s = value % 1000 < 500) || this->cursorVisible_))
    {
        paint.setPenColor(this->style.cursorColor);
        paint.setPenWidth(this->style.cursorWidth);
        if (s != state)
        {
            this->cursorVisible_ = false;
            state = s;
        }
        if (this->cursorPos_ == 0)
            paint.drawLine(
                offsetX_,
                offsetY_,
                offsetX_,
                offsetY_ + painter.getTextHeight(L"_"));
        else
        {
            paint.drawLine(
                this->widths_[this->cursorPos_] + offsetX_,
                offsetY_,
                this->widths_[this->cursorPos_] + offsetX_,
                offsetY_ + painter.getTextHeight(L"_"));
        }
    }
    event.endPaint();
    pm.endPaint();
}

// 密文显示
void LineEdit::paintPassword(const PaintEvent &event)
{
    PixelMap pm(1, 1);
    auto &painter = pm.beginPaint();
    painter.setFont(this->style.fontName, this->style.fontSize);

    auto circleWidth = this->style.fontSize / 2;
    // 计算以及更新所有光标位置
    if (this->viewChangedFlag_)
    {
        this->viewChangedFlag_ = false;
        this->widths_.clear();
        this->widths_.push_back(-this->clipOffsetX_);
        for (int i = 1; i <= this->text_.size(); i++)
        {
            this->widths_.push_back(i * circleWidth - this->clipOffsetX_);
        }
        auto pixelpos = this->widths_[this->cursorPos_];
        if (pixelpos > this->clipWidth_)
        {
            this->clipOffsetX_ += pixelpos - this->clipWidth_;
        }
        else if (pixelpos < 0)
        {
            this->clipOffsetX_ += pixelpos;
        }
        if (circleWidth * this->text_.size() > this->clipWidth_ &&
            circleWidth * this->text_.size() - this->widths_[this->cursorPos_] - this->clipOffsetX_ < this->clipWidth_)
        {
            this->clipOffsetX_ = circleWidth * this->text_.size() - this->clipWidth_;
        }
        this->widths_.clear();
        this->widths_.push_back(-this->clipOffsetX_);
        for (int i = 1; i <= this->text_.size(); i++)
        {
            this->widths_.push_back(circleWidth * i - this->clipOffsetX_);
        }
    }
    // 绘制内容
    pm.setSize(circleWidth * this->text_.size(),
               painter.getTextHeight(L"_"));
    // painter.setBrushColor(this->style.backgroundColor);
    // painter.drawFillRect(painter.rect());
    painter.clear(this->style.backgroundColor);
    painter.setBrushColor(this->style.textColor);
    for (int i = 0; i < this->text_.size(); i++)
    {
        painter.drawFillCircle(circleWidth * i + circleWidth / 2,
                               pm.getSize().height() / 2, circleWidth * 2 / 5);
    }

    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch().count();

    // 绘制UI
    auto &paint = event.beginPaint(this);
    paint.setBrushColor(this->style.backgroundColor);
    paint.drawFillRoundRect(paint.rect(),
                            this->style.borderRadius,
                            this->style.borderRadius);
    if (App::getFocusBlock() == this)
        paint.setPenColor(this->style.onFocusBorderColor);
    else
        paint.setPenColor(this->style.offFocusBorderColor);
    paint.setPenWidth(this->style.borderWidth);
    paint.drawRoundRect(paint.rect(),
                        this->style.borderRadius,
                        this->style.borderRadius);
    // this->offsetX_ = (this->rect().width() - pm.getSize().width()) / 2;
    this->offsetY_ = (this->rect().height() - pm.getSize().height()) / 2;
    if (this->clipWidth_ > pm.getSize().width())
    {
        paint.drawPixelMap(offsetX_, offsetY_, pm);
    }
    else
    {
        auto viewPart = pm.clip(Rect{
            this->clipOffsetX_,
            0,
            this->clipWidth_,
            pm.getSize().height(),
        });
        paint.drawPixelMap(offsetX_, offsetY_, viewPart);
    }
    // 绘制光标
    static bool state{false};
    bool s = state;
    if (App::getFocusBlock() == this && ((s = value % 1000 < 500) || this->cursorVisible_))
    {
        paint.setPenColor(this->style.cursorColor);
        paint.setPenWidth(this->style.cursorWidth);
        if (s != state)
        {
            this->cursorVisible_ = false;
            state = s;
        }
        if (this->cursorPos_ == 0)
            paint.drawLine(
                offsetX_,
                offsetY_,
                offsetX_,
                offsetY_ + painter.getTextHeight(L"_"));
        else
        {
            paint.drawLine(
                this->widths_[this->cursorPos_] + offsetX_,
                offsetY_,
                this->widths_[this->cursorPos_] + offsetX_,
                offsetY_ + painter.getTextHeight(L"_"));
        }
    }
    event.endPaint();
    pm.endPaint();
}

void LineEdit::paintEvent(const PaintEvent &event)
{
    if (this->showPlainText_)
        this->paintText(event);
    else
        this->paintPassword(event);
}

void LineEdit::mousePressEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left)
    {
        if (this->rect().contains(pos))
        {
            this->isPressed_ = true;
            this->hasSelect_ = false;
            // 计算光标位置
            auto relativePos = pos - this->rect().getTopLeft() - Point(offsetX_, offsetY_);
            auto ais = this->widths_;
            for (auto &e : ais)
                e = abs(e - relativePos.x());
            auto minIndex = std::min_element(ais.begin(), ais.end()) - ais.begin();
            this->cursorPos_ = minIndex;
        }
    }
    return Block::mousePressEvent(pos, button);
}

void LineEdit::keyPressEvent(Key key, KeyFlag flag)
{
    if (App::getFocusBlock() != this)
        return;
    switch (key)
    {
    case Key::C: // Ctrl + C 复制
        if (flag == KeyFlag::Ctrl)
        {
            App::setCilpboardText(this->text_);
        }
        break;
    case Key::V: // Ctrl + V 粘贴
        if (flag == KeyFlag::Ctrl)
        {
            if (this->cursorPos_ < this->text_.size())
            {
                this->text_.insert(this->cursorPos_, App::getCilpboardText());
                this->cursorPos_ += App::getCilpboardText().size();
            }
            else
            {
                this->text_ += App::getCilpboardText();
                this->cursorPos_ = this->text_.size();
            }
            this->textChanged.emit(this->text_);
        }
        break;
    case Key::X: // Ctrl + X 剪切
        if (flag == KeyFlag::Ctrl)
        {
            App::setCilpboardText(this->text_);
            this->text_.clear();
            this->cursorPos_ = 0;
            this->textChanged.emit(this->text_);
        }
        break;
    case Key::Enter:
        this->textEnter.emit(this->text_);
        break;
    case Key::Left:
        if (this->cursorPos_ > 0)
            this->cursorPos_--;
        break;
    case Key::Right:
        if (this->cursorPos_ < this->text_.size())
            this->cursorPos_++;
        break;
    case Key::Home:
        this->cursorPos_ = 0;
        break;
    case Key::End:
        this->cursorPos_ = this->text_.size();
        break;
    case Key::BackSpace:
        if (this->cursorPos_ > 0)
        {
            this->text_.erase(this->cursorPos_ - 1, 1);
            this->cursorPos_--;
            this->textChanged.emit(this->text_);
        }
        break;
    case Key::Delete:
        if (this->cursorPos_ < this->text_.size())
        {
            this->text_.erase(this->cursorPos_, 1);
            this->textChanged.emit(this->text_);
        }
        break;
    default:
        break;
    }
}

void LineEdit::InputTextEvent(wchar_t inputChar)
{
    if (App::getFocusBlock() != this)
        return;
    switch (inputChar)
    {
    case L'\b':
    case L'\r':
    case L'\n':
        break;
    case L'\t':
        this->text_ += L"    ";
        this->cursorPos_ += 4;
        this->textChanged.emit(this->text_);
        break;
    default:
        if (this->cursorPos_ < this->text_.size())
        {
            this->text_.insert(this->cursorPos_, 1, inputChar);
            this->cursorPos_++;
            this->textChanged.emit(this->text_);
        }
        else if (this->cursorPos_ == this->text_.size())
        {
            this->text_ += inputChar;
            this->cursorPos_++;
            this->textChanged.emit(this->text_);
        }
        break;
    }
}

void LineEdit::mouseMoveEvent(const Point &pos)
{
    using namespace std::chrono_literals;
    if (this->isPressed_)
    {
    }
    return Block::mouseMoveEvent(pos);
}

void LineEdit::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left)
    {
        this->isPressed_ = false;
        if (this->hasSelect_ && this->selectPos_ == this->cursorPos_)
            this->hasSelect_ = false;
    }
    return Block::mouseReleaseEvent(pos, button);
}

LineEdit::LineEdit(const Rect &rect, Block *parent)
    : Block(rect, parent), text_(L"")
{
    this->setCursorType(CursorType::IBeam);
    this->cursorPos_.valueChanged.connect(
        [this](int value)
        {
            this->cursorVisible_ = true;
            this->viewChangedFlag_ = true;
        });
    this->textChanged.connect(
        [this](const std::wstring &text)
        {
            this->viewChangedFlag_ = true;
        });
    this->clipWidth_ = this->rect().width() - 2 * this->offsetX_;
}

void LineEdit::setText(const std::wstring &text)
{
    this->text_ = text;
    this->cursorPos_ = 0;
    this->viewChangedFlag_ = true;
}

const std::wstring &LineEdit::text() const
{
    return this->text_;
}

void LineEdit::setShowPlainText(bool show)
{
    this->showPlainText_ = show;
    this->viewChangedFlag_ = true;
}

bool LineEdit::isShowPlainText() const
{
    return this->showPlainText_;
}
