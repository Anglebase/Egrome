#pragma once

#include "../core/Point.h"
#include "./Event.h"

class MouseEvent : public Event {
protected:
    Point position_;
public:
    MouseEvent(Point position);
    virtual ~MouseEvent();

    const Point& position() const;
};