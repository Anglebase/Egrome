#pragma once

#include "./KeyEvent.h"

/**
 * @brief 按键按下事件
 */
class KeyPressEvent : public KeyEvent {
public:
    KeyPressEvent(Key key, bool shift, bool ctrl);
    virtual ~KeyPressEvent();
};