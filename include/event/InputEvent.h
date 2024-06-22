#pragma once

#include "./Event.h"

/**
 * @brief 输入事件
 */
class InputEvent final : public Event {
private:
    wchar_t inputChar_;
public:
    InputEvent(const wchar_t inputChar);
    virtual ~InputEvent();

    /**
     * @brief 获取输入的字符
     * @return 输入的字符
     */
    wchar_t content() const;
};