#include "App.h"
#include "Block.h"
#include "Painter.h"
#include "PixelMap.h"

class Window : public Block
{
    PixelMap m_pixelMap;

protected:
    void paintEvent(const PaintEvent &event) override
    {
        auto &painter = event.beginPaint(this);
        if (!m_pixelMap.isNull())
            // painter.drawPixelMap(0, 0, m_pixelMap);
            painter.drawPixelMap({0, 0, 100, 100}, m_pixelMap);
        event.endPaint();
    }

public:
    Window(const Rect &rect, Block *parent = nullptr)
        : Block(rect, parent)
    {
        App::windowCreate.connect(
            [this]()
            { this->m_pixelMap = PixelMap::FromFile(R"(C:\Users\Lenovo\Project\.Demo\QQLogin\res\Header.jpg)"); });
    }
    ~Window() override = default;
};

int main()
{
    Window window(Rect(0, 0, 800, 600));
    App app{&window};
    app.run();
    return 0;
}