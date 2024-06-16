#include "Drag.h"
#include "App.h"

void Drag::mousePressEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left)
    {
        if (this->rect().contains(pos))
        {
            switch (this->ref_)
            {
            case Ref::Global:
            {
                this->beginPos_ = App::getMousePos();
                this->thisPos_ = this->rect().getTopLeft();
            }
            break;
            case Ref::Window:
            {
                this->beginPos_ = pos;
                this->thisPos_ = this->rect().getTopLeft();
            }
            break;
            }
        }
    }
    return Block::mousePressEvent(pos, button);
}

void Drag::mouseMoveEvent(const Point &pos)
{
    if (this->beginPos_.has_value())
    {
        Point delta;
        switch (this->ref_)
        {
        case Ref::Global:
        {
            Point globalPos = App::getMousePos();
            if (this->xEnabled_)
                delta.x() = globalPos.x() - this->beginPos_.value().x();
            if (this->yEnabled_)
                delta.y() = globalPos.y() - this->beginPos_.value().y();
        }
        break;
        case Ref::Window:
        {
            if (this->xEnabled_)
                delta.x() = pos.x() - this->beginPos_.value().x();
            if (this->yEnabled_)
                delta.y() = pos.y() - this->beginPos_.value().y();
        }
        break;
        }
        this->rect().setTopLeft(this->thisPos_.value() + delta);
        this->dragged.emit(this->rect().getTopLeft());
    }
    return Block::mouseMoveEvent(pos);
}

void Drag::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left)
    {
        this->beginPos_ = std::nullopt;
        this->thisPos_ = std::nullopt;
        this->released.emit();
    }
    return Block::mouseReleaseEvent(pos, button);
}

Drag::Drag(const Rect &rect, Block *parent)
    : Block(rect, parent)
{
}

Drag::~Drag()
{
}

void Drag::setEnabled(bool x, bool y)
{
    this->xEnabled_ = x;
    this->yEnabled_ = y;
}

bool Drag::isXEnabled() const
{
    return this->xEnabled_;
}

bool Drag::isYEnabled() const
{
    return this->yEnabled_;
}

void Drag::setReference(Ref ref)
{
    this->ref_ = ref;
}
