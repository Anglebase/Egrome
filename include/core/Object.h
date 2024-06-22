/**
 * @file Object.h
 * @author Anglebase[Github]
 * @brief 所有类的基类
 */
#pragma once

/**
 * @brief 所有类的基类
 * @anchor Anglebase[Github]
 * @details 它是所有类的基类，提供运行时泛型的支持
 */
class Object
{
public:
    /**
     * @brief 构造函数
     */
    Object() noexcept;
    /**
     * @brief 析构函数
     */
    virtual ~Object() noexcept;
};