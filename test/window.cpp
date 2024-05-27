#include <iostream>
#include "core.h"
#include "view.h"

class Button : public Block
{
    bool isPressed = false;

protected:
    void paint(const PaintEvent &event) const override
    {
        auto &painter = event.beginPaint(this);
        painter.setBrushColor(0x00ffff);
        if (isPressed)
            painter.setPenColor(0xff0000);
        else
            painter.setPenColor(0xffffff);
        painter.setTextAlign(TextHAlign::Center, TextVAlign::Center);
        // painter.setFont("Consolas", 16);
        painter.drawText(painter.rect(), std::to_string(App::getFps()));
        // painter.drawRect(painter.rect());
        return Block::paint(event);
    }
    void mousePressEvent(const Point &pos, MouseButton button) override
    {
        Block::mousePressEvent(pos, button);
        if (!this->rect().contains(pos))
            return;
        if (button == MouseButton::Left)
            isPressed = true;
    }
    void mouseReleaseEvent(const Point &pos, MouseButton button) override
    {
        Block::mouseReleaseEvent(pos, button);
        if (button == MouseButton::Left)
            isPressed = false;
    }

public:
    Button(const Rect &rect, Block *parent = nullptr)
        : Block(rect, parent)
    {
        this->onClicked.connect([]()
                                { std::cout << "Button clicked" << std::endl; });
    }
};

class Window : public Block
{
private:
    Button *button = nullptr;

public:
    Window(const Rect &rect)
        : Block(rect)
    {
        this->button = new Button(Rect(100, 100, 100, 50), this);
    }
    ~Window()
    {
        delete button;
    }
};

int main()
{
    Window window(Rect(0, 0, 1000, 600));
    App app(&window, InitFlag::Unicode);
    App::setFps(60);
    app.run();
    return 0;
}
