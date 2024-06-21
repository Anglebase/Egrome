
#pragma once
#include "./Object.h"

/**
 * @brief 尺寸类
 */
class Size : public Object
{
private:
    float width_;
    float height_;

public:
    Size(float x = 0, float y = 0) noexcept;
    ~Size() noexcept;

    float &width() noexcept;
    float &height() noexcept;
    const float &width() const noexcept;
    const float &height() const noexcept;

    Size &operator=(const Size &other) noexcept;
    Size operator+(const Size &other) const noexcept;
    Size operator-(const Size &other) const noexcept;
    Size operator*(const float &scale) const noexcept;
    Size operator/(const float &scale) const noexcept;
    Size &operator+=(const Size &other) noexcept;
    Size &operator-=(const Size &other) noexcept;
    Size &operator*=(const float &scale) noexcept;
    Size &operator/=(const float &scale) noexcept;

    bool operator==(const Size &other) const noexcept;
    bool operator!=(const Size &other) const noexcept;
};