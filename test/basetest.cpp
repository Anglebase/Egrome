#include "App.h"

int main() {
    Block block{ Rect(0,0,800,600) };
    App app{ &block };
    app.run();
    return 0;
}