#pragma once

#include "../core/Object.h"

/**
 * @brief 事件类，它是所有事件类的基类。
 */
class Event : public Object {
    mutable bool accepted_;

public:
    Event();
    virtual ~Event();

    /**
     * @brief 接受事件
     */
    void accept() const;
    /**
     * @brief 重置事件状态
     */
    void reset() const;

    /**
     * @brief 事件是否已被接受
     * @return 事件是否已被接受
     */
    bool isAccepted() const;
};