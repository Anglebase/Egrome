#pragma once

#include "../view/Block.h"
#include "../view/Color.h"

class Slider : public Block
{
    double minValue_;
    double maxValue_;
    double value_;

    Color barColor_{Color::Blue};
    Color handleColor_{Color::White};

protected:
    void paintEvent(const PaintEvent &event) override;
    void mousePressEvent(const Point &pos, MouseButton button) override;
    void mouseMoveEvent(const Point &pos) override;
    void mouseReleaseEvent(const Point &pos, MouseButton button) override;

public:
    Slider(const Rect &rect, Block *parent = nullptr);
    ~Slider() override = default;
    
    std::pair<double, double> getRange() const;
    void setRange(double minValue, double maxValue);
    double getValue() const;
    void setValue(double value);

    void setBarColor(const Color &color);
    void setHandleColor(const Color &color);
};