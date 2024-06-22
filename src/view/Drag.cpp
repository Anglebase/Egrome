#include "Drag.h"
#include "MousePressEvent.h"
#include "MouseReleaseEvent.h"
#include "MouseMoveEvent.h"

void Drag::mousePressEvent(MousePressEvent* event) {
    if (event->button() == this->button_) {
        if (this->isContains(event->position())) {
            this->isDragging_ = true;
            this->relativePos = event->position() - this->rect().position();
            this->dragged.emit(this->rect().position());
        }
    }
}

void Drag::mouseMoveEvent(MouseMoveEvent* event) {
    if (this->isDragging_) {
        this->rect().position() = event->position() - this->relativePos;
    }
}

void Drag::mouseReleaseEvent(MouseReleaseEvent* event) {
    if (event->button() == this->button_) {
        this->isDragging_ = false;
        this->released.emit(this->rect().position());
    }
}

bool Drag::isContains(Point point) const {
    return this->rect().contains(point);
}

Drag::Drag(const Rect& rect, Block* parent)
    : Block(rect, parent), isDragging_(false),
     button_(MouseButton::Left) {}

Drag::~Drag() = default;

bool Drag::isDragging() const {
    return this->isDragging_;
}

void Drag::setTriggerButton(MouseButton button) {
    this->button_ = button;
}
