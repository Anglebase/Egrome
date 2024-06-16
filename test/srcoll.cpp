#include "ScrollView.h"
#include "Block.h"
#include "Painter.h"
#include "PixelMap.h"
#include "App.h"

class Window : public Block
{
    PixelMap m_map;
    ScrollView *m_scroll{nullptr};

public:
    Window(const Rect &rect, Block *parent = nullptr)
        : Block(rect, parent)
    {
        this->m_scroll = new ScrollView(Rect(50, 50, 700, 500), this);
        this->m_scroll->setView(&this->m_map);
        {
            constexpr int x = 0x7;
            this->m_scroll->setHScrollPos(x & 0x1 ? HScrollPos::Top : HScrollPos::Bottom);
            this->m_scroll->setVScrollPos(x & 0x2 ? VScrollPos::Left : VScrollPos::Right);
            this->m_scroll->setFirstScrollType(x & 0x4 ? ScrollType::Horizontal : ScrollType::Vertical);
        }

        App::windowCreate.connect(
            [this]()
            {
                this->m_map = PixelMap::FromFile(
                    LR"(C:\Users\Lenovo\Project\.Demo\QQLogin\res\Header.jpg)")
                    .clip(Rect(0, 0, 680, 600));
                this->m_scroll->updateScroll(); });
    }
    ~Window()
    {
        delete this->m_scroll;
    }
};

int main()
{
    Window window(Rect(0, 0, 800, 600));
    App app{&window};
    app.run();
    return 0;
}