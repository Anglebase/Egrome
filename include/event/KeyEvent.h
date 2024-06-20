#pragma once

#include "./Event.h"

enum class Key {
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
    /// Pause键
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
    /// Print键
    Print = 0x2a,
    /// PrintScreen键(截屏键)
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
    /// 计算机休眠键
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

    /// 小键盘乘号(*)键
    Multiply = 0x6a,
    /// 小键盘加号(+)键
    Add = 0x6b,
    /// 分隔符键
    Separator = 0x6c,
    /// 小键盘减号(-)键
    Subtract = 0x6d,
    /// 小键盘点(.)键
    Decimal = 0x6e,
    /// 小键盘除号(/)键
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
    /// Scrolllock键
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
    /// ;:键(分号、冒号)
    Semicolon = 0xba,
    /// =+键(等号、加号)
    Plus = 0xbb,
    /// ,<键(逗号、小于号)
    Comma = 0xbc,
    /// -_键(减号、下划线)
    Minus = 0xbd,
    /// .>键(句号、大于号)
    Period = 0xbe,
    /// /?键(斜杠、问号)
    Slash = 0xbf,
    /// `~键(波浪线、tilde键)
    Tilde = 0xc0,
    /// [{键(左中括号、左花括号)
    Lbrace = 0xdb,
    /// \\|键(竖线、反斜杠)
    Backslash = 0xdc,
    /// ]}键(右中括号、右花括号)
    Rbrace = 0xdd,
    /// '"键(引号、双引号)
    Quote = 0xde,
    /// IME_PROCESS键
    Ime_process = 0xe5,
};

enum class KeyState {
    Pressed,
    Released,
};

class KeyEvent : public Event {
private:
    Key key_;
    bool shift_;
    bool ctrl_;
    // bool alt_;

    KeyState state_;
public:
    KeyEvent(Key key, KeyState state, bool shift, bool ctrl);
    virtual ~KeyEvent();

    Key key()const;

    bool hasShift()const;
    bool hasCtrl()const;
    // bool hasAlt()const;

    KeyState state()const;
};