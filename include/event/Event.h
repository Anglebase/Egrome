#pragma once

class Event {
    bool accepted_;

public:
    Event();
    virtual ~Event();

    void accept();
    void reset();

    bool isAccepted();
};