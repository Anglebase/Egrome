#include "App.h"
#include "Block.h"
#include "Button.h"
#include "PaintEvent.h"
#include "Painter.h"
#include <iostream>

class Window :public Block {
protected:
    void paintEvent(PaintEvent* event) override {
        auto& painter = event->beginPaint(this);

        painter.clear(0xffffff_rgb);
        painter.setFontFamily(L"楷体");

        event->endPaint(painter);
    }
private:
    Button* button;
public:
    Window(const Rect& rect, Block* parent = nullptr)
        :Block(rect, parent) {
        this->button = new Button(Rect(10, 10, 200, 90), this);
        this->button->setText(L"Click me!点击");
        this->button->clicked.connect(
            [this](const Point&) {
                std::cout << "Button clicked!" << std::endl;
            });
        this->button->setTriggerButton(MouseButton::Right);
        this->button->setTriggerState(ButtonState::Released);
    }
    ~Window() {
        delete this->button;
    }
};

int main() {
    Window window(Rect(100, 100, 900, 600));
    App app{ &window };
    app.run();
    return 0;
}