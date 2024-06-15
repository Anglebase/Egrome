#include "Drag.h"
#include "App.h"
#include "Painter.h"
#include "Color.h"

class DragBlock : public Drag
{
protected:
    void paintEvent(const PaintEvent &event) override
    {
        auto &painter = event.beginPaint(this);
        painter.setBrushColor(Color::White);
        painter.drawFillRect(painter.rect());
        event.endPaint();
    }

public:
    DragBlock(const Rect &rect, Block *parent = nullptr)
        : Drag(rect, parent)
    {
    }
    ~DragBlock() {}
};

class Window : public Block
{
    DragBlock *drag;

protected:
    void paintEvent(const PaintEvent &event) override
    {
        auto &painter = event.beginPaint(this);
        painter.setPenColor(Color::White);
        painter.drawText({0,0},std::to_wstring(App::getFps()));
        event.endPaint();
        return Block::paintEvent(event);
    }
public:
    Window(const Rect &rect, Block *parent = nullptr)
        : Block(rect, parent)
    {
        drag = new DragBlock({100, 100, 200, 200}, this);
        // drag->setEnabled(true, false);
        drag->setReference(Ref::Window);
        drag->dragged.connect([this](const Point &pos){
            std::cout << "dragged: " << pos << std::endl;
        });
    }
    ~Window()
    {
        delete drag;
    }
};

int main()
{
    Window window({0, 0, 800, 600});
    App app{&window};
    app.run();
    return 0;
}