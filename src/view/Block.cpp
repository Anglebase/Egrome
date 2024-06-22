#include "Block.h"
#include <algorithm>

void Block::paintEvent(PaintEvent* event) {}
void Block::mousePressEvent(MousePressEvent* event) {}
void Block::mouseMoveEvent(MouseMoveEvent* event) {}
void Block::mouseWheelEvent(MouseWheelEvent* event) {}
void Block::mouseReleaseEvent(MouseReleaseEvent* event) {}
void Block::keyPressEvent(KeyPressEvent* event) {}
void Block::keyReleaseEvent(KeyReleaseEvent* event) {}
void Block::inputEvent(InputEvent* event) {}

Block::Block(const Rect& rect, Block* parent)
    :rect_(rect), parent_(parent), foreach_(true), zindex_(0) {
    if (this->parent_) {
        this->parent_->addChild(this);
        // 若存在父对象，则将自身的坐标转换到父对象坐标系下
        this->rect_.topLeft() =
            (Point)this->parent_->rect().topLeft() +
            (Point)this->rect_.topLeft();
        std::sort(this->parent_->children_.begin(), this->parent_->children_.end(),
            [](Block* a, Block* b) { return a->zIndex() < b->zIndex(); });
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

std::vector<Block*>& Block::children() {
    return this->children_;
}

void Block::setParent(Block* parent) {
    if (this->parent_) {
        this->parent_->removeChild(this);
        this->parent_ = parent;
        this->parent_->addChild(this);
    }
    std::sort(this->parent_->children_.begin(), this->parent_->children_.end(),
        [](Block* a, Block* b) { return a->zIndex() < b->zIndex(); });
}

void Block::addChild(Block* child) {
    for (auto& c : this->children_) {
        if (c == child) return;
    }
    this->children_.push_back(child);
    std::sort(this->children_.begin(), this->children_.end(),
        [](Block* a, Block* b) { return a->zIndex() < b->zIndex(); });
}

void Block::removeChild(Block* child) {
    for (auto it = this->children_.begin(); it != this->children_.end(); ++it) {
        if (*it == child) {
            this->children_.erase(it);
            return;
        }
    }
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

void Block::setZIndex(long long zindex) {
    this->zindex_ = zindex;
    std::sort(this->parent_->children_.begin(), this->parent_->children_.end(),
        [](Block* a, Block* b) { return a->zIndex() < b->zIndex(); });
}

long long Block::zIndex() const {
    return this->zindex_;
}
