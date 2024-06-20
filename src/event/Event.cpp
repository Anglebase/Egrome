#include "Event.h"

Event::Event() :accepted_(false) {}
Event::~Event() {}

void Event::accept() {
    this->accepted_ = true;
}

void Event::reset() {
    this->accepted_ = false;
}

bool Event::isAccepted() {
    return this->accepted_;
}
