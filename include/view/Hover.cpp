#include "Hover.h"
#include "MouseMoveEvent.h"

void Hover::mouseMoveEvent(MouseMoveEvent* event) {
    if (this->hasPos) {
        if (this->isContains(event->position())
            && !this->isContains(this->lastPos)) {
            this->entered.emit(event->position());
        }
        if (!this->isContains(event->position())
            && this->isContains(this->lastPos)) {
            this->leaved.emit(this->lastPos);
        }
    }
    this->lastPos = event->position();
    this->hasPos = true;
}

bool Hover::isContains(const Point& point) {
    return this->rect().contains(point);
}

Hover::Hover(const Rect& rect, Block* parent)
    : Block(rect, parent), hasPos(false), lastPos(Point()) {}

Hover::~Hover() = default;
