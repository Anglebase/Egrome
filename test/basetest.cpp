#include "App.h"
#include "PaintEvent.h"
#include "Painter.h"

class Window :public Block {
    void paintEvent(PaintEvent& event) override {
        auto& painter = event.beginPaint(this);
        painter.drawRect(Rect(100, 100, 100, 100));
        event.endPaint(painter);
    }
public:
    Window(const Rect& rect, Block* parent = nullptr) :Block(rect, parent) {

    }
};

int main() {
    Window block{ Rect(0,0,800,600) };
    App app{ block };
    app.run();
    return 0;
}