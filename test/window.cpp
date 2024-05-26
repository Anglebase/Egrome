#include <iostream>
#include "core.h"
#include "view.h"

class Window : public Block
{
private:
    std::wstring text_;

protected:
    // void paint(const PaintEvent &event) const override
    // {
    //     auto &painter = event.beginPaint(this);
    //     painter.setPenColor(0xffffff);
    //     painter.drawText(20, 20, this->text_);
    //     return Block::paint(event);
    // }
    // void mousePressEvent(const Point &pos, MouseButton button) override
    // {
    //     std::cout << "Mouse pressed at " << pos << std::endl;
    //     std::cout << "Button: ";
    //     switch (button)
    //     {
    //     case MouseButton::Left:
    //         std::cout << "Left";
    //         break;
    //     case MouseButton::Middle:
    //         std::cout << "Middle";
    //         break;
    //     case MouseButton::Right:
    //         std::cout << "Right";
    //         break;
    //     }
    //     std::cout << std::endl;
    // }
    // void mouseReleaseEvent(const Point &pos, MouseButton button) override
    // {
    //     std::cout << "Mouse released at " << pos << std::endl;
    //     std::cout << "Button: ";
    //     switch (button)
    //     {
    //     case MouseButton::Left:
    //         std::cout << "Left";
    //         break;
    //     case MouseButton::Middle:
    //         std::cout << "Middle";
    //         break;
    //     case MouseButton::Right:
    //         std::cout << "Right";
    //         break;
    //     }
    //     std::cout << std::endl;
    // }
    // void mouseMoveEvent(const Point &pos) override
    // {
    //     std::cout << "Mouse moved to " << pos << std::endl;
    // }
    // void mouseWheelEvent(const Point &pos, MouseWheel wheel) override
    // {
    //     std::cout << "Mouse wheel at " << pos << std::endl;
    //     std::cout << "Wheel: ";
    //     switch (wheel)
    //     {
    //     case MouseWheel::Up:
    //         std::cout << "Up";
    //         break;
    //     case MouseWheel::Down:
    //         std::cout << "Down";
    //         break;
    //     }
    //     std::cout << std::endl;
    // }
    // void keyPressEvent(Key key, KeyFlag flag) override
    // {
    //     std::cout << "Key pressed: " << (int)key << "'" << (char)key << "'" << std::endl;
    // }
    // void keyReleaseEvent(Key key, KeyFlag flag) override
    // {
    //     std::cout << "Key released: " << (int)key << "'" << (char)key << "'" << std::endl;
    // }
    // void InputTextEvent(int inputChar) override
    // {
    //     std::cout << "Input text: " << (char *)&inputChar;
    //     std::wcout << L" Input(L): " << (wchar_t *)&inputChar;
    //     std::cout << " [Code]: " << inputChar << std::endl;

    //     if (inputChar)
    //         this->text_ += (wchar_t)inputChar;
    // }

public:
    Window(const Rect &rect, Block *parent = nullptr)
        : Block(rect, parent)
    {
        this->text_ = L"Hello, world!";

        onClicked.connect([]()
                          { std::cout << "Clicked!" << std::endl; });
        onMenuClicked.connect([]()
                              { std::cout << "Menu clicked!" << std::endl; });
        onEnter.connect([]()
                        { std::cout << "Enter pressed!" << std::endl; });
        onLeave.connect([]()
                        { std::cout << "Leave!" << std::endl; });
        onFocused.connect([](Block *block)
                          { std::cout << "Focused!" << std::endl; });
        onUnfocused.connect([](Block *block)
                            { std::cout << "Unfocused!" << std::endl; });
        onNext.connect([]()
                       { std::cout << "Enter pressed!" << std::endl; });
        onMoved.connect([](const Point &pos)
                        { std::cout << "Moved to " << pos << std::endl; });
        onInputText.connect([](int inputChar)
                             { std::cout << "Input text: " << (char *)&inputChar << std::endl; });
    }
};

int main()
{
    Window window(Rect(0, 0, 1000, 600));
    App app(&window, InitFlag::Unicode);
    app.run();
    return 0;
}
