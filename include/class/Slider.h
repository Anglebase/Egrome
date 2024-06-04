#pragma once

#include "../view/Block.h"
#include "../view/Color.h"

class SliderBar : public Block
{
    double minValue_;
    double maxValue_;
    double value_;


protected:
    void paintEvent(const PaintEvent &event) override;
    void mousePressEvent(const Point& pos, MouseButton button) override;
    void mouseMoveEvent(const Point& pos) override;
    void mouseReleaseEvent(const Point& pos, MouseButton button) override;

public:
    SliderBar(const Rect &rect, Block *parent = nullptr);
    ~SliderBar();
};