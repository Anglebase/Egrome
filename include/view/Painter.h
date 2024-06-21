#pragma once

#include <vector>
#include "./Color.h"
class Block;
class PixelMap;

class Point;
class Rect;
class String;

enum class TextAlign {
    Left = 0x01,
    Center = 0x02,
    Right = 0x04,
    Top = 0x08,
    Middle = 0x10,
    Bottom = 0x20,
};

enum class BlendMode {
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

class TextAligns {
private:
    int aligns;
public:
    TextAligns(int aligns) noexcept;
    friend class Painter;
    friend TextAligns operator|(TextAlign a, TextAlign b);
    friend TextAligns operator|(TextAligns a, TextAlign b);
    friend TextAligns operator|(TextAlign a, TextAligns b);
    friend TextAligns operator|(TextAligns a, TextAligns b);

    friend bool operator&(TextAligns a, TextAlign b);
    friend bool operator&(TextAlign a, TextAligns b);
};

TextAligns operator|(TextAlign a, TextAlign b);
TextAligns operator|(TextAligns a, TextAlign b);
TextAligns operator|(TextAlign a, TextAligns b);
TextAligns operator|(TextAligns a, TextAligns b);

bool operator&(TextAligns a, TextAlign b);
bool operator&(TextAlign a, TextAligns b);


class Painter final : public Object {
    friend class PaintEvent;
    friend class PixelMap;

    friend void* getTarget(Painter* painter);
    friend Point transfrom(Painter* painter, const Point& pos);
private:
    Block* block_;
    PixelMap* pixelMap_;

    Color penColor_;
    Color brushColor_;

    Painter(Block* block) noexcept;
    Painter(PixelMap* pixelMap) noexcept;
public:
    Painter(const Painter& other) = delete;
    Painter& operator=(const Painter& other) = delete;
    Painter(Painter&& other) = delete;
    Painter& operator=(Painter&& other) = delete;
    ~Painter() noexcept;

    void setPenColor(const Color& color) noexcept;
    void setPenWidth(int width) noexcept;
    // void setPenStyle(int style) noexcept;

    void setBrushColor(const Color& color) noexcept;
    // void setBrushStyle(int style) noexcept;

    void setFontFamily(const String& fontName) noexcept;
    void setFontSize(int size) noexcept;
    void setFontWeight(int weight) noexcept;
    void setFontItalic(bool italic) noexcept;
    void setFontUnderline(bool underline) noexcept;
    void setFontStrikeOut(bool strikeOut) noexcept;

    void clear(const Color& color) noexcept;


    void drawPixel(const Point& pos) noexcept;

    void drawLine(const Point& p1, const Point& p2) noexcept;
    void drawRect(const Rect& rect) noexcept;
    void drawPolygon(const std::vector<Point>& points) noexcept;
    void drawPolyline(const std::vector<Point>& points) noexcept;

    void drawArc(const Rect& rect, float startAngle, float range) noexcept;
    void drawEllipse(const Rect& rect) noexcept;
    void drawPie(const Rect& rect, float startAngle, float range) noexcept;
    void drawBezier(
        const Point& p1, const Point& c1,
        const Point& p2, const Point& c2
    ) noexcept;

    void fillRect(const Rect& rect) noexcept;
    void fillPolygon(const std::vector<Point>& points) noexcept;
    void fillEllipse(const Rect& rect) noexcept;
    void fillPie(const Rect& rect, float startAngle, float range) noexcept;

    void drawText(const Point& pos, const String& text) noexcept;
    void drawText(
        const Rect& rect, const String& text,
        TextAligns aligns = TextAlign::Left | TextAlign::Top
    ) noexcept;

    void drawPixmap(
        const Point& pos, const PixelMap& pixmap,
        BlendMode mode = BlendMode::S
    ) noexcept;
    void drawPixmap(
        const Rect& rect, const PixelMap& pixmap,
        BlendMode mode = BlendMode::S
    ) noexcept;
};