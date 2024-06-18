/**
 * @file Rect.h
 * @author Anglebase
 */
#pragma once

#include "./Object.h"
#include "./Point.h"
#include "./Size.h"

class Rect : public Object {
private:
    float x_;
    float y_;
    float width_;
    float height_;
private:
#pragma region 修改器
    class RectData {
    protected:
        Rect* rect_;
        RectData(Rect* rect);
    };
#pragma region 边坐标修改器
    class LeftSide :public RectData {
        friend class Rect;
    private:
        LeftSide(Rect* rect);
    public:
        float operator=(float value);
        operator float() const;
    };
    class RightSide :public RectData {
        friend class Rect;
    private:
        RightSide(Rect* rect);
    public:
        float operator=(float value);
        operator float() const;
    };
    class TopSide :public RectData {
        friend class Rect;
    private:
        TopSide(Rect* rect);
    public:
        float operator=(float value);
        operator float() const;
    };
    class BottomSide :public RectData {
        friend class Rect;
    private:
        BottomSide(Rect* rect);
    public:
        float operator=(float value);
        operator float() const;
    };
#pragma endregion 边坐标修改器
#pragma region 点坐标修改器
    class Center :public RectData {
        friend class Rect;
    private:
        Center(Rect* rect);
    public:
        Point operator=(const Point& value);
        operator Point() const;
    };
    class TopLeftCorner :public RectData {
        friend class Rect;
    private:
        TopLeftCorner(Rect* rect);
    public:
        Point operator=(const Point& value);
        operator Point() const;
    };
    class TopRightCorner :public RectData {
        friend class Rect;
    private:
        TopRightCorner(Rect* rect);
    public:
        Point operator=(const Point& value);
        operator Point() const;
    };
    class BottomLeftCorner :public RectData {
        friend class Rect;
    private:
        BottomLeftCorner(Rect* rect);
    public:
        Point operator=(const Point& value);
        operator Point() const;
    };
    class BottomRightCorner :public RectData {
        friend class Rect;
    private:
        BottomRightCorner(Rect* rect);
    public:
        Point operator=(const Point& value);
        operator Point() const;
    };
#pragma endregion 点坐标修改器
#pragma region 其余修改器
    class PosData :public RectData {
        friend class Rect;
    private:
        PosData(Rect* rect);
    public:
        Point operator=(const Point& value);
        operator Point() const;
    };
    class SizeData :public RectData {
        friend class Rect;
    private:
        SizeData(Rect* rect);
    public:
        Size operator=(const Size& value);
        operator Size() const;
    };
#pragma endregion 其余修改器
#pragma endregion 修改器
public:
    Rect(float x, float y, float width, float height) noexcept;
    ~Rect() noexcept;
#pragma region 属性访问器
    float& x() noexcept;
    float& y() noexcept;
    float& width() noexcept;
    float& height() noexcept;

    const float& x() const noexcept;
    const float& y() const noexcept;
    const float& width() const noexcept;
    const float& height() const noexcept;
#pragma endregion 属性访问器
#pragma region 隐属性访问器
    LeftSide left() noexcept;
    RightSide right() noexcept;
    TopSide top() noexcept;
    BottomSide bottom() noexcept;

    Center center() noexcept;
    TopLeftCorner topLeft() noexcept;
    TopRightCorner topRight() noexcept;
    BottomLeftCorner bottomLeft() noexcept;
    BottomRightCorner bottomRight() noexcept;

    PosData pos() noexcept;
    SizeData size() noexcept;

    float left() const noexcept;
    float right() const noexcept;
    float top() const noexcept;
    float bottom() const noexcept;

    Point center() const noexcept;
    Point topLeft() const noexcept;
    Point topRight() const noexcept;
    Point bottomLeft() const noexcept;
    Point bottomRight() const noexcept;

    Point pos() const noexcept;
    Size size() const noexcept;
#pragma endregion 隐属性访问器
};