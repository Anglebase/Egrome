#pragma once

#include <set>
#include "../core/Object.h"
#include "../core/Rect.h"

class MousePressEvent;
class MouseReleaseEvent;
class MouseMoveEvent;
class MouseWheelEvent;
class KeyPressEvent;
class KeyReleaseEvent;
class InputEvent;
class PaintEvent;

/**
 * @brief 它是所有UI对象的基类
 */
class Block : public Object {
    friend class App;
private:
    Rect rect_;
    bool foreach_;

    Block* parent_;
    std::set<Block*> children_;

protected:
    /**
     * @brief 视图绘制事件处理函数
     * @param event 视图绘制事件指针
     */
    virtual void paintEvent(PaintEvent* event);
    /**
     * @brief 鼠标按键按下事件处理函数
     * @param event 鼠标按键按下事件指针
     */
    virtual void mousePressEvent(MousePressEvent* event);
    /**
     * @brief 鼠标按键释放事件处理函数
     * @param event 鼠标按键释放事件指针
     */
    virtual void mouseReleaseEvent(MouseReleaseEvent* event);
    /**
     * @brief 鼠标移动事件处理函数
     * @param event 鼠标移动事件指针
     */
    virtual void mouseMoveEvent(MouseMoveEvent* event);
    /**
     * @brief 鼠标滚轮事件处理函数
     * @param event 鼠标滚轮事件指针
     */
    virtual void mouseWheelEvent(MouseWheelEvent* event);
    /**
     * @brief 键盘按下事件处理函数
     * @param event 键盘按下事件指针
     */
    virtual void keyPressEvent(KeyPressEvent* event);
    /**
     * @brief 键盘释放事件处理函数
     * @param event 键盘释放事件指针
     */
    virtual void keyReleaseEvent(KeyReleaseEvent* event);
    /**
     * @brief 输入事件处理函数
     * @param event 输入事件指针
     */
    virtual void inputEvent(InputEvent* event);

public:
    /**
     * @brief 构造函数
     * @param rect 矩形区域
     * @param parent 父对象指针
     */
    Block(const Rect& rect, Block* parent = nullptr);
    virtual ~Block();

    const Rect& rect() const;
    Rect& rect();

    /**
     * @brief 获取父对象指针
     * @return 父对象指针
     */
    Block* parent();
    /**
     * @brief 获取子对象指针集合
     * @return 子对象指针集合
     */
    std::set<Block*>& children();

    /**
     * @brief 设置父对象
     * @param parent 父对象指针
     */
    void setParent(Block* parent);
    /**
     * @brief 添加子对象
     * @param child 子对象指针
     */
    void addChild(Block* child);
    /**
     * @brief 移除子对象
     * @param child 子对象指针
     */
    void removeChild(Block* child);

    /**
     * @brief 终止此对象子树事件循环的遍历
     */
    void stopForeach();
    /**
     * @brief 重新启用此对象子树事件循环的遍历
     */
    void resetForeach();
    /**
     * @brief 此对象子树是否处于事件循环可遍历状态
     * @return 事件循环可遍历状态
     */
    bool isForeach() const;
};