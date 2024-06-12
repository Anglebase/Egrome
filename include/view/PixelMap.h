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
     * @warning 此函数不应在构造函数中调用，如有需求，应将他在构造函数中作为槽函数连接至信号App::windowCreate
     */
    static PixelMap FormScreen(const Rect &rect);
    /**
     * @brief 从文件创建像素图
     * @param filename 文件名
     * @return 创建出的像素图
     * @note 支持的图像格式：png/bmp/jpg/gif/emf/wmf/ico
     * @warning 此函数不应在构造函数中调用，如有需求，应将他在构造函数中作为槽函数连接至信号App::windowCreate
     */
    static PixelMap FromFile(const std::string &filename);
    /**
     * @brief 从文件创建像素图
     * @param filename 文件名
     * @return 创建出的像素图
     * @note 支持的图像格式：png/bmp/jpg/gif/emf/wmf/ico
     * @warning 此函数不应在构造函数中调用，如有需求，应将他在构造函数中作为槽函数连接至信号App::windowCreate
     */
    static PixelMap FromFile(const std::wstring &filename);

private:
    void *image_{nullptr};
    int width_;
    int height_;

    mutable Painter *painter_{nullptr};

public:
    /**
     * @brief 默认构造函数
     */
    PixelMap() = default;
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
    /**
     * @brief 拷贝构造函数
     * @param other 要拷贝的对象
     */
    PixelMap(const PixelMap &other);
    /**
     * @brief 移动构造函数
     * @param other 要移动的对象
     * @note 该构造函数不会拷贝位图数据，只会转移指针所有权，因此可以避免内存分配和释放，被移动的对象将无法再被使用
     */
    PixelMap(PixelMap &&other);
    /**
     * @brief 复制赋值
     * @param other 源对象
     * @return 赋值后的对象
     */
    PixelMap &operator=(const PixelMap &other);
    /**
     * @brief 移动赋值
     * @param other 源对象
     * @return 赋值后的对象
     * @note 该赋值操作不会拷贝位图数据，只会转移指针所有权，因此可以避免内存分配和释放，被移动的对象将无法再被使用
     */
    PixelMap &operator=(PixelMap &&other);

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
     * @brief 裁剪像素图
     * @param rect 裁剪区域
     * @return 裁剪出的像素图
     */
    PixelMap clip(const Rect &rect) const;
    /**
     * @brief 判断是否为空
     * @return 是否为空
     */
    bool isNull() const;
};

/** @} */