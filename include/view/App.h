#pragma once

#include "../core/Object.h"
#include "./Block.h"
class String;

class App final : public Object {
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
    static void setTitle(const String& title);
public:
    App(Block& root);
    ~App();
    void run();
};
