#include "LineEdit.h"
#include "Painter.h"
#include "Color.h"
#include "PixelMap.h"
#include "App.h"
#include "Size.h"

#include <chrono>

void LineEdit::paintEvent(const PaintEvent &event)
{
    PixelMap pm(1, 1);
    auto &painter = pm.beginPaint();
    painter.setFont(this->fontName_, this->fontSize_);
    // 计算所有光标位置
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
    // painter.setFontSize(this->fontSize_);
    pm.setSize(painter.getTextWidth(this->text_),
               painter.getTextHeight(L"_"));
    painter.setPenColor(Color::White);
    painter.drawText(0, 0, this->text_);

    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch().count();

    // 绘制UI
    auto &paint = event.beginPaint(this);
    if (App::getFocusBlock() == this)
        paint.setPenColor(Color::White);
    else
        paint.setPenColor(Color::Gray);
    paint.drawRect(paint.rect());
    // this->offsetX_ = (this->rect().width() - pm.getSize().width()) / 2;
    this->offsetY_ = (this->rect().height() - pm.getSize().height()) / 2;
    paint.drawPixelMap(offsetX_, offsetY_,
                       *pm.clip(Rect{
                           this->clipOffsetX_,
                           0,
                           this->clipWidth_,
                           pm.getSize().height(),
                       }));
    // 绘制光标
    static bool state{false};
    bool s = state;
    if (App::getFocusBlock() == this && ((s = value % 1000 < 500) || this->cursorVisible_))
    {
        if (s != state)
        {
            this->cursorVisible_ = false;
            state = s;
        }
        paint.setPenColor(Color::White);
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
    // 绘制选择区域
    if (this->hasSelect_)
    {
    }
    event.endPaint();
    pm.endPaint();
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
        std::wcout << L"Enter" << std::endl;
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
    if (this->isPressed_)
    {
        this->hasSelect_ = true;
        auto relativePos = pos - this->rect().getTopLeft() - Point(offsetX_, offsetY_);
        auto ais = this->widths_;
        for (auto &e : ais)
            e = abs(e - relativePos.x());
        auto minIndex = std::min_element(ais.begin(), ais.end()) - ais.begin();
        this->selectPos_ = minIndex;
    }
    return Block::mouseMoveEvent(pos);
}

void LineEdit::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left)
    {
        this->isPressed_ = false;
    }
    return Block::mouseReleaseEvent(pos, button);
}

LineEdit::LineEdit(const Rect &rect, Block *parent)
    : Block(rect, parent), text_(L"")
{
    this->cursorPos_.valueChanged.connect(
        [this](int value)
        {
            this->cursorVisible_ = true;
            this->viewChangedFlag_ = true;
            std::cout << "cursorPos: " << value << std::endl;
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
    this->cursorPos_ = this->text_.size();
    this->textChanged.emit(this->text_);
}

void LineEdit::setFont(const std::wstring &fontName, long fontSize)
{
    this->fontName_ = fontName;
    this->fontSize_ = fontSize;
}
