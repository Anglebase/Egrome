#include "KeyReleaseEvent.h"


KeyReleaseEvent::KeyReleaseEvent(Key key, bool shift, bool ctrl)
    : KeyEvent(key, KeyState::Released, shift, ctrl) {}

KeyReleaseEvent::~KeyReleaseEvent() = default;
