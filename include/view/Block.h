#pragma once

#include "core/SignalSlots.hpp"

class Rect;
class Point;
class Size;

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

/**
 * @brief Block是所有UI对象的基类，它提供了视图绘制、事件处理等基本功能
 * @brief 用户可以通过继承Block类来实现自己的UI对象，通过重写paint()函数来实现自己的绘制逻辑，通过重写update()函数来实现自己的更新逻辑
 */
class Block
{
    friend class App;

private:
    Rect *rect;

protected:
    /**
     * @brief 纯虚函数，用于绘制Block，此函数内不应修改Block的数据状态，应采用update()函数来更新数据状态
     * @note 子类必须实现该函数
     */
    virtual void paint() const = 0;

    /**
     * @brief 虚函数，用于更新Block的数据状态
     * @note 此函数在paint()函数之前调用，用于更新Block的数据状态，如文本、颜色等，由于它运行于事件循环线程中，因此应避免执行耗时操作，否则会导致UI卡顿，耗时操作应采用std::async等异步方式执行
     */
    virtual void update();

    /**
     * @brief 此函数用于处理鼠标、键盘等事件，并发出相应信号
     * @note 此函数在事件循环线程中运行，因此相关槽函数中应避免执行耗时操作，否则会导致UI卡顿，耗时操作应采用std::async等异步方式执行
     */
    void handle();

signals:
    /// @brief 当Block重绘完成时时发出此信号
    Signal<void(Block *self)> redraw;
    /// @brief 当鼠标移动时发出此信号
    Signal<void(const Point &position, const Point &delta)> onMouseMoved;
    /// @brief 当鼠标按键按下时发出此信号
    Signal<void(const Point &position, const MouseButton &button)> onMousePressed;
    /// @brief 当鼠标按键松开时发出此信号
    Signal<void(const Point &position, const MouseButton &button)> onMouseReleased;
    /// @brief 当鼠标滚轮滚动时发出此信号
    Signal<void(const MouseWheel &wheel)> onMouseWheel;
    /// @brief 当鼠标点击此Block时发出此信号
    Signal<void()> onClicked;
    /// @brief 当鼠标右键点击此Block时发出此信号
    Signal<void()> onMenu;
    /// @brief 如果焦点在此Block上，则当键盘按键按下时发出此信号
    Signal<void(const Key &key)> onKeyPressed;
    /// @brief 如果焦点在此Block上，则当键盘按键松开时发出此信号
    Signal<void(const Key &key)> onKeyReleased;
    /// @brief 如果焦点在此Block上，则当存在字符输入时发出此信号
    Signal<void(const int &ch)> onCharInput;

public:
    /**
     * @brief 构造函数
     * @param rect Block的矩形区域
     * @note 子类应在构造函数中调用父类的构造函数并传入自己的矩形区域
     */
    Block(Rect *rect);

    /**
     * @brief 析构函数
     */
    ~Block();

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
};