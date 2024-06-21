#include "Block.h"

void Block::paintEvent(const PaintEvent& event) {}
void Block::mousePressEvent(const MousePressEvent& event) {}
void Block::mouseMoveEvent(const MouseMoveEvent& event) {}
void Block::mouseWheelEvent(const MouseWheelEvent& event) {}
void Block::mouseReleaseEvent(const MouseReleaseEvent& event) {}
void Block::keyPressEvent(const KeyPressEvent& event) {}
void Block::keyReleaseEvent(const KeyReleaseEvent& event) {}
void Block::inputEvent(const InputEvent& event) {}

Block::Block(const Rect& rect, Block* parent = nullptr)
    :rect_(rect), parent_(parent), foreach_(true) {
    if (this->parent_) {
        this->parent_->addChild(this);
        // 若存在父对象，则将自身的坐标转换到父对象坐标系下
        this->rect_.topLeft() =
            (Point)this->parent_->rect().topLeft() +
            (Point)this->rect_.topLeft();
    }
    else {
        // 若不存在父对象，则置坐标为(0,0)
        this->rect_.topLeft() = Point(0, 0);
    }
}
Block::~Block() = default;

Rect& Block::rect() { return this->rect_; }
const Rect& Block::rect() const { return this->rect_; }

Block* Block::parent() {
    return this->parent_;
}

std::set<Block*>& Block::children() {
    return this->children_;
}

void Block::setParent(Block* parent) {
    if (this->parent_) {
        this->parent_->removeChild(this);
        this->parent_ = parent;
        this->parent_->addChild(this);
    }
}

void Block::addChild(Block* child) {
    this->children_.insert(child);
}

void Block::removeChild(Block* child) {
    this->children_.erase(child);
}

void Block::stopForeach() {
    this->foreach_ = false;
}
void Block::resetForeach() {
    this->foreach_ = true;
}

bool Block::isForeach() const {
    return this->foreach_;
}
