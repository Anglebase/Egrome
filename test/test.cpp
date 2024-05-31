#include "App.h"
#include "button.h"

int main()
{
    Block block{Rect{10, 10, 100, 100}};
    Button button{Rect{20, 20, 80, 80}, &block};
    App app{&block};
    app.run();
    return 0;
}