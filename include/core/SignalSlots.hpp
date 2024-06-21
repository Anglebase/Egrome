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

/**
 * @brief 信号类
 * @tparam ...Args 信号参数类型
 */
template <typename... Args>
class Signal<void(Args...)> {
    friend class Connection;

private:
    std::map<unsigned long long, std::function<void(Args...)>> slots;
    unsigned long long id = 0;

public:
    /**
     * @brief 信号槽连接
     */
    class Connection {
        friend class Signal<void(Args...)>;
    private:
        unsigned long long id;
        Signal<void(Args...)>* signal;

    private:
        Connection(unsigned long long id, Signal<void(Args...)>* signal)
            : id(id), signal(signal) {}

    public:
        /**
         * @brief 断开连接
         */
        void disconnect() {
            auto it = this->signal->slots.find(id);
            if (it != this->signal->slots.end()) {
                this->signal->slots.erase(it);
            }
        }
    };

public:
    /**
     * @brief 连接槽函数
     * @param slot 要连接的槽函数
     * @return 连接对象
     */
    Signal<void(Args...)>::Connection connect(std::function<void(Args...)> slot) {
        auto id = this->id++;
        this->slots[id] = slot;
        return Connection(id, this);
    }
    /**
     * @brief 连接槽函数
     * @param obj 对象指针
     * @param method 对象方法指针
     * @return 连接对象
     */
    Signal<void(Args...)>::Connection connect(Object* obj, void (Object::* method)(Args...)) {
        return this->connect([obj, method](Args... args) { (obj->*method)(args...); });
    }
    /**
     * @brief 发射信号
     * @param ...args 信号参数
     */
    void emit(Args &&...args) {
        for (auto& slot : this->slots) {
            slot.second(std::forward<Args>(args)...);
        }
    }
};

/**
 * @brief 信号类模板无参特化
 */
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