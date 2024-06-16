#pragma once

#include "Block.h"
#include "PixelMap.h"
#include "Drag.h"
#include "Color.h"

class ScrollView;

enum class HScrollPos
{
    Top,
    Bottom,
};

enum class VScrollPos
{
    Left,
    Right,
};

enum class ScrollType
{
    Horizontal,
    Vertical,
};

class ScrollBar : public Drag
{
public:
    struct StyleSheet
    {
        Color barColor{Color::Gray};
    } style;
    ScrollView *parent_{nullptr};
    friend class ScrollView;
protected:
    void paintEvent(const PaintEvent &event) override;

public:
    ScrollBar(const Rect &rect, ScrollView *parent = nullptr);
    ~ScrollBar() override = default;
};

/**
 * @brief 滚动视图
 * @note 滚动视图提供了滚动功能，可以让页面内容在视图中移动，并提供滚动条
 */
class ScrollView : public Block
{
private:
    // 页面内容
    PixelMap *view_{nullptr};
    // 滚动条
    ScrollBar *horScroll_{nullptr};
    ScrollBar *verScroll_{nullptr};
    // 滚动条位置
    HScrollPos horPos_{HScrollPos::Bottom};
    VScrollPos verPos_{VScrollPos::Right};
    // 优先渲染的滚动条
    ScrollType firstScrollType_{ScrollType::Vertical};
    // 页面内容的裁剪位置
    Point clipPos_{0, 0};

    bool hasHorScroll_{false};
    bool hasVerScroll_{false};

    long step_{20};
    bool shifting_{false};

public:
    struct StyleSheet
    {
        Color backgroundColor{Color::White};
        Color scrollBarColor{0x88888880_rgba};
        Color scrollLineColor{0x88888880_rgba};
        int scrollBarWidth{20};
    } style;

protected:
    void paintEvent(const PaintEvent &event) override;
    virtual void paintEvent(const Painter &painter);
    void mouseWheelEvent(const Point &pos, MouseWheel wheel) override;
    void keyPressEvent(Key key, KeyFlag flag) override;
    void keyReleaseEvent(Key key, KeyFlag flag) override;

public:
    ScrollView(const Rect &rect, Block *parent = nullptr);
    ~ScrollView();

    void updateScroll();

    void setView(PixelMap *view);
    PixelMap *view() const;

    void setHScrollPos(HScrollPos pos);
    HScrollPos hScrollPos() const;

    void setVScrollPos(VScrollPos pos);
    VScrollPos vScrollPos() const;

    void setFirstScrollType(ScrollType type);
    ScrollType firstScrollType() const;
};