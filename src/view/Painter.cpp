#include <ege.h>
#include "Painter.h"
#include "Exception.h"
#include "PixelMap.h"
#include "Color.h"
#include "Block.h"
#include "Point.h"
#include "Rect.h"
#include "Size.h"
#include "Painter.h"

PaintEvent::~PaintEvent()
{
}

const Painter &PaintEvent::beginPaint(const Block *block) const
{
    if (block == nullptr)
        throw Exception("'block' can not be 'nullptr' in beginPaint()");
    if (this->painter == nullptr)
        this->painter = new Painter(block);
    return *this->painter;
}

void PaintEvent::endPaint() const
{
    if (this->painter)
    {
        delete this->painter;
        this->painter = nullptr;
    }
}

Painter::Painter(const Block *block)
    : block(block), pixelMap(nullptr), brushColor(nullptr)
{
    this->brushColor = new Color(255, 255, 255);
    LOGFONT font;
    ege::getfont(&font);
    font.lfQuality = PROOF_QUALITY;
    ege::setfont(&font);
    ege::ege_enable_aa(true);
}

Painter::Painter(const PixelMap *pixelMap)
    : block(nullptr), pixelMap(pixelMap), brushColor(nullptr)
{
    this->brushColor = new Color(255, 255, 255);
    LOGFONT font;
    ege::getfont(&font);
    font.lfQuality = PROOF_QUALITY;
    ege::setfont(&font);
    ege::ege_enable_aa(true, (ege::IMAGE *)pixelMap->image_);
}

Painter::~Painter()
{
    if (this->brushColor)
    {
        delete this->brushColor;
        this->brushColor = nullptr;
    }
}

Rect Painter::rect() const
{
    if (this->block)
        return Rect(0, 0, this->block->rect_.width_, this->block->rect_.height_);
    if (this->pixelMap)
        return Rect(0, 0, this->pixelMap->width_, this->pixelMap->height_);
    return Rect(0, 0, 0, 0);
}

