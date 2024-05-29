#pragma once

#include <vector>
#include "core/SignalSlots.hpp"
#include "core/Rect.h"
#include "core/Point.h"

class Rect;
class Point;
class Size;
class PaintEvent;

/// @brief 鼠标按钮枚举
enum class MouseButton
{
    Left,
    Right,
    Middle
};

/// @brief 鼠标滚轮方向枚举
enum class MouseWheel
{
    Up,
    Down,
    None
};

/// @brief 键盘按键枚举
enum class Key
{
    Mouse_l = 0x01,
    Mouse_r = 0x02,
    Mouse_m = 0x04,
    Back = 0x08,
    Tab = 0x09,
    Enter = 0x0d,
    Shift = 0x10,
    Control = 0x11,
    Menu = 0x12,
    Pause = 0x13,
    Capslock = 0x14,
    Esc = 0x1b,
    Space = 0x20,

    Pageup = 0x21,
    Pagedown = 0x22,
    Home = 0x23,
    End = 0x24,

    Left = 0x25,
    Up = 0x26,
    Right = 0x27,
    Down = 0x28,

    Print = 0x2a,
    Snapshot = 0x2c,
    Insert = 0x2d,
    Delete = 0x2e,

    N0 = 0x30,
    N1 = 0x31,
    N2 = 0x32,
    N3 = 0x33,
    N4 = 0x34,
    N5 = 0x35,
    N6 = 0x36,
    N7 = 0x37,
    N8 = 0x38,
    N9 = 0x39,

    A = 0x41,
    B = 0x42,
    C = 0x43,
    D = 0x44,
    E = 0x45,
    F = 0x46,
    G = 0x47,
    H = 0x48,
    I = 0x49,
    J = 0x4a,
    K = 0x4b,
    L = 0x4c,
    M = 0x4d,
    N = 0x4e,
    O = 0x4f,
    P = 0x50,
    Q = 0x51,
    R = 0x52,
    S = 0x53,
    T = 0x54,
    U = 0x55,
    V = 0x56,
    W = 0x57,
    X = 0x58,
    Y = 0x59,
    Z = 0x5a,
    Win_l = 0x5b,
    Win_r = 0x5c,

    Sleep = 0x5f,

    Num0 = 0x60,
    Num1 = 0x61,
    Num2 = 0x62,
    Num3 = 0x63,
    Num4 = 0x64,
    Num5 = 0x65,
    Num6 = 0x66,
    Num7 = 0x67,
    Num8 = 0x68,
    Num9 = 0x69,

    Multiply = 0x6a,
    Add = 0x6b,
    Separator = 0x6c,
    Subtract = 0x6d,
    Decimal = 0x6e,
    Divide = 0x6f,

    F1 = 0x70,
    F2 = 0x71,
    F3 = 0x72,
    F4 = 0x73,
    F5 = 0x74,
    F6 = 0x75,
    F7 = 0x76,
    F8 = 0x77,
    F9 = 0x78,
    F10 = 0x79,
    F11 = 0x7a,
    F12 = 0x7b,

    Numlock = 0x90,
    Scrolllock = 0x91,

    Shift_l = 0xa0,
    Shift_r = 0xa1,
    Control_l = 0xa2,
    Control_r = 0xa3,
    Menu_l = 0xa4,
    Menu_r = 0xa5,

    Semicolon = 0xba,
    Plus = 0xbb,
    Comma = 0xbc,
    Minus = 0xbd,
    Period = 0xbe,
    Slash = 0xbf,
    Tilde = 0xc0,
    Lbrace = 0xdb,
    Backslash = 0xdc,
    Rbrace = 0xdd,
    Quote = 0xde,

    Ime_process = 0xe5,
};

enum class KeyFlag
{
    Ctrl = 0x200,
    Shift = 0x100,
};

/**
 * @brief Block是所有UI对象的基类，它提供了视图绘制、事件处理等基本功能
 * @brief 用户可以通过继承Block类来实现自己的UI对象，通过重写paint()函数来实现自己的绘制逻辑，通过重写update()函数来实现自己的更新逻辑
 */
class Block
{
    friend class App;
    friend class Painter;

private:
    Rect rect_;
    std::vector<Block *> childBlocks;
    Block *parentBlock;

private:
    // 用于 BUG-20240529-20 修复
    Point lastPos;

protected:
    /**
     * @brief 虚函数，用于绘制 Block
     * @brief 此函数内不应修改 Block 的数据状态，应采用 update() 函数来更新数据状态
     * @brief 此函数会遍历子 Block 并调用子 Block 的 paint() 函数绘制子 Block
     * @param event 绘制事件
     * @note 子类重写该函数时应当调用父类的 paint() 函数
     */
    virtual void paintEvent(const PaintEvent &event);

