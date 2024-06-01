#include "menubox.h"
#include "App.h"
#include "Painter.h"

class Window : public Block
{
    MenuBox *menuBox_;
    MenuItem *menuItems_[5];
    Divider *divider_;

protected:
    void paintEvent(const PaintEvent &event) override
    {
        auto &painter = event.beginPaint(this);
        painter.drawText(0, 0, std::to_wstring(App::getFps()));
        event.endPaint();
        return Block::paintEvent(event);
    }
    void mousePressEvent(const Point &pos, MouseButton button) override
    {
        if (button == MouseButton::Right && this->rect().contains(pos))
        {
            menuBox_->show(pos);
        }
        return Block::mousePressEvent(pos, button);
    }

public:
    Window(const Rect &rect, Block *parent = nullptr)
        : Block(rect, parent)
    {
        menuBox_ = new MenuBox(Rect(0, 0, 100, 20), this);
        menuItems_[0] = new MenuItem(Rect(0, 0, 100, 20), menuBox_);
        menuItems_[0]->setText(L"File");
        menuItems_[1] = new MenuItem(Rect(0, 0, 100, 20), menuBox_);
        menuItems_[1]->setText(L"Edit");
        menuItems_[2] = new MenuItem(Rect(0, 0, 100, 20), menuBox_);
        menuItems_[2]->setText(L"View");
        menuItems_[3] = new MenuItem(Rect(0, 0, 100, 20), menuBox_);
        menuItems_[3]->setText(L"Help");
        menuItems_[4] = new MenuItem(Rect(0, 0, 100, 20), menuBox_);
        menuItems_[4]->setText(L"Exit");
        divider_ = new Divider(this->menuBox_);
        this->menuBox_->addItem(menuItems_[0]);
        this->menuBox_->addItem(menuItems_[1]);
        this->menuBox_->addItem(menuItems_[2]);
        this->menuBox_->addDivider(divider_);
        this->menuBox_->addItem(menuItems_[3]);
        this->menuBox_->addItem(menuItems_[4]);
    }
    ~Window() override
    {
        delete menuBox_;
        for (int i = 0; i < 5; i++)
            delete menuItems_[i];
        delete divider_;
    }
};

int main()
{
    Window window(Rect(0, 0, 1000, 600));
    App app{&window};
    App::setFps(200);
    app.run();
    return 0;
}