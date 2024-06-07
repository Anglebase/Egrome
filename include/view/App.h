#pragma once
/**
 * @file App.h
 * @brief 应用程序类
 */
#include <string>
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
    TopMost = 0x04,
    /// 使用Unicode字符集
    Unicode = 0x20
};

/**
 * @brief 应用程序类
 */
class App
{
public:
    /**
     * @brief 获取窗口大小
     * @return 窗口大小
     */
    static Size getWindowSize();

    /**
     * @brief 设置窗口大小
     * @param width 窗口宽度
     * @param height 窗口高度
     */
    static void setWindowSize(int width, int height);

    /**
     * @brief 这是一个重载，设置窗口大小
     * @param size 窗口大小
     */
    static void setWindowSize(const Size &size);

    /**
     * @brief 获取窗口位置(相对于屏幕左上角)
     * @return 窗口位置
     */
    static Point getWindowPos();

    /**
     * @brief 设置窗口位置(相对于屏幕左上角)
     * @param x x方向坐标
     * @param y y方向坐标
     */
    static void setWindowPos(int x, int y);

    /**
     * @brief 这是一个重载，设置窗口位置(相对于屏幕左上角)
     * @param pos 相对于屏幕左上角的坐标
     */
    static void setWindowPos(const Point &pos);

    /**
     * @brief 设置窗口标题
     * @param title 窗口标题
     */
    static void setTitle(const std::string &title);

    /**
     * @brief 这是一个重载，设置窗口标题
     * @param title 窗口标题
     */
    static void setTitle(const std::wstring &title);

    /**
     * @brief 获取鼠标位置(相对于屏幕左上角)
     * @return 鼠标位置
     */
    static Point getMousePos();

    /**
     * @brief 设置鼠标位置(相对于屏幕左上角)
     * @param x x方向坐标
     * @param y y方向坐标
     */
    static void setMousePos(int x, int y);

    /**
     * @brief 这是一个重载，设置鼠标位置(相对于屏幕左上角)
     * @param pos 相对于屏幕左上角的坐标
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

    static void setFocusBlock(Block *block);
    static Block *getFocusBlock();

private:
    static Block *focusBlock;
    Block *block_{nullptr};
    static int fps_;

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
     * @note 此函数管理针对于block对象的事件分发
     */
    void run();

    /**
     * @brief 退出应用程序
     * @note 调用此函数将会导致应用程序退出，并返回exitCode作为退出代码
     * @param exitCode 退出代码
     */
    void quit(int exitCode);
};

/**
 * @brief 相对于视口宽度百分比的字面量运算符
 * @param vw 视口宽度百分比
 * @details 例如：100_vw 表示视口宽度的100% ，75_vw 表示视口宽度的75%
 * @return 视口宽度百分比对应的像素值
 */
int operator""_vw(unsigned long long vw);
/**
 * @brief 相对于视口高度百分比的字面量运算符
 * @param vh 视口高度百分比
 * @details 例如：100_vh 表示视口高度的100% ，75_vh 表示视口高度的75%
 * @return 视口高度百分比对应的像素值
 */
int operator""_vh(unsigned long long vh);

/** @} */