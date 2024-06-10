#pragma once
/**
 * @file Block.h
 * @brief 块基类
 */
#include <vector>
#include "../core/SignalSlots.hpp"
#include "../core/Rect.h"
#include "../core/Point.h"

class Rect;
class Point;
class Size;
class PaintEvent;

/**
 * @addtogroup 视图
 * @{
 */

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
    /// 鼠标左键
    Mouse_l = 0x01,
    /// 鼠标右键
    Mouse_r = 0x02,
    /// 鼠标中键
    Mouse_m = 0x04,
    /// 退格键
    BackSpace = 0x08,
    /// Tab键
    Tab = 0x09,
    /// 回车键
    Enter = 0x0d,
    /// Shift键
    Shift = 0x10,
    /// Ctrl键
    Control = 0x11,
    /// Alt键
    Menu = 0x12,
    Pause = 0x13,
    /// Capslock键(大写锁定键)
    Capslock = 0x14,
    /// Esc键
    Esc = 0x1b,
    /// 空格键
    Space = 0x20,

    /// Pageup键
    Pageup = 0x21,
    /// Pagedown键
    Pagedown = 0x22,
    /// End键
    End = 0x23,
    /// Home键
    Home = 0x24,

    /// 左方向键
    Left = 0x25,
    /// 上方向键
    Up = 0x26,
    /// 右方向键
    Right = 0x27,
    /// 下方向键
    Down = 0x28,

    Print = 0x2a,
    Snapshot = 0x2c,
    /// Insert键
    Insert = 0x2d,
    /// Delete键
    Delete = 0x2e,

    /// 0键
    N0 = 0x30,
    /// 1键
    N1 = 0x31,
    /// 2键
    N2 = 0x32,
    /// 3键
    N3 = 0x33,
    /// 4键
    N4 = 0x34,
    /// 5键
    N5 = 0x35,
    /// 6键
    N6 = 0x36,
    /// 7键
    N7 = 0x37,
    /// 8键
    N8 = 0x38,
    /// 9键
    N9 = 0x39,

    /// A键
    A = 0x41,
    /// B键
    B = 0x42,
    /// C键
    C = 0x43,
    /// D键
    D = 0x44,
    /// E键
    E = 0x45,
    /// F键
    F = 0x46,
    /// G键
    G = 0x47,
    /// H键
    H = 0x48,
    /// I键
    I = 0x49,
    /// J键
    J = 0x4a,
    /// K键
    K = 0x4b,
    /// L键
    L = 0x4c,
    /// M键
    M = 0x4d,
    /// N键
    N = 0x4e,
    /// O键
    O = 0x4f,
    /// P键
    P = 0x50,
    /// Q键
    Q = 0x51,
    /// R键
    R = 0x52,
    /// S键
    S = 0x53,
    /// T键
    T = 0x54,
    /// U键
    U = 0x55,
    /// V键
    V = 0x56,
    /// W键
    W = 0x57,
    /// X键
    X = 0x58,
    /// Y键
    Y = 0x59,
    /// Z键
    Z = 0x5a,
    /// 左Windows键
    Win_l = 0x5b,
    /// 右Windows键
    Win_r = 0x5c,

    Sleep = 0x5f,

    /// 小键盘数字0键
    Num0 = 0x60,
    /// 小键盘数字1键
    Num1 = 0x61,
    /// 小键盘数字2键
    Num2 = 0x62,
    /// 小键盘数字3键
    Num3 = 0x63,
    /// 小键盘数字4键
    Num4 = 0x64,
    /// 小键盘数字5键
    Num5 = 0x65,
    /// 小键盘数字6键
    Num6 = 0x66,
    /// 小键盘数字7键
    Num7 = 0x67,
    /// 小键盘数字8键
    Num8 = 0x68,
    /// 小键盘数字9键
    Num9 = 0x69,

    Multiply = 0x6a,
    Add = 0x6b,
    Separator = 0x6c,
    Subtract = 0x6d,
    Decimal = 0x6e,
    Divide = 0x6f,

    /// F1键
    F1 = 0x70,
    /// F2键
    F2 = 0x71,
    /// F3键
    F3 = 0x72,
    /// F4键
    F4 = 0x73,
    /// F5键
    F5 = 0x74,
    /// F6键
    F6 = 0x75,
    /// F7键
    F7 = 0x76,
    /// F8键
    F8 = 0x77,
    /// F9键
    F9 = 0x78,
    /// F10键
    F10 = 0x79,
    /// F11键
    F11 = 0x7a,
    /// F12键
    F12 = 0x7b,

    /// Numlock键
    Numlock = 0x90,
    Scrolllock = 0x91,

    /// 左Shift键
    Shift_l = 0xa0,
    /// 右Shift键
    Shift_r = 0xa1,
    /// 左Ctrl键
    Control_l = 0xa2,
    /// 右Ctrl键
    Control_r = 0xa3,
    /// 左Alt键
    Menu_l = 0xa4,
    /// 右Alt键
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

enum class CursorType
{
    Arrow,
    IBeam,
    Cross,
    Hand,
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
    std::vector<Block *> childBlocks_;
    Block *parentBlock_;

    long long zindex_ = 0;

    CursorType cursorType_ = CursorType::Arrow;
    void *lastCursor_ = nullptr;

private:
    // 用于 BUG-20240529-20 修复
    Point lastPos_;

private:
    static void* cursorArrow;
    static void* cursorIBeam;
    static void* cursorCross;
    static void* cursorHand;

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
    virtual void InputTextEvent(wchar_t inputChar);

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
     * @brief 设置当鼠标悬浮于此Block上时的光标类型
     * @param cursorType 鼠标光标类型
     */
    void setCursorType(CursorType cursorType);
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

    Block *parent() const;
    std::vector<Block *> &childs();
    const std::vector<Block *> &childs() const;

    /**
     * @brief 获取Block的Z索引顺序
     * @return Block的Z索引顺序
     * @see setZindex()
     */
    long long zindex() const;
    /**
     * @brief 设置Block的Z索引顺序
     * @param zindex Block的Z索引顺序
     * @note Z索引决定了同一父Block下的Block的事件处理函数的调用顺序，对于绘图函数来说，越小的Z索引越先绘制，其它事件处理函数则按照Z索引越大越先调用，Z索引的默认值为0，相同Z索引的Block事件触发顺序不确定
     */
    void setZindex(long long zindex);
};

/** @} */