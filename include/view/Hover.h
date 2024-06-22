#pragma once

#include "./Block.h"
#include "../core/SignalSlots.hpp"

/**
 * @brief 悬浮行为基类，通过继承此类可以实现Block悬浮响应
 */
class Hover : public Block {
private:
    Point lastPos;
    bool hasPos;

protected:
    void mouseMoveEvent(MouseMoveEvent* event) override;
    
    /**
     * @brief 判断点是否在此区域内
     * @param point 点
     * @return true 点在区域内，false 点不在区域内
     * @note 子类可以重载此函数实现自定义可点击区域
     */
    virtual bool isContains(const Point& point);
public:
    Hover(const Rect& rect, Block* parent = nullptr);
    ~Hover() override;

public:
    Signal<void(const Point& pos)> entered;
    Signal<void(const Point& pos)> leaved;
};