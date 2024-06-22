#include "Event.h"

Event::Event() :accepted_(false) {}
Event::~Event() {}

void Event::accept() const {
    this->accepted_ = true;
}

void Event::reset() const {
    this->accepted_ = false;
}

bool Event::isAccepted() const {
    return this->accepted_;
}
