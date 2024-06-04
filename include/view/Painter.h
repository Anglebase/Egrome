#pragma once
/**
 * @file Painter.h
 * @brief 绘图类
*/
#include <string>
#include <vector>

class Color;
class Block;
class Point;
class Rect;
class PixelMap;

/**
 * @addtogroup 视图
 * @brief 视图绘制相关
 * @{
 */

/**
 * @brief 颜色混合模式
 * @details 该枚举采用三元光栅操作码的后缀表达式表示
 * @note 三元光栅操作码由三个字符组成，分别为：
 * - S：Source，源像素
 * - D：Destination，目标像素
 * - P：Pattern，模式像素(当前填充颜色)
 * 三元光栅操作码的后缀表达式表示法为：
 * - S与D进行与操作：例如 S & D 表示为 SDa
 * - S与D进行或操作：例如 S | D 表示为 SDo
 * - S与D进行异或操作：例如 S ^ D 表示为 SDx
 * - S与D进行反相操作：例如 ~S 表示为 Sn
 * 目前支持的三元光栅操作码有256个
 */
enum class BlendMode
{
    Mode_0,
    DPSoon,
    DPSona,
    PSon,
    SDPona,
    DPon,
    PDSxnon,
    PDSaon,
    SDPnaa,
    PDSxon,
    DPna,
    PSDnaon,
    SPna,
    PDSnaon,
    PDSonon,
    Pn,
    PDSona,
    DSon,
    SDPxnon,
    SDPaon,
    DPSxnon,
    DPSaon,
    PSDPSanaxx,
    SSPxDSxaxn,
    SPxPDxa,
    SDPSanaxn,
    PDSPaox,
    SDPSxaxn,
    PSDPaox,
    DSPDxaxn,
    PDSox,
    PDSoan,
    DPSnaa,
    SDPxon,
    DSna,
    SPDnaon,
    SPxDSxa,
    PDSPanaxn,
    SDPSaox,
    SDPSxnox,
    DPSxa,
    PSDPSaoxxn,
    DPSana,
    SSPxPDxaxn,
    SPDSoax,
    PSDnox,
    PSDPxox,
    PSDnoan,
    PSna,
    SDPnaon,
    SDPSoox,
    Sn,
    SPDSaox,
    SPDSxnox,
    SDPox,
    SDPoan,
    PSDPoax,
    SPDnox,
    SPDSxox,
    SPDnoan,
    PSx,
    SPDSonox,
    SPDSnaox,
    PSan,
    PSDnaa,
    DPSxon,
    SDxPDxa,
    SPDSanaxn,
    SDna,
    DPSnaon,
    DSPDaox,
    PSDPxaxn,
    SDPxa,
    PDSPDaoxxn,
    DPSDoax,
    PDSnox,
    SDPana,
    SSPxDSxoxn,
    PDSPxox,
    PDSnoan,
    PDna,
    DSPnaon,
    DPSDaox,
    SPDSxaxn,
    DPSonon,
    Dn,
    DPSox,
    DPSoan,
    PDSPoax,
    DPSnox,
    DPx,
    DPSDonox,
    DPSDxox,
    DPSnoan,
    DPSDnaox,
    DPan,
    PDSxa,
    DSPDSaoxxn,
    DSPDoax,
    SDPnox,
    SDPSoax,
    DSPnox,
    DSx,
    SDPSonox,
    DSPDSonoxxn,
    PDSxxn,
    DPSax,
    PSDPSoaxxn,
    SDPax,
    PDSPDoaxxn,
    SDPSnoax,
    PDSxnan,
    PDSana,
    SSDxPDxaxn,
    SDPSxox,
    SDPnoan,
    DSPDxox,
    DSPnoan,
    SDPSnaox,
    DSan,
    PDSax,
    DSPDSoaxxn,
    DPSDnoax,
    SDPxnan,
    SPDSnoax,
    DPSxnan,
    SPxDSxo,
    DPSaan,
    DPSaa,
    SPxDSxon,
    DPSxna,
    SPDSnoaxn,
    SDPxna,
    PDSPnoaxn,
    DSPDSoaxx,
    PDSaxn,
    DSa,
    SDPSnaoxn,
    DSPnoa,
    DSPDxoxn,
    SDPnoa,
    SDPSxoxn,
    SSDxPDxax,
    PDSanan,
    PDSxna,
    SDPSnoaxn,
    DPSDPoaxx,
    SPDaxn,
    PSDPSoaxx,
    DPSaxn,
    DPSxx,
    PSDPSonoxx,
    SDPSonoxn,
    DSxn,
    DPSnax,
    SDPSoaxn,
    SPDnax,
    DSPDoaxn,
    DSPDSaoxx,
    PDSxan,
    DPa,
    PDSPnaoxn,
    DPSnoa,
    DPSDxoxn,
    PDSPonoxn,
    PDxn,
    DSPnax,
    PDSPoaxn,
    DPSoa,
    DPSoxn,
    D,
    DPSono,
    SPDSxax,
    DPSDaoxn,
    DSPnao,
    DPno,
    PDSnoa,
    PDSPxoxn,
    SSPxDSxox,
    SDPanan,
    PSDnax,
    DPSDoaxn,
    DPSDPaoxx,
    SDPxan,
    PSDPxax,
    DSPDaoxn,
    DPSnao,
    DSno,
    SPDSanax,
    SDxPDxan,
    DPSxo,
    DPSano,
    PSa,
    SPDSnaoxn,
    SPDSonoxn,
    PSxn,
    SPDnoa,
    SPDSxoxn,
    SDPnax,
    PSDPoaxn,
    SDPoa,
    SPDoxn,
    DPSDxax,
    SPDSaoxn,
    S,
    SDPono,
    SDPnao,
    SPno,
    PSDnoa,
    PSDPxoxn,
    PDSnax,
    SPDSoaxn,
    SSPxPDxax,
    DPSanan,
    PSDPSaoxx,
    DPSxan,
    PDSPxax,
    SDPSaoxn,
    DPSDanax,
    SPxDSxan,
    SPDnao,
    SDno,
    SDPxo,
    SDPano,
    PDSoa,
    PDSoxn,
    DSPDxax,
    PSDPaoxn,
    SDPSxax,
    PDSPaoxn,
    SDPSanax,
    SPxPDxan,
    SSPxDSxax,
    DSPDSanaxxn,
    DPSao,
    DPSxno,
    SDPao,
    SDPxno,
    DSo,
    SDPnoo,
    P,
    PDSono,
    PDSnao,
    PSno,
    PSDnao,
    PDno,
    PDSxo,
    PDSano,
    PDSao,
    PDSxno,
    DPo,
    DPSnoo,
    PSo,
    PSDnoo,
    DPSoo,
    Mode_1,
};

