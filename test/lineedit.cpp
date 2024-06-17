#include "LineEdit.h"
#include "App.h"
#include "Label.h"
#include "SignalSlots.hpp"

class Window : public Block
{
    LineEdit *lineEdit;
    Label *label;

protected:
    void keyPressEvent(Key key, KeyFlag flag) override
    {
        if (key == Key::Tab)
        {
            if (App::getFocusBlock() == this)
            {
                this->TabPressed.emit();
                return;
            }
            std::cout << "Tab pressed" << std::endl;
        }
        std::cout << "key pressed: " << (int)key << std::endl;
        return Block::keyPressEvent(key, flag);
    }
signals:
    Signal<void()> TabPressed;

public:
    Window(const Rect &rect, Block *parent = nullptr) : Block(rect, parent)
    {
        lineEdit = new LineEdit(Rect{100, 100, 400, 40}, this);
        label = new Label(Rect{100, 200, 400, 50}, this);
        label->setPadding(0, 0, 0, 0);

        lineEdit->style = {
            .textColor = Color::Black,
            .cursorColor = Color::Black,
            .backgroundColor = 0xFFFFFF_rgb,
            .onFocusBorderColor = Color::LightCyan,
            .offFocusBorderColor = Color::LightRed,
            .borderWidth = 5,
            .borderRadius = 10,
            .cursorWidth = 2,
            .fontName = L"思源黑体",
            .fontSize = 36,
        };
        lineEdit->setShowPlainText(false);

        lineEdit->textEnter.connect(
            [this](const std::wstring &text)
            {
                label->setText(text);
            });
        label->style.fontName = L"思源黑体";
        label->style.fontSize = 36;
        label->setText(L"按Enter显示到此...");

        this->TabPressed.connect([this]()
                                 { this->lineEdit->setShowPlainText(!this->lineEdit->isShowPlainText()); });
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