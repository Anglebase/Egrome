#include "App.h"
#include "ProgressBar.h"
#include "Animation.hpp"

class Window : public Block
{
    ProgressBar *progress;
    Animation<double> *animation;

protected:
    void paintEvent(const PaintEvent &event) override
    {

        return Block::paintEvent(event);
    }

public:
    Window(const Rect &rect, Block *parent = nullptr) : Block(rect, parent)
    {
        using namespace std::chrono_literals;
        progress = new ProgressBar(Rect(0, 0, 100, 20), this);
        animation = new Animation<double>{};
        animation->set(0.0, 1.0, 5s);
        animation->start();
        animation.
    }
    ~Window()
    {
        delete progress;
        delete animation;
    }
};