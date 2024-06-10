#include "Block.h"
#include "Rect.h"
#include "Point.h"
#include "App.h"

#include "Painter.h"
#include "Color.h"

#include <windows.h>
#include <winuser.h>

void *Block::cursorArrow = CopyCursor(::LoadCursorW(nullptr, IDC_ARROW));
void *Block::cursorCross = CopyCursor(::LoadCursorW(nullptr, IDC_CROSS));
void *Block::cursorHand = CopyCursor(::LoadCursorW(nullptr, IDC_HAND));
void *Block::cursorIBeam = CopyCursor(::LoadCursorW(nullptr, IDC_IBEAM));

void Block::setCursorType(CursorType cursorType)
{
    this->cursorType_ = cursorType;
}

void Block::paintEvent(const PaintEvent &event)
{
    for (auto child = childBlocks_.begin(); child != childBlocks_.end(); ++child)
        (*child)->paintEvent(event);
}

void Block::mousePressEvent(const Point &pos, MouseButton button)
{
    if (rect_.contains(pos))
    {
        if (button == MouseButton::Left)
            onClicked.emit();
        else if (button == MouseButton::Right)
            onMenuClicked.emit();
    }

    for (auto child : childBlocks_)
        child->mousePressEvent(pos, button);
}

void Block::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    for (auto child : childBlocks_)
        child->mouseReleaseEvent(pos, button);
}

void Block::mouseMoveEvent(const Point &pos)
{
    // 此处引发BUG20240529-20，原因不明
    // static Point lastPos;
    if (lastPos_ != pos)
    {
        onMoved.emit(pos - lastPos_);
        if (rect_.contains(pos) && !rect_.contains(lastPos_))
        {
            this->lastCursor_ = CopyCursor(::LoadCursorW(nullptr, IDC_ARROW));
            switch (this->cursorType_)
            {
            case CursorType::Arrow:
                ::SetSystemCursor(CopyCursor((HCURSOR)Block::cursorArrow), 32512);
                break;
            case CursorType::Cross:
                ::SetSystemCursor(CopyCursor((HCURSOR)Block::cursorCross), 32512);
                break;
            case CursorType::Hand:
                ::SetSystemCursor(CopyCursor((HCURSOR)Block::cursorHand), 32512);
                break;
            case CursorType::IBeam:
                ::SetSystemCursor(CopyCursor((HCURSOR)Block::cursorIBeam), 32512);
                break;
            default:
                break;
            }
            onEnter.emit();
        }
        else if (!rect_.contains(pos) && rect_.contains(lastPos_))
        {
            ::SetSystemCursor((HCURSOR)this->lastCursor_, 32512);
            onLeave.emit();
        }
    }

    lastPos_ = pos;
    for (auto child : childBlocks_)
        child->mouseMoveEvent(pos);
}

void Block::mouseWheelEvent(const Point &pos, MouseWheel wheel)
{
    for (auto child : childBlocks_)
        child->mouseWheelEvent(pos, wheel);
}

void Block::keyPressEvent(Key key, KeyFlag flag)
{
    if (key == Key::Enter)
        onNext.emit();
    for (auto child : childBlocks_)
        child->keyPressEvent(key, flag);
}

void Block::keyReleaseEvent(Key key, KeyFlag flag)
{
    for (auto child : childBlocks_)
        child->keyReleaseEvent(key, flag);
}

void Block::InputTextEvent(wchar_t inputChar)
{
    onInputText.emit(inputChar);
    for (auto child : childBlocks_)
        child->InputTextEvent(inputChar);
}

Block::Block(const Rect &rect, Block *parent)
    : rect_(rect), parentBlock_(parent)
{
    if (parent)
    {
        parent->childBlocks_.push_back(this);
        this->rect_.x_ += parent->rect_.x_;
        this->rect_.y_ += parent->rect_.y_;
    }
    else
    {
        this->rect_.x_ = 0;
        this->rect_.y_ = 0;
    }
    this->setZindex(0);
    onClicked.connect(
        [this]()
        {
            auto foucsBlock = App::getFocusBlock();
            if (foucsBlock != this)
            {
                App::setFocusBlock(this);
                foucsBlock->onUnfocused.emit(this);
                this->onFocused.emit(foucsBlock);
            }
        });
}

const Rect &Block::getRect() const
{
    return rect_;
}

void Block::setRect(const Rect &rect)
{
    this->rect_ = rect;
}

Rect &Block::rect() { return rect_; }
const Rect &Block::rect() const { return rect_; }

Block *Block::parent() const
{
    return this->parentBlock_;
}

std::vector<Block *> &Block::childs()
{
    return this->childBlocks_;
}

const std::vector<Block *> &Block::childs() const
{
    return this->childBlocks_;
}

long long Block::zindex() const
{
    return this->zindex_;
}

void Block::setZindex(long long zindex)
{
    this->zindex_ = zindex;
    if (parentBlock_)
        std::sort(parentBlock_->childBlocks_.begin(),
                  parentBlock_->childBlocks_.end(),
                  [](const Block *a, const Block *b)
                  {
                      return a->zindex_ > b->zindex_;
                  });
}
