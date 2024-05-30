#include "Block.h"
#include "Rect.h"
#include "Point.h"
#include "App.h"

void Block::paintEvent(const PaintEvent &event)
{
    for (auto child : childBlocks)
        child->paintEvent(event);
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

    for (auto child : childBlocks)
        child->mousePressEvent(pos, button);
}

void Block::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    for (auto child : childBlocks)
        child->mouseReleaseEvent(pos, button);
}

void Block::mouseMoveEvent(const Point &pos)
{
    // 此处引发BUG20240529-20，原因不明
    // static Point lastPos;
    if (lastPos != pos)
    {
        onMoved.emit(pos - lastPos);
        if (rect_.contains(pos) && !rect_.contains(lastPos))
            onEnter.emit();
        else if (!rect_.contains(pos) && rect_.contains(lastPos))
            onLeave.emit();
    }

    lastPos = pos;
    for (auto child : childBlocks)
        child->mouseMoveEvent(pos);
}

void Block::mouseWheelEvent(const Point &pos, MouseWheel wheel)
{
    for (auto child : childBlocks)
        child->mouseWheelEvent(pos, wheel);
}

void Block::keyPressEvent(Key key, KeyFlag flag)
{
    if (key == Key::Enter)
        onNext.emit();
    for (auto child : childBlocks)
        child->keyPressEvent(key, flag);
}

void Block::keyReleaseEvent(Key key, KeyFlag flag)
{
    for (auto child : childBlocks)
        child->keyReleaseEvent(key, flag);
}

void Block::InputTextEvent(int inputChar)
{
    onInputText.emit(inputChar);
    for (auto child : childBlocks)
        child->InputTextEvent(inputChar);
}

Block::Block(const Rect &rect, Block *parent)
    : rect_(rect), parentBlock(parent)
{
    if (parent)
    {
        parent->childBlocks.push_back(this);
        this->rect_.x_ += parent->rect_.x_;
        this->rect_.y_ += parent->rect_.y_;
    }
    else
    {
        this->rect_.x_ = 0;
        this->rect_.y_ = 0;
    }

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