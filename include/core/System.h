#pragma once

#include "./XString.h"
class Size;

/**
 * @brief 系统功能接口
 */
namespace Sys{
    /**
     * @brief 读取剪贴板文本
     * @return 剪贴板文本
     */
    String getCilpBoardText();
    /**
     * @brief 写入剪贴板文本
     * @param text 要写入的文本
     */
    void setCilpBoardText(String text);
    /**
     * @brief 获取屏幕大小
     * @return 屏幕大小
     */
    Size getScreenSize();
}