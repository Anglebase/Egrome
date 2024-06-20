#pragma once

#include "./KeyEvent.h"


class KeyPressEvent : public KeyEvent {
public:
    KeyPressEvent(Key key, bool shift, bool ctrl);
    virtual ~KeyPressEvent();
};