#pragma once

#include "Block.h"
#include "PixelMap.h"
#include "Drag.h"
#include "Color.h"

/**
 * @addtogroup 视图
 * @{
 */

class ScrollView;
/**
 * @addtogroup 枚举
 * @{
 */
/// @brief 水平滚动条位置
enum class HScrollPos
{
    /// 滚动视图顶部
    Top,
    /// 滚动视图底部
    Bottom,
};
/// @brief 垂直滚动条位置
enum class VScrollPos
{
    /// 滚动视图左侧
    Left,
    /// 滚动视图右侧
    Right,
};
/// 滚动条类型
enum class ScrollType
{
    /// 水平滚动条
    Horizontal,
    /// 垂直滚动条
    Vertical,
};
/** @} */

/**
 * @addtogroup 滚动视图
 * @{
 */

/**
 * @brief 滚动条
 * @note 滚动条是用来控制滚动视图的滚动的
 */
class ScrollBar : public Drag
{
public:
    /// @brief 样式表
    struct StyleSheet
    {
        /// 滚动条颜色
        Color barColor{Color::Gray};
    } style;
    ScrollView *parent_{nullptr};
    friend class ScrollView;

protected:
    /**
     * @brief 重写此方法，用于滚动条的绘制
     */
    void paintEvent(const PaintEvent &event) override;

public:
    /**
     * @brief 构造函数
     * @param parent 滚动视图
     * @note 此类是特化用于滚动视图的，用户不应使用此类
     */
    ScrollBar(ScrollView *parent = nullptr);
    ~ScrollBar() override = default;
};

/**
 * @brief 滚动视图
 * @note 滚动视图提供了滚动功能，可以让页面内容在视图中移动，并提供滚动条。
 * @note 滚动视图的滚动条是根据页面大小和视图大小自动生成的
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

    float step_{20.};
    bool shifting_{false};

public:
    /// @brief 样式表
    struct StyleSheet
    {
        /// 背景颜色
        Color backgroundColor{Color::White};
        /// 滚动条颜色
        Color scrollBarColor{0x88888880_rgba};
        /// 滚动条边界线条颜色
        Color scrollLineColor{0x88888880_rgba};
        /// 滚动条宽度
        float scrollBarWidth{20};
    } style;
    /**
     * @addtogroup 枚举
     * @{
     */
    /// @brief 滚动视图类型
    enum Type
    {
        /// 无滚动条
        None,
        /// 具有水平滚动条
        Horizontal,
        /// 具有垂直滚动条
        Vertical,
        /// 具有水平和垂直滚动条
        Both
    };
    /** @} */
protected:
    /**
     * @brief 重写此方法，用于滚动视图的绘制
     * @param event 绘制事件
     */
    void paintEvent(const PaintEvent &event) override;
    /**
     * @brief 此方法替代paintEvent(const PaintEvent &event)，用于向页面绘制内容
     * @param painter 绘制器
     * @note 子类可以重写此方法，用于绘制页面内容，它采用的是页面自己的坐标系，页面的左上角为坐标原点
     */
    virtual void pagePaintEvent(const Painter &painter);
    /**
     * @brief 重写此方法，用于滚动视图的鼠标事件
     * @param pos 鼠标位置
     * @param wheel 鼠标滚轮事件
     * @note 此实现中提供了滚轮和Shift+滚轮控制滚动条的滚动的功能，子类可以有选择地调用此方法决定是否执行该行为
     */
    void mouseWheelEvent(const Point &pos, MouseWheel wheel) override;
    /**
     * @brief 此方法用于监测Shift键是否按下
     * @param key 按下的键
     * @param flag 按键标志
     */
    void keyPressEvent(Key key, KeyFlag flag) override;
    /**
     * @brief 此方法用于监测Shift键是否松开
     * @param key 松开的键
     * @param flag 松开键标志
     */
    void keyReleaseEvent(Key key, KeyFlag flag) override;

public:
    /**
     * @brief 构造函数
     * @param rect 矩形区域
     * @param parent 父级块
     */
    ScrollView(const Rect &rect, Block *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~ScrollView() override;

    /**
     * @brief 依据页面的位置计算并更新滚动条的位置
     * @note 此方法应该在页面内容发生变化时调用，以更新滚动条的位置
     */
    void updateScroll();
    /**
     * @brief 设置页面内容
     * @param view 页面内容
     */
    void setView(PixelMap *view);
    /**
     * @brief 获取页面内容
     * @return 页面内容
     */
    PixelMap *view() const;
    /**
     * @brief 设置水平滚动条的位置
     * @param pos 水平滚动条位置
     * @note 水平滚动条的位置可以处于顶部或底部
     */
    void setHScrollPos(HScrollPos pos);
    /**
     * @brief 获取水平滚动条的位置
     * @return 水平滚动条位置
     */
    HScrollPos hScrollPos() const;
    /**
     * @brief 设置垂直滚动条的位置
     * @param pos 垂直滚动条位置
     * @note 垂直滚动条的位置可以处于左侧或右侧
     */
    void setVScrollPos(VScrollPos pos);
    /**
     * @brief 获取垂直滚动条的位置
     * @return 垂直滚动条位置
     */
    VScrollPos vScrollPos() const;
    /**
     * @brief 设置优先渲染的滚动条
     * @param type 优先渲染的滚动条类型
     * @note 被优先渲染的滚动条的可滚动区域将会占有滚动视图的整个宽度或高度，次级渲染的滚动条的可滚动区域是滚动视图的高度或宽度减去已渲染滚动条的宽度
     */
    void setFirstScrollType(ScrollType type);
    /**
     * @brief 获取优先渲染的滚动条类型
     * @return 优先渲染的滚动条类型
     */
    ScrollType firstScrollType() const;
};

/** @} */
/** @} */