void Painter::setPenColor(const Color &color) const
{
    if (this->block)
        ege::setcolor(EGERGBA(color.red, color.green, color.blue, color.alpha));
    if (this->pixelMap)
        ege::setcolor(EGERGBA(color.red, color.green, color.blue, color.alpha),
                      (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::setPenWidth(int width) const
{
    if (this->block)
        ege::setlinewidth(width);
    if (this->pixelMap)
        ege::setlinewidth(width, (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::setPenStyle(PenStyle style) const
{
    int linestyle;
    int linewidth;
    if (this->block)
        ege::getlinestyle(&linestyle,
                          NULL,
                          &linewidth,
                          NULL);
    if (this->pixelMap)
        ege::getlinestyle(&linestyle,
                          nullptr,
                          &linewidth,
                          (ege::IMAGE *)this->pixelMap->image_);
    switch (style)
    {
    case PenStyle::Solid:
        linestyle = ege::SOLID_LINE;
        break;
    case PenStyle::Dash:
        linestyle = ege::CENTER_LINE;
        break;
    case PenStyle::Dot:
        linestyle = ege::DOTTED_LINE;
        break;
    case PenStyle::DashDot:
        linestyle = ege::DASHED_LINE;
        break;
    case PenStyle::Null:
        linestyle = ege::NULL_LINE;
        break;
    default:
        throw Exception("Invalid pen style");
    }
    if (this->block)
        ege::setlinestyle(linestyle, 0, linewidth);
    if (this->pixelMap)
        ege::setlinestyle(linestyle, 0, linewidth,
                          (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::clear(const Color &color) const
{
    if (this->block)
    {
        ege::setbkcolor(EGERGBA(color.red, color.green, color.blue, color.alpha));
        ege::cleardevice();
    }
    if (this->pixelMap)
    {
        ege::setbkcolor(EGERGBA(color.red, color.green, color.blue, color.alpha),
                        (ege::IMAGE *)this->pixelMap->image_);
        ege::cleardevice((ege::IMAGE *)this->pixelMap->image_);
    }
}

void Painter::setBrushColor(const Color &color) const
{
    *this->brushColor = color;
    if (this->block)
        ege::setfillcolor(EGERGBA(color.red, color.green, color.blue, color.alpha));
    if (this->pixelMap)
        ege::setfillcolor(EGERGBA(color.red, color.green, color.blue, color.alpha),
                          (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::setLinerGradient(const Point &start, const Color &startColor,
                               const Point &end, const Color &endColor) const
{
    if (this->block)
    {
        ege::ege_setpattern_lineargradient(
            this->block->rect_.x_ + start.x_,
            this->block->rect_.y_ + start.y_,
            EGERGBA(startColor.red, startColor.green,
                    startColor.blue, startColor.alpha),
            this->block->rect_.x_ + end.x_,
            this->block->rect_.y_ + end.y_,
            EGERGBA(endColor.red, endColor.green,
                    endColor.blue, endColor.alpha));
    }
    if (this->pixelMap)
    {
        ege::ege_setpattern_lineargradient(
            this->block->rect_.x_ + start.x_,
            this->block->rect_.y_ + start.y_,
            EGERGBA(startColor.red, startColor.green,
                    startColor.blue, startColor.alpha),
            this->block->rect_.x_ + end.x_,
            this->block->rect_.y_ + end.y_,
            EGERGBA(endColor.red, endColor.green,
                    endColor.blue, endColor.alpha),
            (ege::IMAGE *)this->pixelMap->image_);
    }
}

void Painter::setFont(const std::string &fontName, int size) const
{
    if (this->block)
        ege::setfont(size, 0, fontName.c_str());
    if (this->pixelMap)
        ege::setfont(size, 0, fontName.c_str(),
                     (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::setFont(const std::wstring &fontName, int size) const
{
    if (this->block)
        ege::setfont(size, 0, fontName.c_str());
    if (this->pixelMap)
        ege::setfont(size, 0, fontName.c_str(),
                     (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::setFontSize(int size) const
{
    LOGFONT font;
    ege::getfont(&font);
    font.lfHeight = size;
    ege::setfont(&font);
}

void Painter::setFontWeight(int weight) const
{
    LOGFONT font;
    ege::getfont(&font);
    font.lfWeight = weight;
    ege::setfont(&font);
}

void Painter::setFontItalic(bool italic) const
{
    LOGFONT font;
    ege::getfont(&font);
    font.lfItalic = italic;
    ege::setfont(&font);
}

void Painter::setFontUnderline(bool underline) const
{
    LOGFONT font;
    ege::getfont(&font);
    font.lfUnderline = underline;
    ege::setfont(&font);
}

void Painter::setFontStrikeOut(bool strikeOut) const
{
    LOGFONT font;
    ege::getfont(&font);
    font.lfStrikeOut = strikeOut;
    ege::setfont(&font);
}

void Painter::setTextAlign(TextHAlign halign, TextVAlign valign) const
{
    this->halign = halign;
    this->valign = valign;
}

void Painter::drawPixel(const Point &pos, const Color &color) const
{
    if (this->block)
        ege::putpixel(static_cast<int>(this->block->rect_.x_ + pos.x_),
                      static_cast<int>(this->block->rect_.y_ + pos.y_),
                      EGERGBA(color.red, color.green, color.blue, color.alpha));
    if (this->pixelMap)
        ege::putpixel(static_cast<int>(pos.x_),
                      static_cast<int>(pos.y_),
                      EGERGBA(color.red, color.green, color.blue, color.alpha));
}

void Painter::drawLine(const Point &p1, const Point &p2) const
{
    if (this->block)
        ege::ege_line(this->block->rect_.x_ + p1.x_,
                      this->block->rect_.y_ + p1.y_,
                      this->block->rect_.x_ + p2.x_,
                      this->block->rect_.y_ + p2.y_);
    if (this->pixelMap)
        ege::ege_line(p1.x_, p1.y_, p2.x_, p2.y_,
                      (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawRect(const Rect &rect) const
{
    if (this->block)
        ege::ege_rectangle(this->block->rect_.x_ + rect.x_,
                           this->block->rect_.y_ + rect.y_,
                           rect.width_,
                           rect.height_);
    if (this->pixelMap)
        ege::ege_rectangle(rect.x_, rect.y_, rect.width_, rect.height_,
                           (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawFillRect(const Rect &rect) const
{
    if (this->block)
        ege::ege_fillrect(this->block->rect_.x_ + rect.x_,
                          this->block->rect_.y_ + rect.y_,
                          rect.width_, rect.height_);
    if (this->pixelMap)
        ege::ege_fillrect(rect.x_, rect.y_, rect.width_, rect.height_,
                          (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawEllipse(const Rect &rect) const
{
    if (this->block)
        ege::ege_ellipse(this->block->rect_.x_ + rect.x_,
                         this->block->rect_.y_ + rect.y_,
                         rect.width_, rect.height_);
    if (this->pixelMap)
        ege::ege_ellipse(rect.x_, rect.y_, rect.width_, rect.height_,
                         (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawFillEllipse(const Rect &rect) const
{
    if (this->block)
        ege::ege_fillellipse(this->block->rect_.x_ + rect.x_,
                             this->block->rect_.y_ + rect.y_,
                             rect.width_, rect.height_);
    if (this->pixelMap)
        ege::ege_fillellipse(rect.x_, rect.y_, rect.width_, rect.height_,
                             (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawPolygon(const std::vector<Point> &points) const
{
    auto points_ = new ege::ege_point[points.size() + 1];
    for (int i = 0; i < points.size(); i++)
    {
        if (this->block)
        {
            points_[i].x = points[i].x_ + this->block->rect_.x_;
            points_[i].y = points[i].y_ + this->block->rect_.y_;
        }
        if (this->pixelMap)
        {
            points_[i].x = points[i].x_;
            points_[i].y = points[i].y_;
        }
    }
    if (this->block)
    {
        points_[points.size()].x = points[0].x_ + this->block->rect_.x_;
        points_[points.size()].y = points[0].y_ + this->block->rect_.y_;
    }
    if (this->pixelMap)
    {
        points_[points.size()].x = points[0].x_;
        points_[points.size()].y = points[0].y_;
    }
    if (this->block)
        ege::ege_drawpoly(points.size() + 1, points_);
    if (this->pixelMap)
        ege::ege_drawpoly(points.size() + 1, points_,
                          (ege::IMAGE *)this->pixelMap->image_);
    delete[] points_;
}

void Painter::drawPolyline(const std::vector<Point> &points) const
{
    auto points_ = new ege::ege_point[points.size()];
    for (int i = 0; i < points.size(); i++)
    {
        if (this->block)
        {
            points_[i].x = points[i].x_ + this->block->rect_.x_;
            points_[i].y = points[i].y_ + this->block->rect_.y_;
        }
        if (this->pixelMap)
        {
            points_[i].x = points[i].x_;
            points_[i].y = points[i].y_;
        }
    }
    if (this->block)
        ege::ege_drawpoly(points.size(), points_);
    if (this->pixelMap)
        ege::ege_drawpoly(points.size(), points_,
                          (ege::IMAGE *)this->pixelMap->image_);
    delete[] points_;
}

void Painter::drawArc(const Rect &rect, float startAngle, float angle) const
{
    if (this->block)
        ege::ege_arc(this->block->rect_.x_ + rect.x_,
                     this->block->rect_.y_ + rect.y_,
                     rect.width_, rect.height_,
                     startAngle, angle);
    if (this->pixelMap)
        ege::ege_arc(rect.x_, rect.y_, rect.width_, rect.height_,
                     startAngle, angle,
                     (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawText(const Point &pos, const std::string &text) const
{
    if (this->block)
        ege::outtextxy(static_cast<int>(this->block->rect_.x_ + pos.x_),
                       static_cast<int>(this->block->rect_.y_ + pos.y_),
                       text.c_str());
    if (this->pixelMap)
        ege::outtextxy(static_cast<int>(pos.x_), static_cast<int>(pos.y_),
                       text.c_str(),
                       (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawText(const Point &pos, const std::wstring &text) const
{
    if (this->block)
        ege::outtextxy(static_cast<int>(this->block->rect_.x_ + pos.x_),
                       static_cast<int>(this->block->rect_.y_ + pos.y_),
                       text.c_str());
    if (this->pixelMap)
        ege::outtextxy(static_cast<int>(pos.x_), static_cast<int>(pos.y_),
                       text.c_str(),
                       (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawText(const Rect &rect, const std::string &text) const
{
    Point p;
    switch (this->halign)
    {
    case TextHAlign::Left:
        p.x_ = 0;
        break;
    case TextHAlign::Center:
        p.x_ = (rect.width_ - ege::textwidth(text.c_str())) / 2;
        break;
    case TextHAlign::Right:
        p.x_ = rect.width_ - ege::textwidth(text.c_str());
        break;
    }
    switch (this->valign)
    {
    case TextVAlign::Top:
        p.y_ = 0;
        break;
    case TextVAlign::Middle:
        p.y_ = (rect.height_ - ege::textheight(text.c_str())) / 2;
        break;
    case TextVAlign::Bottom:
        p.y_ = rect.height_ - ege::textheight(text.c_str());
        break;
    }
    this->drawText(p + Point(rect.left(), rect.top()), text);
}

void Painter::drawText(const Rect &rect, const std::wstring &text) const
{
    Point p;
    switch (this->halign)
    {
    case TextHAlign::Left:
        p.x_ = 0;
        break;
    case TextHAlign::Center:
        p.x_ = (rect.width_ - ege::textwidth(text.c_str())) / 2;
        break;
    case TextHAlign::Right:
        p.x_ = rect.width_ - ege::textwidth(text.c_str());
        break;
    }
    switch (this->valign)
    {
    case TextVAlign::Top:
        p.y_ = 0;
        break;
    case TextVAlign::Middle:
        p.y_ = (rect.height_ - ege::textheight(text.c_str())) / 2;
        break;
    case TextVAlign::Bottom:
        p.y_ = rect.height_ - ege::textheight(text.c_str());
        break;
    }
    this->drawText(p + Point(rect.left(), rect.top()), text);
}

DWORD translateOperationCode(BlendMode blendMode)
{
    switch (blendMode)
    {
    case BlendMode::Mode_0:
        return 0x00000042;
    case BlendMode::DPSoon:
        return 0x00010289;
    case BlendMode::DPSona:
        return 0x00020C89;
    case BlendMode::PSon:
        return 0x000300AA;
    case BlendMode::SDPona:
        return 0x00040C88;
    case BlendMode::DPon:
        return 0x000500A9;
    case BlendMode::PDSxnon:
        return 0x00060865;
    case BlendMode::PDSaon:
        return 0x000702C5;
    case BlendMode::SDPnaa:
        return 0x00080F08;
    case BlendMode::PDSxon:
        return 0x00090245;
    case BlendMode::DPna:
        return 0x000A0329;
    case BlendMode::PSDnaon:
        return 0x000B0B2A;
    case BlendMode::SPna:
        return 0x000C0324;
    case BlendMode::PDSnaon:
        return 0x000D0B25;
    case BlendMode::PDSonon:
        return 0x000E08A5;
    case BlendMode::Pn:
        return 0x000F0001;
    case BlendMode::PDSona:
        return 0x00100C85;
    case BlendMode::DSon:
        return 0x001100A6;
    case BlendMode::SDPxnon:
        return 0x00120868;
    case BlendMode::SDPaon:
        return 0x001302C8;
    case BlendMode::DPSxnon:
        return 0x00140869;
    case BlendMode::DPSaon:
        return 0x001502C9;
    case BlendMode::PSDPSanaxx:
        return 0x00165CCA;
    case BlendMode::SSPxDSxaxn:
        return 0x00171D54;
    case BlendMode::SPxPDxa:
        return 0x00180D59;
    case BlendMode::SDPSanaxn:
        return 0x00191CC8;
    case BlendMode::PDSPaox:
        return 0x001A06C5;
    case BlendMode::SDPSxaxn:
        return 0x001B0768;
    case BlendMode::PSDPaox:
        return 0x001C06CA;
    case BlendMode::DSPDxaxn:
        return 0x001D0766;
    case BlendMode::PDSox:
        return 0x001E01A5;
    case BlendMode::PDSoan:
        return 0x001F0385;
    case BlendMode::DPSnaa:
        return 0x00200F09;
    case BlendMode::SDPxon:
        return 0x00210248;
    case BlendMode::DSna:
        return 0x00220326;
    case BlendMode::SPDnaon:
        return 0x00230B24;
    case BlendMode::SPxDSxa:
        return 0x00240D55;
    case BlendMode::PDSPanaxn:
        return 0x00251CC5;
    case BlendMode::SDPSaox:
        return 0x002606C8;
    case BlendMode::SDPSxnox:
        return 0x00271868;
    case BlendMode::DPSxa:
        return 0x00280369;
    case BlendMode::PSDPSaoxxn:
        return 0x002916CA;
    case BlendMode::DPSana:
        return 0x002A0CC9;
    case BlendMode::SSPxPDxaxn:
        return 0x002B1D58;
    case BlendMode::SPDSoax:
        return 0x002C0784;
    case BlendMode::PSDnox:
        return 0x002D060A;
    case BlendMode::PSDPxox:
        return 0x002E064A;
    case BlendMode::PSDnoan:
        return 0x002F0E2A;
    case BlendMode::PSna:
        return 0x0030032A;
    case BlendMode::SDPnaon:
        return 0x00310B28;
    case BlendMode::SDPSoox:
        return 0x00320688;
    case BlendMode::Sn:
        return 0x00330008;
    case BlendMode::SPDSaox:
        return 0x003406C4;
    case BlendMode::SPDSxnox:
        return 0x00351864;
    case BlendMode::SDPox:
        return 0x003601A8;
    case BlendMode::SDPoan:
        return 0x00370388;
    case BlendMode::PSDPoax:
        return 0x0038078A;
    case BlendMode::SPDnox:
        return 0x00390604;
    case BlendMode::SPDSxox:
        return 0x003A0644;
    case BlendMode::SPDnoan:
        return 0x003B0E24;
    case BlendMode::PSx:
        return 0x003C004A;
    case BlendMode::SPDSonox:
        return 0x003D18A4;
    case BlendMode::SPDSnaox:
        return 0x003E1B24;
    case BlendMode::PSan:
        return 0x003F00EA;
    case BlendMode::PSDnaa:
        return 0x00400F0A;
    case BlendMode::DPSxon:
        return 0x00410249;
    case BlendMode::SDxPDxa:
        return 0x00420D5D;
    case BlendMode::SPDSanaxn:
        return 0x00431CC4;
    case BlendMode::SDna:
        return 0x00440328;
    case BlendMode::DPSnaon:
        return 0x00450B29;
    case BlendMode::DSPDaox:
        return 0x004606C6;
    case BlendMode::PSDPxaxn:
        return 0x0047076A;
    case BlendMode::SDPxa:
        return 0x00480368;
    case BlendMode::PDSPDaoxxn:
        return 0x004916C5;
    case BlendMode::DPSDoax:
        return 0x004A0789;
    case BlendMode::PDSnox:
        return 0x004B0605;
    case BlendMode::SDPana:
        return 0x004C0CC8;
    case BlendMode::SSPxDSxoxn:
        return 0x004D1954;
    case BlendMode::PDSPxox:
        return 0x004E0645;
    case BlendMode::PDSnoan:
        return 0x004F0E25;
    case BlendMode::PDna:
        return 0x00500325;
    case BlendMode::DSPnaon:
        return 0x00510B26;
    case BlendMode::DPSDaox:
        return 0x005206C9;
    case BlendMode::SPDSxaxn:
        return 0x00530764;
    case BlendMode::DPSonon:
        return 0x005408A9;
    case BlendMode::Dn:
        return 0x00550009;
    case BlendMode::DPSox:
        return 0x005601A9;
    case BlendMode::DPSoan:
        return 0x00570389;
    case BlendMode::PDSPoax:
        return 0x00580785;
    case BlendMode::DPSnox:
        return 0x00590609;
    case BlendMode::DPx:
        return 0x005A0049;
    case BlendMode::DPSDonox:
        return 0x005B18A9;
    case BlendMode::DPSDxox:
        return 0x005C0649;
    case BlendMode::DPSnoan:
        return 0x005D0E29;
    case BlendMode::DPSDnaox:
        return 0x005E1B29;
    case BlendMode::DPan:
        return 0x005F00E9;
    case BlendMode::PDSxa:
        return 0x00600365;
    case BlendMode::DSPDSaoxxn:
        return 0x006116C6;
    case BlendMode::DSPDoax:
        return 0x00620786;
    case BlendMode::SDPnox:
        return 0x00630608;
    case BlendMode::SDPSoax:
        return 0x00640788;
    case BlendMode::DSPnox:
        return 0x00650606;
    case BlendMode::DSx:
        return 0x00660046;
    case BlendMode::SDPSonox:
        return 0x006718A8;
    case BlendMode::DSPDSonoxxn:
        return 0x006858A6;
    case BlendMode::PDSxxn:
        return 0x00690145;
    case BlendMode::DPSax:
        return 0x006A01E9;
    case BlendMode::PSDPSoaxxn:
        return 0x006B178A;
    case BlendMode::SDPax:
        return 0x006C01E8;
    case BlendMode::PDSPDoaxxn:
        return 0x006D1785;
    case BlendMode::SDPSnoax:
        return 0x006E1E28;
    case BlendMode::PDSxnan:
        return 0x006F0C65;
    case BlendMode::PDSana:
        return 0x00700CC5;
    case BlendMode::SSDxPDxaxn:
        return 0x00711D5C;
    case BlendMode::SDPSxox:
        return 0x00720648;
    case BlendMode::SDPnoan:
        return 0x00730E28;
    case BlendMode::DSPDxox:
        return 0x00740646;
    case BlendMode::DSPnoan:
        return 0x00750E26;
    case BlendMode::SDPSnaox:
        return 0x00761B28;
    case BlendMode::DSan:
        return 0x007700E6;
    case BlendMode::PDSax:
        return 0x007801E5;
    case BlendMode::DSPDSoaxxn:
        return 0x00791786;
    case BlendMode::DPSDnoax:
        return 0x007A1E29;
    case BlendMode::SDPxnan:
        return 0x007B0C68;
    case BlendMode::SPDSnoax:
        return 0x007C1E24;
    case BlendMode::DPSxnan:
        return 0x007D0C69;
    case BlendMode::SPxDSxo:
        return 0x007E0955;
    case BlendMode::DPSaan:
        return 0x007F03C9;
    case BlendMode::DPSaa:
        return 0x008003E9;
    case BlendMode::SPxDSxon:
        return 0x00810975;
    case BlendMode::DPSxna:
        return 0x00820C49;
    case BlendMode::SPDSnoaxn:
        return 0x00831E04;
    case BlendMode::SDPxna:
        return 0x00840C48;
    case BlendMode::PDSPnoaxn:
        return 0x00851E05;
    case BlendMode::DSPDSoaxx:
        return 0x008617A6;
    case BlendMode::PDSaxn:
        return 0x008701C5;
    case BlendMode::DSa:
        return 0x008800C6;
    case BlendMode::SDPSnaoxn:
        return 0x00891B08;
    case BlendMode::DSPnoa:
        return 0x008A0E06;
    case BlendMode::DSPDxoxn:
        return 0x008B0666;
    case BlendMode::SDPnoa:
        return 0x008C0E08;
    case BlendMode::SDPSxoxn:
        return 0x008D0668;
    case BlendMode::SSDxPDxax:
        return 0x008E1D7C;
    case BlendMode::PDSanan:
        return 0x008F0CE5;
    case BlendMode::PDSxna:
        return 0x00900C45;
    case BlendMode::SDPSnoaxn:
        return 0x00911E08;
    case BlendMode::DPSDPoaxx:
        return 0x009217A9;
    case BlendMode::SPDaxn:
        return 0x009301C4;
    case BlendMode::PSDPSoaxx:
        return 0x009417AA;
    case BlendMode::DPSaxn:
        return 0x009501C9;
    case BlendMode::DPSxx:
        return 0x00960169;
    case BlendMode::PSDPSonoxx:
        return 0x0097588A;
    case BlendMode::SDPSonoxn:
        return 0x00981888;
    case BlendMode::DSxn:
        return 0x00990066;
    case BlendMode::DPSnax:
        return 0x009A0709;
    case BlendMode::SDPSoaxn:
        return 0x009B07A8;
    case BlendMode::SPDnax:
        return 0x009C0704;
    case BlendMode::DSPDoaxn:
        return 0x009D07A6;
    case BlendMode::DSPDSaoxx:
        return 0x009E16E6;
    case BlendMode::PDSxan:
        return 0x009F0345;
    case BlendMode::DPa:
        return 0x00A000C9;
    case BlendMode::PDSPnaoxn:
        return 0x00A11B05;
    case BlendMode::DPSnoa:
        return 0x00A20E09;
    case BlendMode::DPSDxoxn:
        return 0x00A30669;
    case BlendMode::PDSPonoxn:
        return 0x00A41885;
    case BlendMode::PDxn:
        return 0x00A50065;
    case BlendMode::DSPnax:
        return 0x00A60706;
    case BlendMode::PDSPoaxn:
        return 0x00A707A5;
    case BlendMode::DPSoa:
        return 0x00A803A9;
    case BlendMode::DPSoxn:
        return 0x00A90189;
    case BlendMode::D:
        return 0x00AA0029;
    case BlendMode::DPSono:
        return 0x00AB0889;
    case BlendMode::SPDSxax:
        return 0x00AC0744;
    case BlendMode::DPSDaoxn:
        return 0x00AD06E9;
    case BlendMode::DSPnao:
        return 0x00AE0B06;
    case BlendMode::DPno:
        return 0x00AF0229;
    case BlendMode::PDSnoa:
        return 0x00B00E05;
    case BlendMode::PDSPxoxn:
        return 0x00B10665;
    case BlendMode::SSPxDSxox:
        return 0x00B21974;
    case BlendMode::SDPanan:
        return 0x00B30CE8;
    case BlendMode::PSDnax:
        return 0x00B4070A;
    case BlendMode::DPSDoaxn:
        return 0x00B507A9;
    case BlendMode::DPSDPaoxx:
        return 0x00B616E9;
    case BlendMode::SDPxan:
        return 0x00B70348;
    case BlendMode::PSDPxax:
        return 0x00B8074A;
    case BlendMode::DSPDaoxn:
        return 0x00B906E6;
    case BlendMode::DPSnao:
        return 0x00BA0B09;
    case BlendMode::DSno:
        return 0x00BB0226;
    case BlendMode::SPDSanax:
        return 0x00BC1CE4;
    case BlendMode::SDxPDxan:
        return 0x00BD0D7D;
    case BlendMode::DPSxo:
        return 0x00BE0269;
    case BlendMode::DPSano:
        return 0x00BF08C9;
    case BlendMode::PSa:
        return 0x00C000CA;
    case BlendMode::SPDSnaoxn:
        return 0x00C11B04;
    case BlendMode::SPDSonoxn:
        return 0x00C21884;
    case BlendMode::PSxn:
        return 0x00C3006A;
    case BlendMode::SPDnoa:
        return 0x00C40E04;
    case BlendMode::SPDSxoxn:
        return 0x00C50664;
    case BlendMode::SDPnax:
        return 0x00C60708;
    case BlendMode::PSDPoaxn:
        return 0x00C707AA;
    case BlendMode::SDPoa:
        return 0x00C803A8;
    case BlendMode::SPDoxn:
        return 0x00C90184;
    case BlendMode::DPSDxax:
        return 0x00CA0749;
    case BlendMode::SPDSaoxn:
        return 0x00CB06E4;
    case BlendMode::S:
        return 0x00CC0020;
    case BlendMode::SDPono:
        return 0x00CD0888;
    case BlendMode::SDPnao:
        return 0x00CE0B08;
    case BlendMode::SPno:
        return 0x00CF0224;
    case BlendMode::PSDnoa:
        return 0x00D00E0A;
    case BlendMode::PSDPxoxn:
        return 0x00D1066A;
    case BlendMode::PDSnax:
        return 0x00D20705;
    case BlendMode::SPDSoaxn:
        return 0x00D307A4;
    case BlendMode::SSPxPDxax:
        return 0x00D41D78;
    case BlendMode::DPSanan:
        return 0x00D50CE9;
    case BlendMode::PSDPSaoxx:
        return 0x00D616EA;
    case BlendMode::DPSxan:
        return 0x00D70349;
    case BlendMode::PDSPxax:
        return 0x00D80745;
    case BlendMode::SDPSaoxn:
        return 0x00D906E8;
    case BlendMode::DPSDanax:
        return 0x00DA1CE9;
    case BlendMode::SPxDSxan:
        return 0x00DB0D75;
    case BlendMode::SPDnao:
        return 0x00DC0B04;
    case BlendMode::SDno:
        return 0x00DD0228;
    case BlendMode::SDPxo:
        return 0x00DE0268;
    case BlendMode::SDPano:
        return 0x00DF08C8;
    case BlendMode::PDSoa:
        return 0x00E003A5;
    case BlendMode::PDSoxn:
        return 0x00E10185;
    case BlendMode::DSPDxax:
        return 0x00E20746;
    case BlendMode::PSDPaoxn:
        return 0x00E306EA;
    case BlendMode::SDPSxax:
        return 0x00E40748;
    case BlendMode::PDSPaoxn:
        return 0x00E506E5;
    case BlendMode::SDPSanax:
        return 0x00E61CE8;
    case BlendMode::SPxPDxan:
        return 0x00E70D79;
    case BlendMode::SSPxDSxax:
        return 0x00E81D74;
    case BlendMode::DSPDSanaxxn:
        return 0x00E95CE6;
    case BlendMode::DPSao:
        return 0x00EA02E9;
    case BlendMode::DPSxno:
        return 0x00EB0849;
    case BlendMode::SDPao:
        return 0x00EC02E8;
    case BlendMode::SDPxno:
        return 0x00ED0848;
    case BlendMode::DSo:
        return 0x00EE0086;
    case BlendMode::SDPnoo:
        return 0x00EF0A08;
    case BlendMode::P:
        return 0x00F00021;
    case BlendMode::PDSono:
        return 0x00F10885;
    case BlendMode::PDSnao:
        return 0x00F20B05;
    case BlendMode::PSno:
        return 0x00F3022A;
    case BlendMode::PSDnao:
        return 0x00F40B0A;
    case BlendMode::PDno:
        return 0x00F50225;
    case BlendMode::PDSxo:
        return 0x00F60265;
    case BlendMode::PDSano:
        return 0x00F708C5;
    case BlendMode::PDSao:
        return 0x00F802E5;
    case BlendMode::PDSxno:
        return 0x00F90845;
    case BlendMode::DPo:
        return 0x00FA0089;
    case BlendMode::DPSnoo:
        return 0x00FB0A09;
    case BlendMode::PSo:
        return 0x00FC008A;
    case BlendMode::PSDnoo:
        return 0x00FD0A0A;
    case BlendMode::DPSoo:
        return 0x00FE02A9;
    case BlendMode::Mode_1:
        return 0x00FF0062;
    default:
        return 0x00000000;
    }
}

void Painter::drawPixelMap(const Point &pos, const PixelMap &pixelmap, BlendMode blendMode) const
{
    auto operationCode = translateOperationCode(blendMode);
    if (this->block)
        ege::putimage(this->block->rect_.x_ + pos.x_,
                      this->block->rect_.y_ + pos.y_,
                      (ege::IMAGE *)pixelmap.image_,
                      operationCode);
    if (this->pixelMap)
        ege::putimage((ege::IMAGE *)this->pixelMap->image_,
                      pos.x_, pos.y_,
                      (ege::IMAGE *)pixelmap.image_,
                      operationCode);
}

void Painter::drawPixelMap(const Rect &rect, const PixelMap &pixelmap,
                           const Point &pixelmapSrcPos,
                           BlendMode blendMode) const
{
    auto operationCode = translateOperationCode(blendMode);
    if (this->block)
        ege::putimage(this->block->rect_.x_ + rect.x_,
                      this->block->rect_.y_ + rect.y_,
                      rect.width_, rect.height_,
                      (ege::IMAGE *)pixelmap.image_,
                      pixelmapSrcPos.x_, pixelmapSrcPos.y_,
                      operationCode);
    if (this->pixelMap)
        ege::putimage((ege::IMAGE *)this->pixelMap->image_,
                      rect.x_, rect.y_,
                      rect.width_, rect.height_,
                      (ege::IMAGE *)pixelmap.image_,
                      pixelmapSrcPos.x_, pixelmapSrcPos.y_,
                      operationCode);
}

void Painter::drawPixelMap(const Rect &rect, const PixelMap &pixelmap,
                           BlendMode blendMode) const
{
    if (this->block)
    {
        ege::putimage(this->block->rect_.x_ + rect.x_,
                      this->block->rect_.y_ + rect.y_,
                      rect.width_, rect.height_,
                      (ege::IMAGE *)pixelmap.image_,
                      0, 0,
                      pixelmap.width_,
                      pixelmap.height_,
                      translateOperationCode(blendMode));
    }
    if (this->pixelMap)
    {
        ege::putimage((ege::IMAGE *)this->pixelMap->image_,
                      rect.x_, rect.y_,
                      rect.width_, rect.height_,
                      (ege::IMAGE *)pixelmap.image_,
                      0, 0,
                      pixelmap.width_,
                      pixelmap.height_,
                      translateOperationCode(blendMode));
    }
}

void Painter::drawCircle(const Point &pos, float r) const
{
    this->drawEllipse({pos.x_ - r, pos.y_ - r, 2 * r, 2 * r});
}

void Painter::drawFillCircle(const Point &pos, float r) const
{
    this->drawFillEllipse({pos.x_ - r, pos.y_ - r, 2 * r, 2 * r});
}

void Painter::drawRoundRect(const Rect &rect, float rx, float ry) const
{
    float x, y, w, h;
    x = rect.x_;
    y = rect.y_;
    w = rect.width_;
    h = rect.height_;
    this->drawLine({x + rx, y}, {x + w - rx, y});
    this->drawLine({x + w, y + ry}, {x + w, y + h - ry});
    this->drawLine({x + w - rx, y + h}, {x + rx, y + h});
    this->drawLine({x, y + h - ry}, {x, y + ry});
    this->drawArc({x, y, 2 * rx, 2 * ry}, 180, 90);
    this->drawArc({x + w - 2 * rx, y, 2 * rx, 2 * ry}, 270, 90);
    this->drawArc({x + w - 2 * rx, y + h - 2 * ry, 2 * rx, 2 * ry}, 0, 90);
    this->drawArc({x, y + h - 2 * ry, 2 * rx, 2 * ry}, 90, 90);
}

void Painter::drawFillRoundRect(const Rect &rect, float rx, float ry) const
{
    float x, y, w, h;
    x = rect.x_;
    y = rect.y_;
    w = rect.width_;
    h = rect.height_;
    this->drawFillPie(
        {x, y, 2 * rx, 2 * ry},
        180, 90);
    this->drawFillPie(
        {x + w - 2 * rx, y, 2 * rx, 2 * ry},
        0, -90);
    this->drawFillPie(
        {x + w - 2 * rx, y + h - 2 * ry, 2 * rx, 2 * ry},
        0, 90);
    this->drawFillPie(
        {x, y + h - 2 * ry, 2 * rx, 2 * ry},
        90, 90);
    this->drawFillRect({x + rx, y, w - 2 * rx, ry});
    this->drawFillRect({x + rx, y + h - ry, w - 2 * rx, ry});
    this->drawFillRect({x, y + ry, w, h - 2 * ry});
}

long Painter::getTextWidth(const std::string &text) const
{
    if (this->block)
        return ege::textwidth(text.c_str());
    if (this->pixelMap)
        return ege::textwidth(text.c_str(), (ege::IMAGE *)this->pixelMap->image_);
    return -1;
}

long Painter::getTextWidth(const std::wstring &text) const
{
    if (this->block)
        return ege::textwidth(text.c_str());
    if (this->pixelMap)
        return ege::textwidth(text.c_str(), (ege::IMAGE *)this->pixelMap->image_);
    return -1;
}

long Painter::getTextHeight(const std::string &text) const
{
    if (this->block)
        return ege::textheight(text.c_str());
    if (this->pixelMap)
        return ege::textheight(text.c_str(), (ege::IMAGE *)this->pixelMap->image_);
    return -1;
}

long Painter::getTextHeight(const std::wstring &text) const
{
    if (this->block)
        return ege::textheight(text.c_str());
    if (this->pixelMap)
        return ege::textheight(text.c_str(), (ege::IMAGE *)this->pixelMap->image_);
    return -1;
}

void Painter::drawPie(const Rect &rect, int startAngle, int angle) const
{
    if (this->block)
        ege::ege_pie(
            this->block->rect_.x_ + rect.x_,
            this->block->rect_.y_ + rect.y_,
            rect.width_, rect.height_,
            startAngle, angle);
    if (this->pixelMap)
        ege::ege_pie(
            rect.x_, rect.y_, rect.width_, rect.height_,
            startAngle, angle,
            (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawFillPie(const Rect &rect, int startAngle, int angle) const
{
    if (this->block)
        ege::ege_fillpie(
            this->block->rect_.x_ + rect.x_,
            this->block->rect_.y_ + rect.y_,
            rect.width_, rect.height_,
            startAngle, angle);
    if (this->pixelMap)
        ege::ege_fillpie(
            rect.x_, rect.y_, rect.width_, rect.height_,
            startAngle, angle,
            (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawBezier(const Point &point1, const Point &point2,
                         const Point &control1, const Point &control2) const
{
    if (this->block)
    {
        ege::ege_point p[4] = {
            {
                this->block->rect_.x_ + point1.x_,
                this->block->rect_.y_ + point1.y_,
            },
            {
                this->block->rect_.x_ + control1.x_,
                this->block->rect_.y_ + control1.y_,
            },
            {
                this->block->rect_.x_ + control2.x_,
                this->block->rect_.y_ + control2.y_,
            },
            {
                this->block->rect_.x_ + point2.x_,
                this->block->rect_.y_ + point2.y_,
            },
        };
        ege::ege_bezier(4, p);
    }
    if (this->pixelMap)
    {
        ege::ege_point p[4] = {
            {point1.x_, point1.y_},
            {control1.x_, control1.y_},
            {control2.x_, control2.y_},
            {point2.x_, point2.y_},
        };
        ege::ege_bezier(4, p, (ege::IMAGE *)this->pixelMap->image_);
    }
}

void Painter::drawFitCurve(const std::vector<Point> &points) const
{
    ege::ege_point *p = new ege::ege_point[points.size()];
    for (size_t i = 0; i < points.size(); ++i)
    {
        if (this->block)
        {
            p[i].x = this->block->rect_.x_ + points[i].x_;
            p[i].y = this->block->rect_.y_ + points[i].y_;
        }
        if (this->pixelMap)
        {
            p[i].x = points[i].x_;
            p[i].y = points[i].y_;
        }
    }
    if (this->block)
        ege::ege_drawcurve(points.size(), p);
    if (this->pixelMap)
        ege::ege_drawcurve(points.size(), p,
                           (ege::IMAGE *)this->pixelMap->image_);
    delete[] p;
}
