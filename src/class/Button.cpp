#include "Button.h"
#include "PaintEvent.h"
#include "Painter.h"
#include "MousePressEvent.h"
#include "MouseReleaseEvent.h"
#include "MouseMoveEvent.h"

void Button::paintEvent(PaintEvent* event) {
    auto& painter = event->beginPaint(this);

    if (this->isHovered_) {
        painter.setBrushColor(0x99999980_rgba);
        painter.drawFillRect(painter.rect());
    }
    if (this->isPressed_) {
        painter.setBrushColor(0x999999c0_rgba);
        painter.drawFillRect(painter.rect());
    }
    painter.setPenColor(0x000000_rgb);
    painter.setFontSize(1_em);
    painter.drawText(painter.rect(), this->text_,
        TextAlign::Center | TextAlign::Middle);

    event->endPaint(painter);
}

void Button::mousePressEvent(MousePressEvent* event) {
    if (this->rect().contains(event->position())) {
        if (event->button() == this->button_) {
            this->isPressed_ = true;
        }
    }
    return Click::mousePressEvent(event);
}

void Button::mouseReleaseEvent(MouseReleaseEvent* event) {
    this->isPressed_ = false;
    if (!this->rect().contains(event->position()))
        this->isHovered_ = false;
    return Click::mouseReleaseEvent(event);
}

void Button::mouseMoveEvent(MouseMoveEvent* event) {
    return Hover::mouseMoveEvent(event);
}

Button::Button(const Rect& rect, Block* parent)
    :Click(rect, parent), Hover(rect, parent), Block(rect, parent),
    text_(L""), isPressed_(false), isHovered_(false) {
    this->entered.connect([this](const Point&) {this->isHovered_ = true;});
    this->leaved.connect(
        [this](const Point&) {this->isHovered_ = this->isPressed_ ? this->isHovered_ : false;});
}

Button::~Button() {

}

void Button::setText(const String& text) {
    this->text_ = text;
}