#include "App.h"
#include "core/Size.h"
#include "core/Point.h"
#include "core/Rect.h"
#include "view/Block.h"
#include "view/Painter.h"
#include <ege.h>
#include <windows.h>

Block *App::focusBlock = nullptr;
int App::fps_ = 60;

Size App::getWindowSize()
{
    return Size(ege::getwidth(), ege::getheight());
}

void App::setWindowSize(int width, int height)
{
    ege::resizewindow(width, height);
}

void App::setWindowSize(const Size &size)
{
    ege::resizewindow(size.width(), size.height());
}

Point App::getWindowPos()
{
    int x, y, rx, ry;
    ege::getviewport(&x, &y, &rx, &ry);
    return Point(x, y);
}

void App::setWindowPos(int x, int y)
{
    ege::setviewport(x, y,
                     x + ege::getwidth(), y + ege::getheight());
}

void App::setWindowPos(const Point &pos)
{
    ege::setviewport(pos.x(), pos.y(),
                     pos.x() + ege::getwidth(),
                     pos.y() + ege::getheight());
}
void App::setTitle(const std::string &title)
{
    ege::setcaption(title.c_str());
}

void App::setTitle(const std::wstring &title)
{
    ege::setcaption(title.c_str());
}

Point App::getMousePos()
{
    POINT point;
    GetCursorPos(&point);
    return Point(point.x, point.y);
}

void App::setMousePos(int x, int y)
{
    SetCursorPos(x, y);
}

void App::setMousePos(const Point &pos)
{
    SetCursorPos(pos.x(), pos.y());
}

float App::getFps()
{
    return ege::getfps();
}

int App::getSettingFps()
{
    return App::fps_;
}

void App::setFps(int fps)
{
    App::fps_ = fps;
}

void App::setFocusBlock(Block *block)
{
    App::focusBlock = block;
}

Block *App::getFocusBlock()
{
    return App::focusBlock;
}

App::App(Block *block, int flags) : block_(block)
{
    App::focusBlock = block;
    App::fps_ = 60;
    ege::setinitmode(flags | ege::INIT_ANIMATION);
}

App::~App() {}

void App::run()
{
    // 初始化环境
    ege::initgraph(this->block_->rect().width(),
                   this->block_->rect().height());
    ege::setbkmode(TRANSPARENT);
    App::setTitle(L"中文");

    // 事件循环
    PaintEvent paintEvent;
    static Point lastMousePos;
    for (; ege::is_run(); ege::delay_fps(App::fps_))
    {
        // 捕获键盘输入
        if (ege::kbmsg())
        {
            auto keymsg = ege::getkey();
            switch (keymsg.msg)
            {
            case ege::key_msg_down:
                if (App::focusBlock)
                    App::focusBlock->keyPressEvent((Key)keymsg.key, (KeyFlag)keymsg.flags);
                break;
            case ege::key_msg_up:
                if (App::focusBlock)
                    App::focusBlock->keyReleaseEvent((Key)keymsg.key, (KeyFlag)keymsg.flags);
                break;
            case ege::key_msg_char: // 文本输入(输入法输入)
            {
                do
                {
                    if (App::focusBlock)
                        App::focusBlock->InputTextEvent(keymsg.key);
                    keymsg = ege::getkey();
                } while (keymsg.msg == ege::key_msg_char);
            }
            break;
            default:
                break;
            }
            if (ege::kbhit()) // 文本输入(英文、字符和ASCII符号)
            {
                auto ch = ege::getch();
                if (std::isprint(ch))
                    if (App::focusBlock)
                        App::focusBlock->InputTextEvent(ch);
            }
            ege::flushkey();
        }
        // 捕获鼠标输入
        if (ege::mousemsg())
        {
            auto msg = ege::getmouse();
            MouseButton button;
            {
                if (msg.is_left())
                    button = MouseButton::Left;
                else if (msg.is_right())
                    button = MouseButton::Right;
                else if (msg.is_mid())
                    button = MouseButton::Middle;
            }
            if (msg.is_move() && lastMousePos != Point(msg.x, msg.y))
                this->block_->mouseMoveEvent(Point(msg.x, msg.y)),
                    lastMousePos = Point(msg.x, msg.y);
            else if (msg.is_down())
                this->block_->mousePressEvent(Point(msg.x, msg.y), button);
            else if (msg.is_up())
                this->block_->mouseReleaseEvent(Point(msg.x, msg.y), button);
            else if (msg.is_wheel())
                this->block_->mouseWheelEvent(Point(msg.x, msg.y),
                                              msg.wheel > 0 ? MouseWheel::Up : (msg.wheel < 0 ? MouseWheel::Down : MouseWheel::None));
            ege::flushmouse();
        }

        // 更新显示
        this->block_->update();
        ege::cleardevice();
        this->block_->paint(paintEvent);
    }
}

void App::quit(int exitCode)
{
    exit(exitCode);
}
