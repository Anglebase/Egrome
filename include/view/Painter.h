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
 * @{
 */

/**
 * @addtogroup 视图绘制相关
 * @{
 */

/**
 * @addtogroup 枚举
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
 * 目前支持的三元光栅操作码有以下256个
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
    Middle,
    /// 底部对齐
    Bottom
};

/** @} */

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
     * @brief 使用指定颜色清除对象内容
     * @param color 指定的颜色
     */
    void clear(const Color &color) const;

    /**
     * @brief 设置填充颜色
     * @param color 填充颜色
     */
    void setBrushColor(const Color &color) const;

    /**
     * @brief 设置填充模式为线性渐变
     * @param start 起点坐标
     * @param startColor 起点颜色
     * @param end 终点坐标
     * @param endColor 终点颜色
     * @note 该模式下，将忽略当前的填充颜色
     */
    void setLinerGradient(const Point &start, const Color &startColor,
                          const Point &end, const Color &endColor) const;

    /**
     * @brief 设置字体
     * @param fontName 字体名称
     * @param size 字体大小
     */
    void setFont(const std::string &fontName, int size) const;

    /**
     * @brief 设置字体
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
     * @param pos 像素点坐标
     */
    void drawPixel(const Point &pos, const Color &color) const;

    /**
     * @brief 绘制线
     * @param p1 第一点坐标
     * @param p2 第二点坐标
     */
    void drawLine(const Point &p1, const Point &p2) const;

    /**
     * @brief 绘制矩形
     * @param rect 矩形
     */
    void drawRect(const Rect &rect) const;

    /**
     * @brief 绘制填充矩形
     * @param rect 矩形
     */
    void drawFillRect(const Rect &rect) const;

    /**
     * @brief 绘制椭圆
     * @param rect 椭圆外接矩形
     */
    void drawEllipse(const Rect &rect) const;

    /**
     * @brief 绘制填充椭圆
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
     * @param rect 弧线所在椭圆的外接矩形
     * @param startAngle 弧线的起始角度
     * @param angle 弧线扫过的角度
     * @note 起始角度和终止角度的单位是度，顺时针方向为正，0度为3点钟方向
     */
    void drawArc(const Rect &rect, float startAngle, float angle) const;

    /**
     * @brief 绘制文本
     * @param pos 文本所在的位置
     * @param text 文本内容
     */
    void drawText(const Point &pos, const std::string &text) const;

    /**
     * @brief 绘制文本
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
     * @brief 绘制文本
     * @param rect 文本所在的矩形
     * @param text 文本内容
     */
    void drawText(const Rect &rect, const std::wstring &text) const;

    /**
     * @brief 绘制像素图
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
     * @param pixelmapSrcPos 像素图源位置
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
     * @brief 以拉伸方式绘制像素图
     * @param rect 像素图的目标位置
     * @param pixelmap 像素图
     * @param blendMode 像素图混合模式，默认值为"S"，即源像素
     */
    void drawPixelMap(const Rect &rect, const PixelMap &pixelmap,
                      BlendMode blendMode = BlendMode::S) const;

    /**
     * @brief 绘制圆
     * @param pos 圆心的位置
     * @param r 圆的半径
     * @note 该函数等价于
     * @code
     * drawEllipse({pos.x()-r, pos.y()-r}, 2*r, 2*r)
     * @endcode
     */
    void drawCircle(const Point &pos, float r) const;

    /**
     * @brief 绘制填充圆
     * @param pos 圆心的位置
     * @param r 圆的半径
     * @note 该函数等价于drawFillEllipse(pos.x()-r, pos.y()-r, 2*r, 2*r)
     */
    void drawFillCircle(const Point &pos, float r) const;

    /**
     * @brief 绘制圆角矩形
     * @param rect 矩形
     * @param rx 矩形的圆角x方向半径
     * @param ry 矩形的圆角y方向半径
     */
    void drawRoundRect(const Rect &rect, float rx, float ry) const;

    /**
     * @brief 绘制填充圆角矩形
     * @param rect 矩形
     * @param rx 矩形的圆角x方向半径
     * @param ry 矩形的圆角y方向半径
     */
    void drawFillRoundRect(const Rect &rect, float rx, float ry) const;

    /**
     * @brief 获取当前绘图环境下所绘制的文本宽度，单位为像素
     * @param text 文本内容
     * @return 文本宽度
     */
    long getTextWidth(const std::string &text) const;
    /**
     * @brief 获取当前绘图环境下所绘制的文本宽度，单位为像素
     * @param text 文本内容
     * @return 文本宽度
     * @note 通常情况下，应当使用此函数
     */
    long getTextWidth(const std::wstring &text) const;
    /**
     * @brief 获取当前绘图环境下所绘制的文本高度，单位为像素
     * @param text 文本内容
     * @return 文本高度
     */
    long getTextHeight(const std::string &text) const;
    /**
     * @brief 获取当前绘图环境下所绘制的文本高度，单位为像素
     * @param text 文本内容
     * @return 文本高度
     * @note 通常情况下，应当使用此函数
     */
    long getTextHeight(const std::wstring &text) const;

    /**
     * @brief 绘制扇形
     * @param rect 扇形所在椭圆的外接矩形
     * @param startAngle 扇形的起始角度
     * @param angle 扇形扫过的角度
     * @note 起始角度和终止角度的单位是度，顺时针方向为正，0度为3点钟方向
     */
    void drawPie(const Rect &rect, int startAngle, int angle) const;

    /**
     * @brief 绘制填充扇形
     * @param rect 扇形所在椭圆的外接矩形
     * @param startAngle 扇形的起始角度
     * @param angle 扇形扫过的角度
     * @note 起始角度和终止角度的单位是度，顺时针方向为正，0度为3点钟方向
     */
    void drawFillPie(const Rect &rect, int startAngle, int angle) const;

    /**
     * @brief 绘制贝塞尔曲线
     * @param point1 第一个端点
     * @param point2 第二个端点
     * @param control1 第一个控制点
     * @param control2 第二个控制点
     * @note 贝塞尔曲线由两个端点和两个控制点组成，端点决定了曲线的起止位置，控制点决定了曲线的弯曲程度
     */
    void drawBezier(const Point &point1, const Point &point2,
                    const Point &control1, const Point &control2) const;

    /**
     * @brief 绘制拟合曲线
     * @param points 曲线的取样点
     * @note 该函数会以尽可能平滑的方式使曲线与取样点拟合，并绘制出拟合后的曲线，拟合出的曲线会经过所有取样点
     */
    void drawFitCurve(const std::vector<Point> &points) const;
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
    ~PaintEvent();

    /**
     * @brief 构造Painter对象
     * @param block 绘制区域
     * @return Painter对象
     */
    const Painter &beginPaint(const Block *block) const;

    /**
     * @brief 结束绘制
     * @brief 结束绘制，释放Painter对象
     * @warning 绘图结束时，必须调用该函数，否则会引起不可预知的错误
     */
    void endPaint() const;
};

/**@}*/
/**@}*/