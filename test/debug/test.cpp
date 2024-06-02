#include "App.h"
#include "Block.h"
#include "Rect.h"
#include "radiobox.h"
#include "checkbox.h"
#include "button.h"
#include "label.h"
#include "menubox.h"

class Window : public Block
{
    Label *label[3];
    RadioBoxGroup *radioboxGroup[2];
    RadioBox *radiobox[6];
    CheckBox *checkbox[3];
    Button *button;

    MenuBox *menuBox[3];
    MenuItem *menuItem[15];
    Divider *divider[2];

protected:
    void mousePressEvent(const Point &pos, MouseButton button) override
    {
        if (button == MouseButton::Right)
        {
            menuBox[0]->show(pos);
        }
        return Block::mousePressEvent(pos, button);
    }

public:
    Window(const Rect &rect) : Block(rect)
    {
        for (int i = 0; i < 3; i++)
        {
            menuBox[i] = new MenuBox(Rect(0, 0, 100, 0), this);
        }
        for (int i = 0; i < 15; i++)
        {
            menuItem[i] = new MenuItem{
                Rect{0, 0, 0, 20},
                menuBox[i / 5],
            };
        }
        divider[0] = new Divider(menuBox[0]);
        divider[1] = new Divider(menuBox[2]);

        menuBox[0]->addItem(menuItem[0]);
        menuBox[0]->addItem(menuItem[1]);
        menuBox[0]->addItem(menuItem[2]);
        menuBox[0]->addDivider(divider[0]);
        menuBox[0]->addItem(menuItem[3]);
        menuBox[0]->addItem(menuItem[4]);
        menuBox[1]->addItem(menuItem[5]);
        menuBox[1]->addItem(menuItem[6]);
        menuBox[1]->addItem(menuItem[7]);

        menuBox[1]->addItem(menuItem[8]);
        menuBox[1]->addItem(menuItem[9]);
        menuBox[2]->addItem(menuItem[10]);

        menuBox[2]->addItem(menuItem[11]);
        menuBox[2]->addItem(menuItem[12]);
        menuBox[2]->addItem(menuItem[13]);
        menuBox[2]->addDivider(divider[1]);
        menuBox[2]->addItem(menuItem[14]);

        menuItem[2]->addChildMenu(menuBox[1]);
        menuItem[6]->addChildMenu(menuBox[2]);

        label[0] = new Label(Rect(50, 50, 300, 25), this);
        radioboxGroup[0] = new RadioBoxGroup();
        for (int i = 0; i < 3; i++)
        {
            radiobox[i] = new RadioBox(Rect(50 + i * 100, 80, 100, 30), *radioboxGroup[0], this);
        }
        label[1] = new Label(Rect(50, 110, 300, 25), this);
        radioboxGroup[1] = new RadioBoxGroup();
        for (int i = 3; i < 6; i++)
        {
            radiobox[i] = new RadioBox(Rect(50 + (i - 3) * 100, 140, 100, 30), *radioboxGroup[1], this);
        }
        label[2] = new Label(Rect(50, 170, 300, 25), this);
        for (int i = 0; i < 3; i++)
        {
            checkbox[i] = new CheckBox(Rect(50 + i * 100, 200, 100, 30), this);
        }

        button = new Button(Rect(250, 250, 100, 30), this);

        label[0]->setText(L"最好的语言是什么？");
        radiobox[0]->setText(L"C++");
        radiobox[1]->setText(L"Java");
        radiobox[2]->setText(L"Python");
        label[1]->setText(L"最喜欢的颜色是？");
        radiobox[3]->setText(L"红色");
        radiobox[4]->setText(L"蓝色");
        radiobox[5]->setText(L"绿色");
        label[2]->setText(L"你喜欢哪种动物？");
        checkbox[0]->setText(L"狗");
        checkbox[1]->setText(L"猫");
        checkbox[2]->setText(L"鸟");

        button->setText(L"提交");
    }
    ~Window() override
    {
        delete label[0];
        delete label[1];
        delete label[2];
        delete radiobox[0];
        delete radiobox[1];
        delete radiobox[2];
        delete radiobox[3];
        delete radiobox[4];
        delete radiobox[5];
        delete checkbox[0];
        delete checkbox[1];
        delete checkbox[2];
        delete button;
    }
};

int main()
{
    Window window(Rect(0, 0, 400, 320));
    App app{&window};
    App::setTitle(L"综合功能测试");
    app.run();
    return 0;
}