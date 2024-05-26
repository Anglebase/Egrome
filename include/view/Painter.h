#pragma once

#include <string>
#include <vector>

class Color;
class Block;
class Point;
class Rect;

/**
 * @brief 线条样式
 */
enum class PenStyle
{
    Solid,
    Dash,
    Dot,
    DashDot,
    Null
};

/**
 * @brief 画刷样式
 */
enum class BrushStyle
{
    EMPTY,
    SOLID,
    LINE,
    LTSLASH,
    SLASH,
    BKSLASH,
    LTBKSLASH,
    HATCH,
    XHATCH,
    INTERLEAVE,
    WIDE_DOT,
    CLOSE_DOT
};

enum class TextHAlign
{
    Left,
    Center,
    Right
};

enum class TextVAlign
{
    Top,
    Center,
    Bottom
};

class Painter
{
    friend class PaintEvent;
    Color *brushColor;

    const Block *block = nullptr;

    /**
     * @brief 构造函数，此函数不应该被直接调用，应该通过PainterEvent来构造Painter对象
     * @param block 绘制区域
     */
    Painter(const Block *block);

public:
    Painter(const Painter &) = delete;
    Painter(Painter &&) = delete;
    Painter &operator=(const Painter &) = delete;
    Painter &operator=(Painter &&) = delete;
    ~Painter();

    /**
     * @brief 设置画笔颜色
     * @param color 画笔颜色
     */
    void setPenColor(const Color &color) const;

    /**
     * @brief 设置画笔宽度
     * @param width 画笔宽度
     */
    void setPenWidth(int width) const;

    /**
     * @brief 设置画笔样式
     * @param style 画笔样式
     */
    void setPenStyle(PenStyle style) const;

    /**
     * @brief 设置画刷颜色
     * @param color 画刷颜色
     */
    void setBrushColor(const Color &color) const;

    /**
     * @brief 设置画刷样式
     * @param style 画刷样式
     */
    void setBrushStyle(BrushStyle style) const;

    /**
     * @brief 设置字体
     * @param fontName 字体名称
     * @param size 字体大小
     */
    void setFont(const std::string &fontName, int size) const;

    /**
     * @brief 这是一个重载，设置字体
     * @param fontName 字体名称
     * @param size 字体大小
     */
    void setFont(const std::wstring &fontName, int size) const;

    /**
     * @brief 设置文本对齐方式
     * @param halign 水平对齐方式
     * @param valign 垂直对齐方式
     */
    void setTextAlign(TextHAlign halign, TextVAlign valign) const;

    /**
     * @brief 绘制线
     * @param x1 第一点的x坐标
     * @param y1 第一点的y坐标
     * @param x2 第二点的x坐标
     * @param y2 第二点的y坐标
     */
    void drawLine(int x1, int y1, int x2, int y2) const;

    /**
     * @brief 这是一个重载，绘制线
     * @param p1 第一点坐标
     * @param p2 第二点坐标
     */
    void drawLine(const Point &p1, const Point &p2) const;

    /**
     * @brief 绘制矩形
     * @param x 矩形左上角的x坐标
     * @param y 矩形左上角的y坐标
     * @param w 矩形的宽度
     * @param h 矩形的高度
     */
    void drawRect(int x, int y, int w, int h) const;

    /**
     * @brief 这是一个重载，绘制矩形
     * @param rect 矩形
     */
    void drawRect(const Rect &rect) const;

    /**
     * @brief 绘制椭圆
     * @param x 椭圆外接矩形左上角的x坐标
     * @param y 椭圆外接矩形左上角的y坐标
     * @param w 椭圆外接矩形的宽度
     * @param h 椭圆外接矩形的高度
     */
    void drawEllipse(int x, int y, int w, int h) const;

    /**
     * @brief 这是一个重载，绘制椭圆
     * @param rect 椭圆外接矩形
     */
    void drawEllipse(const Rect &rect) const;

    /**
     * @brief 绘制多边形
     * @param points 多边形的各顶点坐标
     */
    void drawPolygon(const std::vector<Point> &points) const;

    /**
     * @brief 绘制折线
     * @param points 折线的各转折点坐标
     */
    void drawPolyline(const std::vector<Point> &points) const;

    /**
     * @brief 绘制弧线
     * @param x 弧线的圆心x坐标
     * @param y 弧线的圆心y坐标
     * @param rx 弧线的x半径
     * @param ry 弧线的y半径
     * @param startAngle 弧线的起始角度
     * @param endAngle 弧线的终止角度
     */
    void drawArc(int x, int y, int rx, int ry, int startAngle, int endAngle) const;

    /**
     * @brief 这是一个重载，绘制弧线
     * @param rect 弧线所在椭圆的外接矩形
     * @param startAngle 弧线的起始角度
     * @param endAngle 弧线的终止角度
     */
    void drawArc(const Rect &rect, int startAngle, int endAngle) const;

    /**
     * @brief 绘制文本
     * @param x 文本所在的x坐标
     * @param y 文本所在的y坐标
     * @param text 文本内容
     */
    void drawText(int x, int y, const std::string &text) const;

    /**
     * @brief 这是一个重载，绘制文本
     * @param x 文本所在的x坐标
     * @param y 文本所在的y坐标
     * @param text 文本内容
     */
    void drawText(int x, int y, const std::wstring &text) const;

    /**
     * @brief 绘制文本
     * @param pos 文本所在的位置
     * @param text 文本内容
     */
    void drawText(const Point &pos, const std::string &text) const;

    /**
     * @brief 这是一个重载，绘制文本
     * @param pos 文本所在的位置
     * @param text 文本内容
     */
    void drawText(const Point &pos, const std::wstring &text) const;

    /**
     * @brief 绘制文本
     * @param rect 文本所在的矩形
     * @param text 文本内容
     */
    void drawText(const Rect &rect, const std::string &text) const;

    /**
     * @brief 这是一个重载，绘制文本
     * @param rect 文本所在的矩形
     * @param text 文本内容
     */
    void drawText(const Rect &rect, const std::wstring &text) const;
};

class PaintEvent
{
private:
    friend class App;

    /**
     * @brief 构造函数，此函数不应该被直接调用，应该通过App来构造PainterEvent对象
     */
    PaintEvent() = default;
    mutable Painter *painter = nullptr;

public:
    PaintEvent(const PaintEvent &) = delete;
    PaintEvent(PaintEvent &&) = delete;
    PaintEvent &operator=(const PaintEvent &) = delete;
    PaintEvent &operator=(PaintEvent &&) = delete;
    ~PaintEvent();

    /**
     * @brief 构造Painter对象
     * @param block 绘制区域
     * @return Painter对象
     */
    const Painter &beginPaint(const Block *block) const;
    const Painter &beginPaint(Block *block) = delete;

    /**
     * @brief 结束绘制
     * @brief 结束绘制，释放Painter对象，如果该函数未被调用，此类析构时会自动释放Painter对象
     */
    void endPaint();
};