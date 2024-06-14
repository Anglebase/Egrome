#include "App.h"
#include "Block.h"
#include "Painter.h"
#include "Color.h"

class Window : public Block
{
protected:
    void paintEvent(const PaintEvent &event) override
    {
        auto &painter = event.beginPaint(this);
        painter.clear(0xffffffff_rgba);
        painter.setLinerGradient({0, 0}, 0x12345678_rgba,
                                 {20, 20}, 0x87654321_rgba);
        painter.drawFillRoundRect({20, 20, 200, 200}, 10, 5);
        painter.drawFillCircle({100, 100}, 50);
        painter.drawFillRect({150, 150, 100, 100});
        painter.drawFillEllipse({250, 250, 100, 100});
        painter.setPenColor(Color::Black);
        painter.drawBezier({0, 0}, {100, 100},
                           {0, 100}, {100, 0});
        painter.drawFitCurve({
            {100, 100},
            {200, 100},
            {200, 200},
            {100, 200},
        });
        event.endPaint();
        return Block::paintEvent(event);
    }

public:
    Window(const Rect &rect, Block *parent = nullptr)
        : Block(rect, parent) {}
};

int main()
{
    Window window{Rect{0, 0, 800, 600}};
    App app{&window};
    app.run();
    return 0;
}