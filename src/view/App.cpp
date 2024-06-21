#include "App.h"
#include <ege.h>
#include <chrono>
#include <cstdlib>
#include <cwctype>

#include "PaintEvent.h"
#include "KeyPressEvent.h"
#include "KeyReleaseEvent.h"
#include "MousePressEvent.h"
#include "MouseReleaseEvent.h"
#include "MouseMoveEvent.h"
#include "MouseWheelEvent.h"
#include "InputEvent.h"

#include "XString.h"

// 以树结构遍历所有Block
template<typename T>
void foreach(Block* root, void(Block::* func)(T), T arg) {
    if (root == nullptr) return;
    (root->*func)(arg);
    if (root->children().empty())return;

    for (auto child : root->children()) {
        foreach<T>(child, func, arg);
        // 若遍历指示器为false，则退出此子树的遍历
        if (!root->isForeach())break;
    }
}

void App::quit(int code) {
    std::exit(code);
}

int App::fps_ = 60;
float App::getFps() { return ege::getfps(); }
void App::setFps(int fps) { App::fps_ = fps; }
int App::getSetFps() { return App::fps_; }

void App::setTitle(const String& title) {
    std::wstring wtitle = (std::wstring)title;
    ege::setcaption(wtitle.c_str());
}

App::App(Block& root) :root_(&root) {}
App::~App() = default;

void App::run() {
    ::SetProcessDPIAware();

    if (this->root_ == nullptr) return;
    ege::initgraph(this->root_->rect_.width(), this->root_->rect_.height());
    ege::setbkmode(TRANSPARENT);
    App::setTitle(L"Egrome");

    for (auto now = std::chrono::steady_clock::now();
        ege::is_run();
        ege::delay_fps(App::fps_), now = std::chrono::steady_clock::now()) {
        // 绘制事件，每帧只执行一次
        PaintEvent paint_event;
        foreach<PaintEvent&>(this->root_, &Block::paintEvent, paint_event);
        // 键鼠事件，每帧尽可能多地执行
        do {
            // 捕获键盘输入
            if (ege::kbmsg()) {
                auto keymsg = ege::getkey();
                switch (keymsg.msg) {
                case ege::key_msg_down:
                {
                    KeyPressEvent keypress_event = {
                        (Key)keymsg.key,
                        static_cast<bool>(keymsg.flags & ege::key_flag_shift),
                        static_cast<bool>(keymsg.flags & ege::key_flag_ctrl),
                    };
                    foreach<const KeyPressEvent&>(this->root_, &Block::keyPressEvent, keypress_event);
                }
                break;
                case ege::key_msg_up:
                {
                    KeyReleaseEvent keyrelease_event = {
                        (Key)keymsg.key,
                        static_cast<bool>(keymsg.flags & ege::key_flag_shift),
                        static_cast<bool>(keymsg.flags & ege::key_flag_ctrl),
                    };
                    foreach<const KeyReleaseEvent&>(this->root_, &Block::keyReleaseEvent, keyrelease_event);
                }
                break;
                case ege::key_msg_char: // 文本输入(输入法输入)
                {
                    InputEvent input_event = {
                        (wchar_t)keymsg.key,
                    };
                    foreach<const InputEvent&>(this->root_, &Block::inputEvent, input_event);
                }
                break;
                default:
                    break;
                }
                if (ege::kbhit()) // 文本输入(ASCII字符)
                {
                    auto ch = ege::getch();
                    if (std::iswprint(ch)) {
                        InputEvent input_event = {
                            (wchar_t)ch,
                        };
                        foreach<const InputEvent&>(this->root_, &Block::inputEvent, input_event);
                    }
                }
            }
            // 捕获鼠标输入
            if (ege::mousemsg()) {
                auto msg = ege::getmouse();
                MouseButton button;
                if (msg.is_left())
                    button = MouseButton::Left;
                else if (msg.is_right())
                    button = MouseButton::Right;
                else if (msg.is_mid())
                    button = MouseButton::Middle;

                if (msg.is_down()) {
                    MousePressEvent mousepress_event = {
                        Point(msg.x, msg.y),
                        button,
                    };
                    foreach<const MousePressEvent&>(this->root_, &Block::mousePressEvent, mousepress_event);
                }
                if (msg.is_up()) {
                    MouseReleaseEvent mouserelease_event = {
                        Point(msg.x, msg.y),
                        button,
                    };
                    foreach<const MouseReleaseEvent&>(this->root_, &Block::mouseReleaseEvent, mouserelease_event);
                }
                if (msg.is_move()) {
                    MouseMoveEvent mousemove_event = {
                        Point(msg.x, msg.y),
                    };
                    foreach<const MouseMoveEvent&>(this->root_, &Block::mouseMoveEvent, mousemove_event);
                }
                if (msg.is_wheel()) {
                    MouseWheelEvent mousewheel_event = {
                        Point(msg.x, msg.y),
                        (msg.wheel > 0
                            ? MouseWheel::Up
                            : (msg.wheel < 0
                                ? MouseWheel::Down
                                : MouseWheel::None)),
                    };
                    foreach<const MouseWheelEvent&>(this->root_, &Block::mouseWheelEvent, mousewheel_event);
                }
            }
        } while (std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::steady_clock::now() - now).count() * App::fps_ < 900);
    }
}