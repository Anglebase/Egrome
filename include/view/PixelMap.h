#pragma once
/**
 * @file PixelMap.h
 * @brief 像素图类
*/
#include <memory>

class Size;
class Painter;
class Rect;

/**
 * @addtogroup 视图
 * @{
*/

/**
 * @brief 像素图类
 * @details 像素图类用于绘制图像，并提供裁剪、复制以及混合等功能
 * @note 用户可以通过如下方式获取位图对象的Painter对象：
 * @code
 * PixelMap bitmap(100, 100);
 * auto& painter = bitmap.beginPaint();
 * // 绘制图像
 * painter.drawLine(0, 0, 100, 100);
 * // 结束绘制
 * bitmap.endPaint(); // 绘图结束后，必须调用该函数
 * @endcode
 * @see Painter
 * @see PaintEvent
 */
class PixelMap
{
    friend class Painter;

public:
    /**
     * @brief 从屏幕创建像素图
     * @param rect 屏幕矩形区域
     * @return 创建出的像素图
     */
    static std::shared_ptr<PixelMap> FormScreen(const Rect &rect);
    /**
     * @brief 从文件创建像素图
     * @param filename 文件名
     * @return 创建出的像素图
     */
    static std::shared_ptr<PixelMap> FromFile(const std::string &filename);
    // static std::shared_ptr<PixelMap> FromFile(const std::wstring &filename);

private:
    void *image_;
    int width_;
    int height_;

    mutable Painter *painter_{nullptr};

public:
    /**
     * @brief 构造函数
     * @param width 像素图宽度
     * @param height 像素图高度
     */
    PixelMap(long width, long height);
    /**
     * @brief 构造函数
     * @param size 像素图大小
     */
    PixelMap(const Size &size);

    PixelMap(const PixelMap &other) = delete;
    PixelMap(PixelMap &&other) = delete;
    PixelMap &operator=(const PixelMap &other) = delete;
    PixelMap &operator=(PixelMap &&other) = delete;

    /**
     * @brief 析构函数
     */
    ~PixelMap();
    /**
     * @brief 获取像素图大小
     * @return 像素图大小
     */
    Size getSize() const;
    /**
     * @brief 设置像素图大小
     * @param width 像素图宽度
     * @param height 像素图高度
     */
    void setSize(int width, int height);
    /**
     * @brief 设置像素图大小
     * @param size 像素图大小
     */
    void setSize(const Size &size);
    /**
     * @brief 开始绘制
     * @return 该对象的绘图器
     */
    const Painter &beginPaint() const;
    /**
     * @brief 结束绘制
     * @note 调用该函数后，该对象的绘图器将失效
     */
    void endPaint() const;
    /**
     * @brief 复制像素图
     * @return 复制出的像素图
     */
    std::shared_ptr<PixelMap> clone() const;
    /**
     * @brief 裁剪像素图
     * @param rect 裁剪区域
     * @return 裁剪出的像素图
     */
    std::shared_ptr<PixelMap> clip(const Rect &rect) const;
};

/** @} */