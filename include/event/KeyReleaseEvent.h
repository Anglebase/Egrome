#pragma once

#include "./KeyEvent.h"

/**
 * @brief 按键释放事件
 */
class KeyReleaseEvent : public KeyEvent {
public:
    KeyReleaseEvent(Key key, bool shift, bool ctrl);
    virtual ~KeyReleaseEvent();
};