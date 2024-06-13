#include "App.h"
#include "Size.h"
#include "Point.h"
#include "Rect.h"
#include "Block.h"
#include "Painter.h"
#include "Exception.h"
#include <ege.h>
#include <windows.h>
#include <chrono>

Block *App::focusBlock = nullptr;
int App::fps_ = 60;

App *App::instance_ = nullptr;

Size App::getScreenSize()
{
    return Size{
        ::GetSystemMetrics(SM_CXSCREEN),
        ::GetSystemMetrics(SM_CYSCREEN),
    };
}

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
    RECT rect;
    ::GetWindowRect(ege::getHWnd(), &rect);
    return Point(rect.left, rect.top);
}

void App::setWindowPos(int x, int y)
{
    ege::movewindow(x, y);
}

void App::setWindowPos(const Point &pos)
{
    ege::movewindow(pos.x(), pos.y());
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
    ::GetCursorPos(&point);
    return Point(point.x, point.y);
}

void App::setMousePos(int x, int y)
{
    ::SetCursorPos(x, y);
}

void App::setMousePos(const Point &pos)
{
    ::SetCursorPos(pos.x(), pos.y());
}

std::wstring App::getCilpboardText()
{
    HWND hWnd = ege::getHWnd();
    ::OpenClipboard(hWnd);
    HANDLE hClipMemory = ::GetClipboardData(CF_UNICODETEXT);
    DWORD dwLength = ::GlobalSize(hClipMemory);
    LPBYTE lpClipMemory = (LPBYTE)::GlobalLock(hClipMemory);
    auto text = std::wstring((wchar_t *)lpClipMemory);
    ::GlobalUnlock(hClipMemory);
    ::CloseClipboard();
    return text;
}

void App::setCilpboardText(const std::wstring &text)
{
    DWORD dwLength = text.size() + 1;
    HANDLE hGlobalMemory = ::GlobalAlloc(GHND, dwLength * 2 + 2);
    LPBYTE lpGlobalMemory = (LPBYTE)::GlobalLock(hGlobalMemory);
    for (int i = 0; i < dwLength; i++)
    {
        *lpGlobalMemory++ = (text[i] & 0xff);
        *lpGlobalMemory++ = (text[i] >> 8) & 0xff;
    }
    *lpGlobalMemory++ = (L'\0' & 0xff);
    *lpGlobalMemory = (L'\0' >> 8) & 0xff;
    ::GlobalUnlock(hGlobalMemory);
    HWND hWnd = ege::getHWnd();
    ::OpenClipboard(hWnd);
    ::EmptyClipboard();
    ::SetClipboardData(CF_UNICODETEXT, hGlobalMemory);
    ::CloseClipboard();
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

void App::setMinimize()
{
    ::ShowWindow(ege::getHWnd(), SW_MINIMIZE);
}

App::App(Block *block, int flags) : block_(block)
{
    App::focusBlock = block;
    App::fps_ = 60;
    ege::setinitmode(flags | ege::INIT_ANIMATION | ege::INIT_UNICODE);
    if (!App::instance_)
        App::instance_ = this;
    else
        throw Exception("Only one App object can be created.");
}

App::~App() {}

void App::run()
{
    // 用于高清显示
    ::SetProcessDPIAware();
    // 初始化环境
    ege::initgraph(this->block_->rect().width(),
                   this->block_->rect().height());
    App::windowCreate.emit();
    ege::setbkmode(TRANSPARENT);
    App::setTitle(L"Egrome");

    // 事件循环
    PaintEvent paintEvent;
    static Point lastMousePos;
    for (; ege::is_run(); ege::delay_fps(App::fps_))
    {
        // BUG-20240601-20
        auto lastTime = std::chrono::steady_clock::now();
        // 更新显示
        ege::setbkcolor(EGERGB(0, 0, 0));
        ege::cleardevice();
        this->block_->paintEvent(paintEvent);
        // 帧内事件循环
        while (std::chrono::duration_cast<std::chrono::nanoseconds>(
                   std::chrono::steady_clock::now() - lastTime)
                       .count() *
                   App::fps_ <
               8.5e8)
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
                            App::focusBlock->InputTextEvent((wchar_t)keymsg.key);
                        keymsg = ege::getkey();
                    } while (keymsg.msg == ege::key_msg_char);
                }
                break;
                default:
                    break;
                }
                if (ege::kbhit()) // 文本输入(ASCII字符)
                {
                    auto ch = ege::getch();
                    if (std::isprint(ch))
                        if (App::focusBlock)
                            App::focusBlock->InputTextEvent((wchar_t)ch);
                }
                // ege::flushkey();
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
                // BUG20240530-21: 连续触发鼠标消息有概率导致鼠标消息丢失
                if (msg.is_down())
                    this->block_->mousePressEvent(Point(msg.x, msg.y), button);
                if (msg.is_up())
                    this->block_->mouseReleaseEvent(Point(msg.x, msg.y), button);
                if (msg.is_wheel())
                    this->block_->mouseWheelEvent(
                        Point(msg.x, msg.y),
                        msg.wheel > 0 ? MouseWheel::Up
                                      : (msg.wheel < 0 ? MouseWheel::Down
                                                       : MouseWheel::None));
                if (msg.is_move() && lastMousePos != Point(msg.x, msg.y))
                    this->block_->mouseMoveEvent(Point(msg.x, msg.y)),
                        lastMousePos = Point(msg.x, msg.y);
                // ege::flushmouse(); // BUG20240530-21 此行引起鼠标消息丢失
            }
        }
    }
    App::windowDestroy.emit();
    ege::closegraph();
}

void App::quit(int exitCode)
{
    if (App::instance_)
        App::instance_->windowDestroy.emit();
    ege::closegraph();
    exit(exitCode);
}