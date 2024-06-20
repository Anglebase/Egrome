#pragma once

class Event {
    mutable bool accepted_;

public:
    Event();
    virtual ~Event();

    void accept() const;
    void reset() const;

    bool isAccepted() const;
};