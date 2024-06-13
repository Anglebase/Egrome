#pragma once
/**
 * @file App.h
 * @brief 应用程序类
 */
#include <string>
#include "../core/SignalSlots.hpp"
class Size;
class Point;
class Block;

/**
 * @addtogroup 视图
 * @{
 */

/**
 * @brief 初始化标志
 */
enum InitFlag
{
    /// 默认初始化标志
    Default = 0x00,
    /// 不显示边框
    NoBorder = 0x01,
    /// 作为子窗口
    Child = 0x02,
    /// 置顶窗口
    TopMost = 0x04
};

/**
 * @brief 应用程序类
 * @note 应用程序类提供了各种系统接口的封装，并管理应用程序的生命周期。它提供了例如读写剪贴板、获取设置窗口的大小、位置、标题、全局鼠标坐标等功能。其次，它创建的对象应当全局唯一，如果尝试创建第二个实例，将会抛出异常。
 */
class App
{
public:
    /**
     * @brief 获取屏幕大小
     * @return 屏幕大小
     * @note 屏幕大小指的是整个屏幕的物理像素的长和宽，包括任务栏
     */
    static Size getScreenSize();

    /**
     * @brief 获取窗口大小
     * @return 窗口大小
     * @note 窗口大小指的是窗口的逻辑像素的长和宽，不包括边框、标题栏等
     */
    static Size getWindowSize();

    /**
     * @brief 设置窗口大小
     * @param width 窗口宽度
     * @param height 窗口高度
     * @note 窗口大小指的是窗口的逻辑像素的长和宽，不包括边框、标题栏等
     */
    static void setWindowSize(int width, int height);

    /**
     * @brief 设置窗口大小
     * @param size 窗口大小
     * @note 窗口大小指的是窗口的逻辑像素的长和宽，不包括边框、标题栏等
     */
    static void setWindowSize(const Size &size);

    /**
     * @brief 获取窗口位置
     * @return 窗口位置
     * @note 此位置是窗口左上角相对于屏幕左上角的坐标
     */
    static Point getWindowPos();

    /**
     * @brief 设置窗口位置
     * @param x x方向坐标
     * @param y y方向坐标
     * @note 此位置是窗口左上角相对于屏幕左上角的坐标
     */
    static void setWindowPos(int x, int y);

    /**
     * @brief 设置窗口位置
     * @param pos 相对于屏幕左上角的坐标
     * @note 此位置是窗口左上角相对于屏幕左上角的坐标
     */
    static void setWindowPos(const Point &pos);

    /**
     * @brief 设置窗口标题
     * @param title 窗口标题
     * @note 窗口标题将显示在窗口的标题栏中
     * @note 窗口标题将显示在窗口的标题栏中，通常情况下应使用另一重载设置标题
     * @see setTitle(const std::wstring &title)
     */
    static void setTitle(const std::string &title);

    /**
     * @brief 设置窗口标题
     * @param title 窗口标题
     * @note 窗口标题将显示在窗口的标题栏中，通常情况下应使用此函数设置标题
     */
    static void setTitle(const std::wstring &title);

    /**
     * @brief 获取鼠标位置
     * @return 鼠标位置
     * @note 此位置是鼠标相对于屏幕左上角的坐标
     */
    static Point getMousePos();

    /**
     * @brief 设置鼠标位置
     * @param x x方向坐标
     * @param y y方向坐标
     * @note 此位置是鼠标相对于屏幕左上角的坐标
     */
    static void setMousePos(int x, int y);

    /**
     * @brief 设置鼠标位置
     * @param pos 相对于屏幕左上角的坐标
     * @note 此位置是鼠标相对于屏幕左上角的坐标
     */
    static void setMousePos(const Point &pos);

    /**
     * @brief 获取剪切板文本
     * @return 剪切板文本
     */
    static std::wstring getCilpboardText();
    /**
     * @brief 设置剪切板文本
     * @param text 剪切板文本
     */
    static void setCilpboardText(const std::wstring &text);

    /**
     * @brief 获取当前实际帧率
     * @return 实际帧率
     */
    static float getFps();

    /**
     * @brief 获取设置的目标帧率
     * @return 设置的目标帧率
     */
    static int getSettingFps();
    /**
     * @brief 设置目标帧率
     * @param fps 目标帧率
     */
    static void setFps(int fps);

    /**
     * @brief 设置当前焦点块
     * @return 当前焦点块
     * @note 焦点块是一个全局唯一的对象，它代表了当前具有焦点的块对象，如果没有焦点块，则返回nullptr，在默认情况下，焦点块是由鼠标点击事件产生的
     */
    static void setFocusBlock(Block *block);

    /**
     * @brief 获取当前焦点块
     * @return 当前焦点块
     * @note 焦点块是一个全局唯一的对象，它代表了当前具有焦点的块对象，如果没有焦点块，则返回nullptr，在默认情况下，焦点块是由鼠标点击事件产生的
     */
    static Block *getFocusBlock();

    /**
     * @brief 最小化窗口
     * @note 最小化窗口后，窗口将不可见，但仍然存在于任务栏中
     */
    static void setMinimize();

private:
    static Block *focusBlock;
    Block *block_{nullptr};
    static int fps_;
    static App *instance_;
signals:
    /**
     * @brief 窗口创建信号
     * @note 当窗口创建时发出此信号
     */
    inline static Signal<void()> windowCreate;
    /**
     * @brief 窗口销毁信号
     * @note 当窗口销毁时发出此信号
     */
    inline static Signal<void()> windowDestroy;

public:
    /**
     * @brief 构造函数
     * @param block 根块对象
     * @note 此构造函数在同一应用程序中只能调用一次，第二次调用将会抛出异常(如果支持)
     */
    App(Block *block, int flags = Default);
    ~App();

    /**
     * @brief 运行应用程序
     * @note 此函数管理应用程序的事件循环
     */
    void run();

    /**
     * @brief 退出应用程序
     * @note 调用此函数将会导致应用程序退出，并返回exitCode作为退出代码，该函数被调用时，会发出窗口销毁信号，如果未指定exitCode，则默认为0
     * @param exitCode 退出代码
     */
    static void quit(int exitCode = 0);
};

/** @} */