/**
 * @brief 线条样式
 */
enum class PenStyle
{
    /// 实线
    Solid,
    /// 虚线
    Dash,
    /// 点线
    Dot,
    /// 点划线
    DashDot,
    /// 无样式线
    Null
};

/**
 * @brief 画刷样式
 */
enum class BrushStyle
{
    /// 无填充
    EMPTY,
    /// 实心填充
    SOLID,
    /// 线状填充
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
    /// 左对齐
    Left,
    /// 居中对齐
    Center,
    /// 右对齐
    Right
};

enum class TextVAlign
{
    /// 顶部对齐
    Top,
    /// 居中对齐
    Center,
    /// 底部对齐
    Bottom
};

/**
 * @brief Painter类，提供绘图相关的接口
 * @details Painter类提供了绘图相关的接口，包括画笔、画刷、字体、颜色等属性的设置，以及绘制各种图形的接口
 * @details Painter类是视图系统的核心类，负责绘制各种图形，并提供绘图相关的接口
 * @note 用户无法直接创建Painter对象，只能通过PainterEvent或PixelMap来创建
 * @see PaintEvent
 * @see PixelMap
 */
class Painter
{
    friend class PaintEvent;
    friend class PixelMap;
    Color *brushColor;

    mutable TextHAlign halign;
    mutable TextVAlign valign;

    const Block *block;
    const PixelMap *pixelMap;

    /**
     * @brief 构造函数，此函数不应该被直接调用，应该通过PainterEvent来构造Painter对象
     * @param block 绘制区域
     */
    Painter(const Block *block);
    Painter(const PixelMap *pixelMap);

public:
    Painter(const Painter &) = delete;
    Painter(Painter &&) = delete;
    Painter &operator=(const Painter &) = delete;
    Painter &operator=(Painter &&) = delete;
    ~Painter();

