#pragma once

#include "./KeyEvent.h"


class KeyReleaseEvent : public KeyEvent {
public:
    KeyReleaseEvent(Key key, bool shift, bool ctrl);
    virtual ~KeyReleaseEvent();
};