#include "menubox.h"
#include "App.h"
#include "Painter.h"

class Window : public Block
{
    MenuBox *menuBox_;
    MenuBox *subMenuBox_;
    MenuItem *menuItems_[5];
    MenuItem *subMenuItems_[3];
    Divider *divider_;

protected:
    void paintEvent(const PaintEvent &event) override
    {
        auto &painter = event.beginPaint(this);
        painter.drawText({0, 0}, std::to_wstring(App::getFps()));
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
        menuBox_ = new MenuBox(Rect(0, 0, 200, 0), this);
        menuItems_[0] = new MenuItem(Rect(0, 0, 300, 40), menuBox_);
        menuItems_[0]->setText(L"File");
        menuItems_[1] = new MenuItem(Rect(0, 0, 300, 40), menuBox_);
        menuItems_[1]->setText(L"Edit");
        menuItems_[2] = new MenuItem(Rect(0, 0, 300, 40), menuBox_);
        menuItems_[2]->setText(L"View");
        menuItems_[3] = new MenuItem(Rect(0, 0, 300, 40), menuBox_);
        menuItems_[3]->setText(L"Help");
        menuItems_[4] = new MenuItem(Rect(0, 0, 300, 40), menuBox_);
        menuItems_[4]->setText(L"Exit");

        subMenuBox_ = new MenuBox(Rect(0, 0, 200, 0), this);
        subMenuItems_[0] = new MenuItem(Rect(0, 0, 300, 40), subMenuBox_);
        subMenuItems_[0]->setText(L"Undo");
        subMenuItems_[1] = new MenuItem(Rect(0, 0, 300, 40), subMenuBox_);
        subMenuItems_[1]->setText(L"Redo");
        subMenuItems_[2] = new MenuItem(Rect(0, 0, 300, 40), subMenuBox_);
        subMenuItems_[2]->setText(L"Cut");

        this->subMenuBox_->addItem(subMenuItems_[0]);
        this->subMenuBox_->addItem(subMenuItems_[1]);
        this->subMenuBox_->addItem(subMenuItems_[2]);
        menuItems_[1]->addChildMenu(subMenuBox_);
        divider_ = new Divider(this->menuBox_);
        this->menuBox_->addItem(menuItems_[0]);
        this->menuBox_->addItem(menuItems_[1]);
        this->menuBox_->addItem(menuItems_[2]);
        this->menuBox_->addDivider(divider_);
        this->menuBox_->addItem(menuItems_[3]);
        this->menuBox_->addItem(menuItems_[4]);

        this->menuItems_[0]->clicked.connect(
            [this]()
            { std::cout << "File clicked" << std::endl; });
        this->menuItems_[1]->clicked.connect(
            [this]()
            { std::cout << "Edit clicked" << std::endl; });
        this->menuItems_[2]->clicked.connect(
            [this]()
            { std::cout << "View clicked" << std::endl; });
        this->menuItems_[3]->clicked.connect(
            [this]()
            { std::cout << "Help clicked" << std::endl; });
        this->menuItems_[4]->clicked.connect(
            [this]()
            { std::cout << "Exit clicked" << std::endl; });
        this->subMenuItems_[0]->clicked.connect(
            [this]()
            { std::cout << "Undo clicked" << std::endl; });
        this->subMenuItems_[1]->clicked.connect(
            [this]()
            { std::cout << "Redo clicked" << std::endl; });
        this->subMenuItems_[2]->clicked.connect(
            [this]()
            { std::cout << "Cut clicked" << std::endl; });
    }
    ~Window() override
    {
        delete menuBox_;
        for (int i = 0; i < 5; i++)
            delete menuItems_[i];
        delete divider_;
        for (int i = 0; i < 3; i++)
            delete subMenuItems_[i];
        delete subMenuBox_;
    }
};

int main()
{
    Window window(Rect(0, 0, 1000, 600));
    App app{&window};
    app.run();
    return 0;
}