    Rect rect() const;

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
     * @brief 设置字体大小
     * @param size 字体大小
     */
    void setFontSize(int size) const;

    /**
     * @brief 设置字体粗细
     * @param weight 字体粗细
     */
    void setFontWeight(int weight) const;

    /**
     * @brief 设置字体斜体
     * @param italic true表示斜体，false表示非斜体
     */
    void setFontItalic(bool italic) const;

    /**
     * @brief 设置字体是否具有下划线
     * @param underline true表示有下划线，false表示没有下划线
     */
    void setFontUnderline(bool underline) const;

    /**
     * @brief 设置字体是否有删除线
     * @param strikeOut true表示有删除线，false表示没有删除线
     */
    void setFontStrikeOut(bool strikeOut) const;

    /**
     * @brief 设置文本对齐方式
     * @param halign 水平对齐方式
     * @param valign 垂直对齐方式
     */
    void setTextAlign(TextHAlign halign, TextVAlign valign) const;

    /**
     * @brief 绘制像素点
     * @param x x坐标
     * @param y y坐标
     */
    void drawPixel(int x, int y, const Color &color) const;

    /**
     * @brief 这是一个重载，绘制像素点
     * @param pos 像素点坐标
     */
    void drawPixel(const Point &pos, const Color &color) const;

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
     * @brief 绘制填充矩形
     * @param x 矩形左上角的x坐标
     * @param y 矩形左上角的y坐标
     * @param w 矩形的宽度
     * @param h 矩形的高度
     */
    void drawFillRect(int x, int y, int w, int h) const;

    /**
     * @brief 这是一个重载，绘制填充矩形
     * @param rect 矩形
     */
    void drawFillRect(const Rect &rect) const;

    /**
     * @brief 这是一个重载，绘制圆角矩形
     * @param rect 矩形
     * @param r 矩形的圆角半径
     */

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
     * @brief 绘制填充椭圆
     * @param x 椭圆外接矩形左上角的x坐标
     * @param y 椭圆外接矩形左上角的y坐标
     * @param w 椭圆外接矩形的宽度
     * @param h 椭圆外接矩形的高度
     */
    void drawFillEllipse(int x, int y, int w, int h) const;

    /**
     * @brief 这是一个重载，绘制填充椭圆
     * @param rect 椭圆外接矩形
     */
    void drawFillEllipse(const Rect &rect) const;

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
     * @note 起始角度和终止角度的单位是度，逆时针方向为正，0度为3点钟方向
     */
    void drawArc(int x, int y, int rx, int ry, int startAngle, int endAngle) const;

    /**
     * @brief 这是一个重载，绘制弧线
     * @param rect 弧线所在椭圆的外接矩形
     * @param startAngle 弧线的起始角度
     * @param endAngle 弧线的终止角度
     * @note 起始角度和终止角度的单位是度，逆时针方向为正，0度为3点钟方向
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

    /**
     * @brief 绘制像素图
     * @param x 像素图左上角的x坐标
     * @param y 像素图左上角的y坐标
     * @param pixelmap 像素图
     * @param blendMode 像素图混合模式，默认值为"S"，即源像素
     * @note blendMode参数是用逆波兰表示法来表示的，具体如下：
     * @note "S" : 源像素颜色
     * @note "D" : 目标像素颜色
     * @note "P" : 当前画刷颜色
     */
    void drawPixelMap(int x, int y, const PixelMap &pixelmap,
                      BlendMode blendMode = BlendMode::S) const;

    /**
     * @brief 这是一个重载，绘制像素图
     * @param pos 像素图左上角的位置
     * @param pixelmap 像素图
     * @param blendMode 像素图混合模式，默认值为"S"，即源像素
     * @note blendMode参数是用逆波兰表示法来表示的，具体如下：
     * @note "S" : 源像素颜色
     * @note "D" : 目标像素颜色
     * @note "P" : 当前画刷颜色
     */
    void drawPixelMap(const Point &pos, const PixelMap &pixelmap,
                      BlendMode blendMode = BlendMode::S) const;

