#pragma once

#include "../core/Object.h"
#include "./Block.h"
class String;

enum InitFlag {
    Default = 0x00,
    NoBorder = 0x01,
    TopMost = 0x04,
};

/**
 * @brief 应用程序类
 */
class App final : public Object {
public:
    static void quit(int code);
private:
    Block* root_;
private:
    static int fps_;
public:
    /**
     * @brief 获取当前实际帧率
     * @return 实际帧率
     */
    static float getFps();
    /**
     * @brief 设置目标帧率
     * @param fps 目标帧率
     */
    static void setFps(int fps);
    /**
     * @brief 获取设置的目标帧率
     * @return 目标帧率
     */
    static int getSetFps();
    /**
     * @brief 设置窗口标题
     * @param title 窗口标题
     */
    static void setTitle(const String& title);
public:
    /**
     * @brief 构造函数
     * @param root Block对象树的根节点
     * @param flags 程序初始化标志
     */
    App(Block* root, int flags = Default);
    ~App();
    /**
     * @brief 事件循环
     */
    void run();
};
