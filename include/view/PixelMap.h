#pragma once

#include "../core/Object.h"
#include "../core/Exception.h"
class Size;
class Painter;

/**
 * @brief 位图类
 */
class PixelMap final : public Object {
    friend class Painter;
    friend void* getTarget(Painter*);
private:
    void* image_;
    mutable Painter* painter_;

    class SizeData {
        friend class PixelMap;
    private:
        PixelMap* map_;
        SizeData(PixelMap* map) noexcept;
    public:
        Size operator=(const Size& size) noexcept;
        operator Size() const noexcept;
    };

    class WrongPainter: public Exception {
    public:
        WrongPainter(const String& message) noexcept;
    };
public:
    PixelMap() noexcept;
    PixelMap(int width, int height) noexcept;
    PixelMap(const PixelMap& other) noexcept;
    PixelMap(PixelMap&& other) noexcept;
    ~PixelMap() noexcept;

    PixelMap& operator=(const PixelMap& other) noexcept;
    PixelMap& operator=(PixelMap&& other) noexcept;

    /**
     * @brief 开始绘制
     * @return 针对于此位图的绘制器
     */
    Painter& beginPaint() noexcept;
    /**
     * @brief 结束绘制
     * @param painter 通过beginPaint获得的绘制器
     */
    void endPaint(const Painter& painter);

    SizeData size() noexcept;
    Size size() const noexcept;
};