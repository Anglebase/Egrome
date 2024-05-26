#include <iostream>
#include "core.h"
#include "view.h"

class Window : public Block
{
private:
    Animation<long> animation;

protected:
    void paint(const PaintEvent &event) const override
    {
        auto &painter = event.beginPaint(this);
        painter.setPenColor(0xffffff);
        painter.drawText(animation.value(), 20, std::to_wstring(App::getFps()));
        return Block::paint(event);
    }
    void mousePressEvent(const Point &pos, MouseButton button) override
    {
        if (button == MouseButton::Left)
            animation.start();
        if (button == MouseButton::Right)
            animation.stop();
        if (button == MouseButton::Middle)
            animation.run();
    }

public:
    Window(const Rect &rect, Block *parent = nullptr)
        : Block(rect, parent)
    {
        using namespace std::chrono_literals;
        animation.set(20, 980, 5s);
        onNext.connect([this]()
                       { this->animation.reset(); });
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
