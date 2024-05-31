// 按钮类使用示例
#include "button.h"
#include "App.h"

int main()
{
    Block block{Rect{0, 0, 1000, 600}};
    Button button{Rect{100, 100, 200, 50}, &block};
    Button button2{Rect{100, 170, 200, 50}, &block};
    button2.setText(L"Second Button");
    Button button3{Rect{100, 240, 200, 50}, &block};
    button3.setDisabled(true);
    button.clicked.connect([]()
                           { std::wcout << L"Button clicked!" << std::endl; });
    button2.clicked.connect([]()
                            { std::wcout << L"Button 2 clicked!" << std::endl; });
    button3.clicked.connect([]()
                            { std::wcout << L"Button 3 clicked!" << std::endl; });
    App app{&block};
    app.run();
    return 0;
}