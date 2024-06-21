#pragma once

#include "./Block.h"

class App final {
public:
    static void quit(int code);
private:
    Block* root_;
private:
    static int fps_;
public:
    static float getFps();
    static void setFps(int fps);
    static int getSetFps();
public:
    App(Block* root);
    ~App();
    void run();
};
