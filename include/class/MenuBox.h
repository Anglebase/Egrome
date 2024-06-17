#pragma once

/**
 * @file menubox.h
 * @brief 菜单列表控件
 */

#include <vector>
#include "../view/Block.h"
#include "../view/Color.h"
#include "../core/Animation.hpp"
#include "./label.h"
class MenuBox;

/**
 * @addtogroup 控件
 * @{
 */

/**
 * @addtogroup 菜单控件
 * @{
 */
/**
 * @brief 菜单项
 * @details 用于显示菜单项
 * @note
 */
class MenuItem : public Block
{
    friend class MenuBox;

private:
    Label *label_;
    MenuBox *childMenu_{nullptr};

    bool hovered_{false};
    bool clicked_{false};

public:
    /**
     * @brief 样式表
     */
    struct StyleSheet
    {
        /// @brief 鼠标悬浮时背景色
        Color hoverColor{Color::LightGray};
        /// @brief 鼠标点击时背景色
        Color clickColor{Color::Gray};
        /// @brief 默认背景色
        Color defaultColor{Color::White};
    } style;

protected:
    Animation<Color> *hoverColorAnim_;
    Animation<Color> *clickColorAnim_;

protected:
    /**
     * @brief 重写了 Block::paintEvent() 函数，绘制菜单项
     * @param event 绘制事件
     */
    void paintEvent(const PaintEvent &event) override;
    /**
     * @brief 重写了 Block::mousePressEvent() 函数，处理鼠标点击事件
     * @param pos 鼠标点击位置
     * @param button 鼠标按键
     */
    void mousePressEvent(const Point &pos, MouseButton button) override;
    /**
     * @brief 重写了 Block::mouseReleaseEvent() 函数，处理鼠标释放事件
     * @param pos 鼠标释放位置
     * @param button 鼠标按键
     */
    void mouseReleaseEvent(const Point &pos, MouseButton button) override;

    /**
     * @brief 重写了 Block::mouseMoveEvent() 函数，处理鼠标移动事件
     * @param pos 鼠标移动位置
     */
    void mouseMoveEvent(const Point &pos) override;
signals:
    /**
     * @brief 菜单项被点击时发出此信号
     */
    Signal<void()> clicked;

public:
    /**
     * @brief 构造函数
     * @param rect 菜单项的矩形
     * @param parent 菜单项的父级菜单框
     * @note 菜单项的父级菜单框必须是 MenuBox 类型
     * @note 菜单项的矩形仅有高度会生效，宽度继承自 MenuBox
     */
    MenuItem(const Rect &rect, MenuBox *parent);
    /**
     * @brief 析构函数
     */
    ~MenuItem() override;

    /**
     * @brief 设置菜单项的文本
     * @param text 菜单项的文本
     */
    void setText(const std::wstring &text);
    /**
     * @brief 获取菜单项的文本
     * @return 菜单项的文本
     */
    const std::wstring &getText() const;

    /**
     * @brief 设置菜单项的字体颜色
     * @param color 菜单项的字体颜色
     */
    void setTextColor(const Color &color);

    /**
     * @brief 设置子菜单
     * @param menu 子菜单
     */
    void addChildMenu(MenuBox *menu);
};

/**
 * @brief 分割线
 */
class Divider : public Block
{
public:
    /**
     * @brief 样式表
     */
    struct StyleSheet
    {
        /// @brief 分割线颜色
        Color color{Color::Gray};
        /// @brief 背景颜色
        Color backgroundColor{Color::White};
    } style;

private:
    Divider(const Rect &rect, Block *parent);

protected:
    /**
     * @brief 重写了 Block::paintEvent() 函数，绘制分割线
     * @param event 绘制事件
     */
    void paintEvent(const PaintEvent &event) override;

public:
    /**
     * @brief 构造函数
     * @param parent 父级菜单框
     */
    Divider(MenuBox *parent);
    /**
     * @brief 析构函数
     */
    ~Divider() override = default;
};

/**
 * @brief 菜单框
 * @details 用于包装菜单项
 * @note 对于多级菜单栏，所有 MenuBox 对象都应该具有同一父对象
 */
class MenuBox : public Block
{
    friend class MenuItem;
    friend class Divider;

private:
    std::vector<Block *> items_;
    bool visible_{false};

protected:
    /**
     * @brief 重写了 Block::paintEvent() 函数，绘制菜单框
     * @param event 绘制事件
     */
    void paintEvent(const PaintEvent &event) override;
    /**
     * @brief 重写了 Block::mousePressEvent() 函数，处理鼠标点击事件
     * @param pos 鼠标点击位置
     * @param button 鼠标按键
     */
    void mousePressEvent(const Point &pos, MouseButton button) override;
    /**
     * @brief 重写了 Block::mouseReleaseEvent() 函数，处理鼠标释放事件
     * @param pos 鼠标释放位置
     * @param button 鼠标按键
     */
    void mouseReleaseEvent(const Point &pos, MouseButton button) override;
    /**
     * @brief 重写了 Block::mouseMoveEvent() 函数，处理鼠标移动事件
     * @param pos 鼠标移动位置
     */
    void mouseMoveEvent(const Point &pos) override;
signals:
    /**
     * @brief 菜单框被隐藏时发出此信号
     */
    Signal<void()> hidden;
    /**
     * @brief 菜单框被显示时发出此信号
     */
    Signal<void()> shown;

public:
    /**
     * @brief 构造函数
     * @param rect 菜单框的矩形
     * @param parent 菜单框的父级菜单框
     * @note 菜单框的矩形仅有宽度会生效，高度是由内容计算得出的
     * @see getHeight()
     */
    MenuBox(const Rect &rect, Block *parent);
    /**
     * @brief 析构函数
     */
    ~MenuBox() override = default;
    /**
     * @brief 添加菜单项
     * @param item 菜单项
     */
    void addItem(MenuItem *item);
    /**
     * @brief 移除菜单项
     * @param itemIndex 菜单项索引
     */
    void removeItem(int itemIndex);
    /**
     * @brief 添加分割线
     * @param divider 分割线
     */
    void addDivider(Divider *divider);
    /**
     * @brief 移除分割线
     * @param dividerIndex 分割线索引
     */
    void clearItems();
    /**
     * @brief 显示菜单框
     * @param pos 菜单框显示位置
     */
    void show(const Point &pos);
    /**
     * @brief 隐藏菜单框
     */
    void hide();
    /**
     * @brief 获取菜单项数量
     * @return 菜单项数量
     */
    int getItemCount() const;
    /**
     * @brief 获取菜单项实际高度
     * @return 菜单项实际高度
     */
    float getHeight() const;

    /**
     * @brief 获取菜单框是否可见
     * @return 菜单框是否可见
     */
    bool isVisible() const;
};

/** @} */
/** @} */
