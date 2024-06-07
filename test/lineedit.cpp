#include "LineEdit.h"
#include "App.h"
#include "Label.h"

class Window : public Block
{
    LineEdit *lineEdit;
    Label *label;

public:
    Window(const Rect &rect, Block *parent = nullptr) : Block(rect, parent)
    {
        lineEdit = new LineEdit(Rect{100, 100, 400, 40}, this);
        label = new Label(Rect{100, 200, 400, 50}, this);
        label->setPadding(0, 0, 0, 0);
        lineEdit->setFont(L"思源黑体", 36);
        lineEdit->textEnter.connect(
            [this](const std::wstring &text)
            {
                label->setText(text);
            });
        label->setFont(L"思源黑体", 36);
        label->setText(L"按Enter显示到此...");
    }
    ~Window()
    {
        delete lineEdit;
        delete label;
    }
};

int main()
{
    Window block{Rect{0, 0, 800, 600}};
    App app{&block};
    app.run();
    return 0;
}