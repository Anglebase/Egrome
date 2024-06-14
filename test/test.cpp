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

        painter.setBrushColor(Color{255, 0, 0});
        painter.drawFillRoundRect(painter.rect(), 20, 10);
        event.endPaint();
    }

public:
    Window(Rect rect, Block *parent = nullptr) : Block(rect, parent) {}
};

int main()
{
    Block block{Rect{0, 0, 1000, 600}};
    Window window{Rect{100, 100, 300, 200}, &block};
    App app{&block};
    app.run();
    return 0;
}