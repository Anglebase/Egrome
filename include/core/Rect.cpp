#include "Rect.h"

Rect::RectData::RectData(Rect* rect) : rect_(rect) {}

Rect::LeftSide::LeftSide(Rect* rect) : RectData(rect) {}

float Rect::LeftSide::operator=(float value) {
    float old_x = this->rect_->x_;
    this->rect_->x_ = value;
    this->rect_->width_ -= (old_x - value);
    return value;
}

Rect::LeftSide::operator float() const {
    return this->rect_->x_;
}

Rect::RightSide::RightSide(Rect* rect) : RectData(rect) {}

float Rect::RightSide::operator=(float value) {
    float old_x = this->rect_->x_;
    this->rect_->x_ = value - this->rect_->width_;
    this->rect_->width_ = value - old_x;
    return value;
}

Rect::RightSide::operator float() const {
    return this->rect_->x_ + this->rect_->width_;
}

Rect::TopSide::TopSide(Rect* rect) : RectData(rect) {}

float Rect::TopSide::operator=(float value) {
    float old_y = this->rect_->y_;
    this->rect_->y_ = value;
    this->rect_->height_ -= (old_y - value);
    return value;
}

Rect::TopSide::operator float() const {
    return this->rect_->y_;
}

Rect::BottomSide::BottomSide(Rect* rect) : RectData(rect) {}

float Rect::BottomSide::operator=(float value) {
    float old_y = this->rect_->y_;
    this->rect_->y_ = value - this->rect_->height_;
    this->rect_->height_ = value - old_y;
    return value;
}

Rect::BottomSide::operator float() const {
    return this->rect_->y_ + this->rect_->height_;
}

Rect::Center::Center(Rect* rect) : RectData(rect) {}

Point Rect::Center::operator=(const Point& value) {
    float old_x = this->rect_->x_;
    float old_y = this->rect_->y_;
    this->rect_->x_ = value.x() - this->rect_->width_ / 2.0f;
    this->rect_->y_ = value.y() - this->rect_->height_ / 2.0f;
    this->rect_->width_ += (old_x - this->rect_->x_);
    this->rect_->height_ += (old_y - this->rect_->y_);
    return value;
}

Rect::Center::operator Point() const {
    return Point(this->rect_->x_ + this->rect_->width_ / 2.0f, this->rect_->y_ + this->rect_->height_ / 2.0f);
}

Rect::TopLeftCorner::TopLeftCorner(Rect* rect) : RectData(rect) {}

Point Rect::TopLeftCorner::operator=(const Point& value) {
    float old_x = this->rect_->x_;
    float old_y = this->rect_->y_;
    this->rect_->x_ = value.x();
    this->rect_->y_ = value.y();
    this->rect_->width_ += (old_x - this->rect_->x_);
    this->rect_->height_ += (old_y - this->rect_->y_);
    return value;
}

Rect::TopLeftCorner::operator Point() const {
    return Point(this->rect_->x_, this->rect_->y_);
}


Rect::TopRightCorner::TopRightCorner(Rect* rect) : RectData(rect) {}

Point Rect::TopRightCorner::operator=(const Point& value) {
    float old_x = this->rect_->x_;
    float old_y = this->rect_->y_;
    this->rect_->x_ = value.x() - this->rect_->width_;
    this->rect_->y_ = value.y();
    this->rect_->width_ = value.x() - old_x;
    this->rect_->height_ += (old_y - this->rect_->y_);
    return value;
}

Rect::TopRightCorner::operator Point() const {
    return Point(this->rect_->x_ + this->rect_->width_, this->rect_->y_);
}

Rect::BottomLeftCorner::BottomLeftCorner(Rect* rect) : RectData(rect) {}

Point Rect::BottomLeftCorner::operator=(const Point& value) {
    float old_x = this->rect_->x_;
    float old_y = this->rect_->y_;
    this->rect_->x_ = value.x();
    this->rect_->y_ = value.y() - this->rect_->height_;
    this->rect_->width_ += (old_x - this->rect_->x_);
    this->rect_->height_ = value.y() - old_y;
    return value;
}

