#include "radiobox.h"
#include "App.h"

class Window : public Block
{
    RadioBox *radiobox1;
    RadioBox *radiobox2;
    RadioBox *radiobox3;

    RadioBoxGroup *radioboxgroup;

public:
    Window(const Rect &rect) : Block(rect)
    {
        radioboxgroup = new RadioBoxGroup();

        radiobox1 = new RadioBox(Rect(10, 10, 100, 20), *radioboxgroup, this);
        radiobox1->setText(L"RadioBox1");
        radiobox2 = new RadioBox(Rect(10, 40, 100, 20), *radioboxgroup, this);
        radiobox2->setText(L"RadioBox2");
        radiobox3 = new RadioBox(Rect(10, 70, 100, 20), *radioboxgroup, this);
        radiobox3->setText(L"RadioBox3");

        radiobox1->selectedChanged.connect(
            [this](bool selected)
            { std::cout << "RadioBox1 selected: " << selected << std::endl; });
        radiobox2->selectedChanged.connect(
            [this](bool selected)
            { std::cout << "RadioBox2 selected: " << selected << std::endl; });
        radiobox3->selectedChanged.connect(
            [this](bool selected)
            { std::cout << "RadioBox3 selected: " << selected << std::endl; });
        
    }
    ~Window()
    {
        delete radioboxgroup;
        delete radiobox1;
        delete radiobox2;
        delete radiobox3;
    }
};

int main()
{
    Window window(Rect(0, 0, 1000, 800));
    App app{&window};
    app.run();
    return 0;
}