    /**
     * @brief 绘制像素图
     * @param rect 像素图所在的矩形
     * @param pixelmap 像素图
     * @param blendMode 像素图混合模式，默认值为"S"，即源像素
     * @note blendMode参数是用逆波兰表示法来表示的，具体如下：
     * @note "S" : 源像素颜色
     * @note "D" : 目标像素颜色
     * @note "P" : 当前画刷颜色
     */
    void drawPixelMap(const Rect &rect, const PixelMap &pixelmap,
                      const Point &pixelmapSrcPos,
                      BlendMode blendMode = BlendMode::S) const;

    /**
     * @brief 绘制圆
     * @param x 圆心的x坐标
     * @param y 圆心的y坐标
     * @param r 圆的半径
     * @note 该函数等价于drawEllipse(x-r, y-r, 2*r, 2*r)
     */
    void drawCircle(int x, int y, int r) const;

    /**
     * @brief 这是一个重载，绘制圆
     * @param pos 圆心的位置
     * @param r 圆的半径
     * @note 该函数等价于drawEllipse(pos.x()-r, pos.y()-r, 2*r, 2*r)
     */
    void drawCircle(const Point &pos, int r) const;

    /**
     * @brief 绘制填充圆
     * @param x 圆心的x坐标
     * @param y 圆心的y坐标
     * @param r 圆的半径
     * @note 该函数等价于drawFillEllipse(x-r, y-r, 2*r, 2*r)
     */
    void drawFillCircle(int x, int y, int r) const;

    /**
     * @brief 这是一个重载，绘制填充圆
     * @param pos 圆心的位置
     * @param r 圆的半径
     * @note 该函数等价于drawFillEllipse(pos.x()-r, pos.y()-r, 2*r, 2*r)
     */
    void drawFillCircle(const Point &pos, int r) const;

    /**
     * @brief 绘制圆角矩形
     * @param x 矩形左上角的x坐标
     * @param y 矩形左上角的y坐标
     * @param w 矩形的宽度
     * @param h 矩形的高度
     * @param rx 矩形的圆角x方向半径
     * @param ry 矩形的圆角y方向半径
     */
    void drawRoundRect(int x, int y, int w, int h, int rx, int ry) const;

    /**
     * @brief 这是一个重载，绘制圆角矩形
     * @param rect 矩形
     * @param rx 矩形的圆角x方向半径
     * @param ry 矩形的圆角y方向半径
     */
    void drawRoundRect(const Rect &rect, int rx, int ry) const;

    /**
     * @brief 绘制填充圆角矩形
     * @param x 矩形左上角的x坐标
     * @param y 矩形左上角的y坐标
     * @param w 矩形的宽度
     * @param h 矩形的高度
     * @param rx 矩形的圆角x方向半径
     * @param ry 矩形的圆角y方向半径
     */
    void drawFillRoundRect(int x, int y, int w, int h, int rx, int ry) const;

    /**
     * @brief 这是一个重载，绘制填充圆角矩形
     * @param rect 矩形
     * @param rx 矩形的圆角x方向半径
     * @param ry 矩形的圆角y方向半径
     */
    void drawFillRoundRect(const Rect &rect, int rx, int ry) const;

};

/**
 * @brief PainterEvent类
 * @details PainterEvent类是用于绘图事件传递的类，负责创建Painter对象并提供绘图相关的接口
 * @note 用户可以通过在绘图时间传递函数中如下的调用方式来创建Painter对象：
 * @code
 * auto &painter = event.beginPaint(this); // 获取Painter对象
 * // 绘图代码
 * painter.drawLine(0, 0, 100, 100);
 * ...
 * event.endPaint(); // 绘图结束时，必须调用该函数
 * @endcode
 * @note 用户无法直接创建PainterEvent对象，只能通过App来创建，此对象仅在绘图事件中使用
 * @see App
 * @see Painter
 * @see PixelMap
 */
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
    ~PaintEvent() throw();

    /**
     * @brief 构造Painter对象
     * @param block 绘制区域
     * @return Painter对象
     */
    const Painter &beginPaint(const Block *block) const;

    /**
     * @brief 结束绘制
     * @brief 结束绘制，释放Painter对象
     * @note 绘图结束时，必须调用该函数，否则会引起不可预知的错误
     */
    void endPaint() const;
};

/**@}*/