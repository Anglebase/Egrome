#include "KeyPressEvent.h"


KeyPressEvent::KeyPressEvent(Key key, bool shift, bool ctrl)
    : KeyEvent(key, KeyState::Pressed, shift, ctrl) {}

KeyPressEvent::~KeyPressEvent() = default;
