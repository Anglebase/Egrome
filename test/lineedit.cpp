#include "LineEdit.h"
#include "App.h"

int main()
{
    Block block{Rect{0, 0, 800, 600}};
    LineEdit lineEdit{Rect{100, 100, 200, 30}, &block};
    lineEdit.setText(L"Hello World!");
    App app{&block, InitFlag::Unicode};
    app.run();
    return 0;
}