#include "App.h"
#include "Block.h"
#include "Drag.h"
#include "Click.h"
#include "Hover.h"
#include "PaintEvent.h"
#include "Painter.h"
#include <iostream>

class Button :public Click, public Hover {
protected:
    void paintEvent(PaintEvent* event) override {
        auto& painter = event->beginPaint((Click*)this);
        painter.setBrushColor(0x34284765_rgba);
        painter.drawFillRect(painter.rect());
        event->endPaint(painter);
    }
public:
    Button(const Rect& rect, Block* parent)
        : Click(rect, parent), Hover(rect, parent) {
        this->clicked.connect([](const Point& p) {
            std::cout << "Button clicked at " << p.x() << ", " << p.y() << std::endl;
            });
        this->entered.connect([](const Point& p) {
            std::cout << "Button hovered at " << p.x() << ", " << p.y() << std::endl;
            });
        this->leaved.connect([](const Point& p) {
            std::cout << "Button unhovered at " << p.x() << ", " << p.y() << std::endl;
            });
    }
};

class Box :public Drag {
protected:
    void paintEvent(PaintEvent* event) override {
        auto& painter = event->beginPaint((Click*)this);
        painter.setBrushColor(0x538f75a2_rgba);
        painter.drawFillRect(painter.rect());
        event->endPaint(painter);
    }
public:
    Box(const Rect& rect, Block* parent)
        : Drag(rect, parent) {

    }
};

class Window :public Block {
private:
    Button* button;
    Box* box;

protected:
    void paintEvent(PaintEvent* event) override {
        auto& painter = event->beginPaint((Click*)this);
        painter.clear(0xffffffFF_rgba);
        event->endPaint(painter);
    }
public:
    Window(const Rect& rect)
        : Block(rect) {
        button = new Button(Rect(100, 100, 100, 50), this);
        box = new Box(Rect(200, 200, 100, 100), this);
    }
    ~Window() {
        delete button;
        delete box;
    }
};

int main() {
    Window window(Rect(0, 0, 500, 500));
    App app{ &window };
    app.run();
    return 0;
}