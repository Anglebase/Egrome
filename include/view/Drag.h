#pragma once

#include <optional>
#include "Block.h"
#include "Point.h"

enum class Ref{
    Global,
    Window
};

/**
 * @brief 可拖动的块
 * @note 继承自 Block，它是所有可拖动对象的基类，它通过监视鼠标的全局(窗口)坐标来判断鼠标所拖动的相对位置，因此也可以用于窗口拖动移动
 */
class Drag : public Block
{
private:
    Ref ref_ = Ref::Window;
    std::optional<Point> beginPos_{std::nullopt};
    std::optional<Point> thisPos_{std::nullopt};
    bool xEnabled_ = true;
    bool yEnabled_ = true;

protected:
    void mousePressEvent(const Point &pos, MouseButton button) override;
    void mouseMoveEvent(const Point &pos) override;
    void mouseReleaseEvent(const Point &pos, MouseButton button) override;

signals:
    /**
     * @brief 当此对象被拖动时发出信号
     * @param pos 此时被拖动对象的位置
     */
    Signal<void(const Point &pos)> dragged;
    /**
     * @brief 当此对象被释放时发出信号
     */
    Signal<void()> released;

public:
    /**
     * @brief 构造函数
     * @param rect 块的矩形区域，它指示块的大小和初始位置
     * @param parent 父块
     */
    Drag(const Rect &rect, Block *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~Drag() override;
    /**
     * @brief 设置块的可移动方向
     * @param x 是否可水平移动
     * @param y 是否可垂直移动
     */
    void setEnabled(bool x, bool y);
    /**
     * @brief 获取块在水平方向上的可移动状态
     * @return 是否可水平移动
     */
    bool isXEnabled() const;
    /**
     * @brief 获取块在垂直方向上的可移动状态
     * @return 是否可垂直移动
     */
    bool isYEnabled() const;
    /**
     * @brief 设置参考系
     * @param ref 参考系，可以是全局坐标系(Ref::Global)或窗口坐标系(Ref::Window)，默认为窗口坐标系 
     */
    void setReference(Ref ref);
};