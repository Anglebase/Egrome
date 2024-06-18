/**
 * @file SignalSlots.hpp
 * @author Anglebase[GitHub]
 * @brief 信号槽机制
 */
#pragma once

#include <map>
#include <functional>
#include "./Object.h"

template <typename... Args>
class Signal;

template <typename... Args>
class Signal<void(Args...)> {
    friend class Connection;

private:
    std::map<unsigned long long, std::function<void(Args...)>> slots;
    unsigned long long id = 0;

public:
    class Connection {
        friend class Signal<void(Args...)>;
    private:
        unsigned long long id;
        Signal<void(Args...)>* signal;

    private:
        Connection(unsigned long long id, Signal<void(Args...)>* signal)
            : id(id), signal(signal) {}

    public:
        void disconnect() {
            auto it = this->signal->slots.find(id);
            if (it != this->signal->slots.end()) {
                this->signal->slots.erase(it);
            }
        }
    };

public:
    Signal<void(Args...)>::Connection connect(std::function<void(Args...)> slot) {
        auto id = this->id++;
        this->slots[id] = slot;
        return Connection(id, this);
    }

    Signal<void(Args...)>::Connection connect(Object* obj, void (Object::* method)(Args...)) {
        return this->connect([obj, method](Args... args) { (obj->*method)(args...); });
    }

    void emit(Args &&...args) {
        for (auto& slot : this->slots) {
            slot.second(std::forward<Args>(args)...);
        }
    }
};

template <>
class Signal<void()> {
    friend class Connection;
private:
    std::map<unsigned long long, std::function<void()>> slots;
    unsigned long long id = 0;
public:
    class Connection {
        friend class Signal<void()>;
    private:
        unsigned long long id;
        Signal<void()>* signal;

    private:
        Connection(unsigned long long id, Signal<void()>* signal)
            : id(id), signal(signal) {}

    public:
        void disconnect() {
            auto it = this->signal->slots.find(id);
            if (it != this->signal->slots.end()) {
                this->signal->slots.erase(it);
            }
        }
    };

    Signal<void()>::Connection connect(std::function<void()> slot) {
        auto id = this->id++;
        this->slots[id] = slot;
        return Connection(id, this);
    }

    Signal<void()>::Connection connect(Object* obj, void (Object::* method)()) {
        return this->connect([obj, method]() { (obj->*method)(); });
    }

    void emit() {
        for (auto& slot : this->slots) {
            slot.second();
        }
    }
};