Rect::BottomLeftCorner::operator Point() const {
    return Point(this->rect_->x_, this->rect_->y_ + this->rect_->height_);
}

Rect::BottomRightCorner::BottomRightCorner(Rect* rect) : RectData(rect) {}

Point Rect::BottomRightCorner::operator=(const Point& value) {
    float old_x = this->rect_->x_;
    float old_y = this->rect_->y_;
    this->rect_->x_ = value.x() - this->rect_->width_;
    this->rect_->y_ = value.y() - this->rect_->height_;
    this->rect_->width_ = value.x() - old_x;
    this->rect_->height_ = value.y() - old_y;
    return value;
}

Rect::BottomRightCorner::operator Point() const {
    return Point(this->rect_->x_ + this->rect_->width_, this->rect_->y_ + this->rect_->height_);
}

Rect::PosData::PosData(Rect* rect) : RectData(rect) {}

Point Rect::PosData::operator=(const Point& value) {
    this->rect_->x_ = value.x();
    this->rect_->y_ = value.y();
    return value;
}

Rect::PosData::operator Point() const {
    return Point(this->rect_->x_, this->rect_->y_);
}

Rect::SizeData::SizeData(Rect* rect) : RectData(rect) {}

Size Rect::SizeData::operator=(const Size& value) {
    this->rect_->width_ = value.width();
    this->rect_->height_ = value.height();
    return value;
}
Rect::SizeData::operator Size() const {
    return Size(this->rect_->width_, this->rect_->height_);
}


Rect::Rect(float x, float y, float width, float height) noexcept
    : x_(x), y_(y), width_(width), height_(height) {}

Rect::~Rect() noexcept = default;

float& Rect::x() noexcept { return this->x_; }
float& Rect::y() noexcept { return this->y_; }
float& Rect::width() noexcept { return this->width_; }
float& Rect::height() noexcept { return this->height_; }

const float& Rect::x() const noexcept { return this->x_; }
const float& Rect::y() const noexcept { return this->y_; }
const float& Rect::width() const noexcept { return this->width_; }
const float& Rect::height() const noexcept { return this->height_; }

Rect::LeftSide Rect::left() noexcept {
    return LeftSide(this);
}
Rect::RightSide Rect::right() noexcept {
    return RightSide(this);
}
Rect::TopSide Rect::top() noexcept {
    return TopSide(this);
}
Rect::BottomSide Rect::bottom() noexcept {
    return BottomSide(this);
}
Rect::Center Rect::center() noexcept {
    return Center(this);
}
Rect::TopLeftCorner Rect::topLeft() noexcept {
    return TopLeftCorner(this);
}
Rect::TopRightCorner Rect::topRight() noexcept {
    return TopRightCorner(this);
}
Rect::BottomLeftCorner Rect::bottomLeft() noexcept {
    return BottomLeftCorner(this);
}
Rect::BottomRightCorner Rect::bottomRight() noexcept {
    return BottomRightCorner(this);
}
Rect::PosData Rect::pos() noexcept {
    return PosData(this);
}
Rect::SizeData Rect::size() noexcept {
    return SizeData(this);
}

float Rect::left() const noexcept {
    return this->x_;
}
float Rect::right() const noexcept {
    return this->x_ + this->width_;
}
float Rect::top() const noexcept {
    return this->y_;
}
float Rect::bottom() const noexcept {
    return this->y_ + this->height_;
}
Point Rect::center() const noexcept {
    return Point(this->x_ + this->width_ / 2.0f, this->y_ + this->height_ / 2.0f);
}
Point Rect::topLeft() const noexcept {
    return Point(this->x_, this->y_);
}
Point Rect::topRight() const noexcept {
    return Point(this->x_ + this->width_, this->y_);
}
Point Rect::bottomLeft() const noexcept {
    return Point(this->x_, this->y_ + this->height_);
}
Point Rect::bottomRight() const noexcept {
    return Point(this->x_ + this->width_, this->y_ + this->height_);
}

Point Rect::pos() const noexcept {
    return Point(this->x_, this->y_);
}
Size Rect::size() const noexcept {
    return Size(this->width_, this->height_);
}