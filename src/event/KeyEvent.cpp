#include "KeyEvent.h"

KeyEvent::KeyEvent(Key key, KeyState state, bool shift, bool ctrl)
    : key_(key), shift_(shift), ctrl_(ctrl), state_(state) {}
KeyEvent::~KeyEvent() = default;

Key KeyEvent::key() const {
    return this->key_;
}

bool KeyEvent::hasShift() const {
    return this->shift_;
}
bool KeyEvent::hasCtrl() const {
    return this->ctrl_;
}

KeyState KeyEvent::state() const {
    return this->state_;
}
