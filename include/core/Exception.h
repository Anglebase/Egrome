#pragma once
/**
 * @file Exception.h
 * @brief 异常类
*/
#include <iostream>

/**
 * @addtogroup 核心
 * @{
 */

/**
 * @brief 此类用于抛出异常，同时也是所有异常类的基类
 */
class Exception
{
private:
    const char *m_message;

public:
    /**
     * @brief 构造函数
     * @param message 异常信息
    */
    Exception(const char *message) : m_message(message)
    {
    }

    /**
     * @brief 获取异常信息
     * @return 异常信息
     */
    const char *what() const { return m_message; }
};
/** @} */