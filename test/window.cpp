#include "button.h"

int main()
{
    Block block{Rect{0, 0, 1000, 600}};
    Button button{Rect{100, 100, 200, 50}, &block};
    button.setText(L"Click me!");
    button.clicked.connect([]()
                           { std::wcout << L"Button clicked!" << std::endl; });
    button.onEnter.connect([]()
                           { std::wcout << L"Mouse entered button!" << std::endl; });
    button.onLeave.connect([]()
                           { std::wcout << L"Mouse left button!" << std::endl; });

    App app{&block};
    app.run();
    return 0;
}