    /**
     * @brief 虚函数，用于处理鼠标按钮按下事件
     * @param pos 鼠标位置
     * @param button 鼠标按钮
     * @note 子类可以重写该函数来实现自己的事件处理逻辑，默认实现会触发 onClicked 信号和 onMenuClicked 信号
     */
    virtual void mousePressEvent(const Point &pos, MouseButton button);

    /**
     * @brief 虚函数，用于处理鼠标按钮释放事件
     * @param pos 鼠标位置
     * @param button 鼠标按钮
     * @note 子类可以重写该函数来实现自己的事件处理逻辑，默认实现为空函数
     */
    virtual void mouseReleaseEvent(const Point &pos, MouseButton button);

    /**
     * @brief 虚函数，用于处理鼠标移动事件
     * @param pos 鼠标位置
     * @note 子类可以重写该函数来实现自己的事件处理逻辑，默认实现会触发 onMoved 信号、onEnter 信号和 onLeave 信号
     */
    virtual void mouseMoveEvent(const Point &pos);

    /**
     * @brief 虚函数，用于处理鼠标滚轮事件
     * @param pos 鼠标位置
     * @param wheel 鼠标滚轮方向
     * @note 子类可以重写该函数来实现自己的事件处理逻辑，默认实现为空函数
     */
    virtual void mouseWheelEvent(const Point &pos, MouseWheel wheel);

    /**
     * @brief 虚函数，用于处理键盘按下事件
     * @param key 按下的键
     * @note 子类可以重写该函数来实现自己的事件处理逻辑，默认实现会触发 onNext 信号
     */
    virtual void keyPressEvent(Key key, KeyFlag flag);

    /**
     * @brief 虚函数，用于处理键盘释放事件
     * @param key 释放的键
     * @note 子类可以重写该函数来实现自己的事件处理逻辑，默认实现为空函数
     */
    virtual void keyReleaseEvent(Key key, KeyFlag flag);

    /**
     * @brief 虚函数，用于处理输入文本事件
     * @param inputChar 输入的字符
     * @note 子类可以重写该函数来实现自己的事件处理逻辑，默认实现会触发 onInputText 信号
     */
    virtual void InputTextEvent(int inputChar);

signals:
    /**
     * @brief 鼠标点击信号
     * @brief 该信号会在鼠标点击Block时触发
     * @brief 触发该信号时，会条件触发此Block的 onFocused 信号和原先具有焦点的Block的 onUnfocused 信号
     * @see mousePressEvent()
     */
    Signal<void()> onClicked;
    /**
     * @brief 鼠标右键点击信号
     * @brief 该信号会在鼠标右键点击Block时触发
     * @see mousePressEvent()
     */
    Signal<void()> onMenuClicked;
    /**
     * @brief 鼠标移动信号
     * @brief 该信号会在鼠标移动到Block上时触发
     * @param delta 与上次触发此信号时鼠标位置的变化量
     * @see mouseMoveEvent()
     */
    Signal<void(const Point &delta)> onMoved;
    /**
     * @brief 字符输入信号
     * @brief 该信号会在用户输入字符时触发
     * @param inputChar 输入的文本
     * @see InputTextEvent()
     */
    Signal<void(int inputChar)> onInputText;
    /**
     * @brief 完成信号
     * @brief 该信号会在用户按下Enter键时触发
     */
    Signal<void()> onNext;
    /**
     * @brief 鼠标进入信号
     * @brief 该信号会在鼠标进入Block时触发
     * @see onLeave
     */
    Signal<void()> onEnter;
    /**
     * @brief 鼠标离开信号
     * @brief 该信号会在鼠标离开Block时触发
     * @see onEnter
     */
    Signal<void()> onLeave;

    /**
     * @brief 获得焦点信号
     * @brief 该信号会在Block获得焦点时触发
     * @param block 原来焦点所在的Block
     * @see onClicked
     * @see onUnfocused
     */
    Signal<void(Block *block)> onFocused;
    /**
     * @brief 失去焦点信号
     * @brief 该信号会在Block失去焦点时触发
     * @param block 获得焦点的Block
     * @see onClicked
     * @see onFocused
     */
    Signal<void(Block *block)> onUnfocused;

public:
    /**
     * @brief 构造函数
     * @param rect Block的矩形区域
     * @param parent 父Block
     * @note 子类应在构造函数中调用父类的构造函数并传入自己的矩形区域
     */
    Block(const Rect &rect, Block *parent = nullptr);
    virtual ~Block() = default;

    /**
     * @brief 获取Block的矩形区域
     * @return Block的矩形区域
     */
    const Rect &getRect() const;

    /**
     * @brief 设置Block的矩形区域
     * @param rect Block的矩形区域
     */
    void setRect(const Rect &rect);

    Rect &rect();
    const Rect &rect() const;
};