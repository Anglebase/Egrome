#pragma once
/**
 * @file radiobox.h
 * @brief 单选框控件
 * @details 单选框控件用于表示一个可选中的选项，单选框组中只能有一个被选中，当选中组中某个单选框时，组中已选中的单选框的选中状态会自动变为未选中
 */
#include "../view/Block.h"
#include "../view/Color.h"

class RadioBox;

/**
 * @addtogroup 控件
 * @{
 */

/**
 * @addtogroup 单选框控件
 * @{
 */

/**
 * @brief 单选框组
 * @details 单选框组用于管理一组单选框，一组单选框中只能有一个被选中，当选中某个单选框时，已选中的单选框的选中状态会自动变为未选中
 */
class RadioBoxGroup
{
    friend class RadioBox;

private:
    RadioBox *selected_{nullptr};

signals:
    /**
     * @brief 单选框组状态改变信号
     * @details 当单选框组中选中状态改变时，会发出此信号
     * @param pass 原选中单选框
     * @param now 新选中单选框
     */
    Signal<void(RadioBox *pass, RadioBox *now)> selectedChanged;

public:
    /**
     * @brief 构造函数
     */
    RadioBoxGroup() = default;
    /**
     * @brief 析构函数
     */
    ~RadioBoxGroup() = default;

    /**
     * @brief 获取当前选中单选框
     * @return 当前选中单选框
     */
    RadioBox *selected() const;
};

/**
 * @brief 单选框
 * @details 单选框用于表示一个可选中的选项，单选框组中只能有一个被选中，当选中组中某个单选框时，组中已选中的单选框的选中状态会自动变为未选中
 */
class RadioBox : public Block
{
    RadioBoxGroup *group_;
    bool hovered_;
    std::wstring text_;

public:
    struct StyleSheet
    {
        Color textColor_{Color::White};
        Color selectedColor_{Color::Blue};
        Color borderColor_{Color::White};
        Color hoverColor_{Color::LightGray};
        int borderWidth_{1};
        int borderRadius_{5};
    } style;

protected:
    /**
     * @brief 重写 paintEvent() 函数，绘制单选框
     * @param event 绘制事件
     */
    void paintEvent(const PaintEvent &event) override;
    /**
     * @brief 重写 mousePressEvent() 函数，响应鼠标点击事件
     * @param pos 鼠标点击位置
     * @param button 鼠标按键
     */
    void mousePressEvent(const Point &pos, MouseButton button) override;

signals:
    /**
     * @brief 单选框状态改变信号
     * @details 当单选框的选中状态改变时，会发出此信号
     * @param selected 单选框当前是否被选中
     */
    Signal<void(bool selected)> selectedChanged;

public:
    /**
     * @brief 构造函数
     * @param rect 单选框的矩形区域
     * @param group 所属单选框组
     * @param parent 父级控件
     * @details 构造函数会自动将单选框添加到所属单选框组中
     */
    RadioBox(const Rect &rect, RadioBoxGroup &group, Block *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~RadioBox() override = default;
    /**
     * @brief 设置单选框的文本内容
     * @param text 文本内容
     */
    void setText(const std::wstring &text);
    /**
     * @brief 设置单选框所属的单选框组
     * @param group 所属单选框组
     */
    void setRadioBoxGroup(RadioBoxGroup &group);
    /**
     * @brief 设置单选框的选中状态
     * @param selected true表示选中，false表示未选中
     */
    void setSelected(bool selected);
    /**
     * @brief 判断单选框是否被选中
     * @return true表示选中，false表示未选中
     */
    bool isSelected() const;
};

/** @} */
/** @} */
