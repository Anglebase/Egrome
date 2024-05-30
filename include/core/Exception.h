#pragma once

#include <iostream>

/**
 * @addtogroup 核心
 * @{
 */

/**
 * @brief 此类用于抛出异常
 */
class Exception
{
private:
    const char *m_message;

public:
    /**
     * @brief 构造函数
     * @brief 如果在定义了_DEBUG宏，则会直接输出异常信息
     * @param message 异常信息
    */
    Exception(const char *message) : m_message(message)
    {
#ifdef _DEBUG
        std::cout << "Exception: " << message << std::endl;
#endif
    }

    /**
     * @brief 获取异常信息
     * @return 异常信息
     */
    const char *what() const { return m_message; }
};
/** @} */