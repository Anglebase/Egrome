#include "Click.h"
#include "MousePressEvent.h"
#include "MouseReleaseEvent.h"

void Click::mousePressEvent(MousePressEvent* event) {
    return Click::mouseClickEvent(dynamic_cast<MouseKeyEvent*>(event));
}

void Click::mouseReleaseEvent(MouseReleaseEvent* event) {
    return Click::mouseClickEvent(dynamic_cast<MouseKeyEvent*>(event));
}

void Click::mouseClickEvent(MouseKeyEvent* event) {
    if (event->button() == this->button_ && event->state() == this->state_) {
        if (this->isContains(event->position())) {
            this->clicked.emit(event->position());
        }
    }
}

bool Click::isContains(const Point& point) const {
    return this->rect().contains(point);
}

Click::Click(const Rect& rect, Block* parent)
    : Block(rect, parent),
    button_(MouseButton::Left), state_(ButtonState::Pressed) {}

Click::~Click() = default;

void Click::setTriggerButton(MouseButton button) {
    this->button_ = button;
}

void Click::setTriggerState(ButtonState state) {
    this->state_ = state;
}
