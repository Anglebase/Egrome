#pragma once

#include <string>
class Size;
class Point;
class Block;

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

private:
    Block *block_{nullptr};
    static int fps_;

public:
    /**
     * @brief 构造函数
     * @param block 根块对象
     * @note 此构造函数在同一应用程序中只能调用一次，第二次调用将会抛出异常(如果支持)
     */
    App(Block *block);
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