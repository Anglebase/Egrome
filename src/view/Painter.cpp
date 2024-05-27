#include <ege.h>
#include "view/Painter.h"
#include "core/Exception.h"
#include "view/PixelMap.h"
#include "view/Color.h"
#include "view/Block.h"
#include "core/Point.h"
#include "core/Rect.h"
#include "core/Size.h"
#include "Painter.h"

PaintEvent::~PaintEvent()
{
    this->endPaint();
}

const Painter &PaintEvent::beginPaint(const Block *block) const
{
    if (block == nullptr)
        throw Exception("'block' can not be 'nullptr' in beginPaint()");
    if (this->painter == nullptr)
        this->painter = new Painter(block);
    return *this->painter;
}

void PaintEvent::endPaint()
{
    if (this->painter)
    {
        delete this->painter;
        this->painter = nullptr;
    }
}

Painter::Painter(const Block *block) : block(block), brushColor(nullptr)
{
    this->brushColor = new Color(255, 255, 255);
}

Painter::~Painter()
{
    if (this->brushColor)
    {
        delete this->brushColor;
        this->brushColor = nullptr;
    }
}

void Painter::setPenColor(const Color &color) const
{
    if (this->block)
        ege::setcolor(EGERGB(color.red, color.green, color.blue));
    if (this->pixelMap)
        ege::setcolor(EGERGB(color.red, color.green, color.blue),
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
                          nullptr,
                          &linewidth);
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
        ege::setlinestyle(linestyle, NULL, linewidth);
    if (this->pixelMap)
        ege::setlinestyle(linestyle, NULL, linewidth,
                          (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::setBrushColor(const Color &color) const
{
    *this->brushColor = color;
    if (this->block)
        ege::setfillcolor(EGERGB(color.red, color.green, color.blue));
    if (this->pixelMap)
        ege::setfillcolor(EGERGB(color.red, color.green, color.blue),
                          (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::setBrushStyle(BrushStyle style) const
{
    if (this->block)
        ege::setfillstyle(static_cast<int>(style),
                          EGERGB(this->brushColor->red,
                                 this->brushColor->green,
                                 this->brushColor->blue));
    if (this->pixelMap)
        ege::setfillstyle(static_cast<int>(style),
                          EGERGB(this->brushColor->red,
                                 this->brushColor->green,
                                 this->brushColor->blue),
                          (ege::IMAGE *)this->pixelMap->image_);
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

void Painter::setTextAlign(TextHAlign halign, TextVAlign valign) const
{
    int h, v;
    switch (halign)
    {
    case TextHAlign::Left:
        h = (int)ege::LEFT_TEXT;
        break;
    case TextHAlign::Center:
        h = (int)ege::CENTER_TEXT;
        break;
    case TextHAlign::Right:
        h = (int)ege::RIGHT_TEXT;
        break;
    default:
        throw Exception("Invalid horizontal alignment");
    }
    switch (valign)
    {
    case TextVAlign::Top:
        v = (int)ege::TOP_TEXT;
        break;
    case TextVAlign::Center:
        v = (int)ege::CENTER_TEXT;
        break;
    case TextVAlign::Bottom:
        v = (int)ege::BOTTOM_TEXT;
        break;
    default:
        throw Exception("Invalid vertical alignment");
    }
    if (this->block)
        ege::settextjustify(h, v);
    if (this->pixelMap)
        ege::settextjustify(h, v,
                            (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawLine(int x1, int y1, int x2, int y2) const
{
    if (this->block)
        ege::line(this->block->rect_.x_ + x1,
                  this->block->rect_.y_ + y1,
                  this->block->rect_.x_ + x2,
                  this->block->rect_.y_ + y2);
    if (this->pixelMap)
        ege::line(x1, y1, x2, y2, (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawLine(const Point &p1, const Point &p2) const
{
    if (this->block)
        ege::line(this->block->rect_.x_ + p1.x_,
                  this->block->rect_.y_ + p1.y_,
                  this->block->rect_.x_ + p2.x_,
                  this->block->rect_.y_ + p2.y_);
    if (this->pixelMap)
        ege::line(p1.x_, p1.y_, p2.x_, p2.y_,
                  (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawRect(int x, int y, int w, int h) const
{
    if (this->block)
        ege::rectangle(this->block->rect_.x_ + x,
                       this->block->rect_.y_ + y,
                       this->block->rect_.x_ + x + w,
                       this->block->rect_.y_ + y + h);
    if (this->pixelMap)
        ege::rectangle(x, y, x + w, y + h,
                       (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawRect(const Rect &rect) const
{
    if (this->block)
        ege::rectangle(this->block->rect_.x_ + rect.left(),
                       this->block->rect_.y_ + rect.top(),
                       this->block->rect_.x_ + rect.right(),
                       this->block->rect_.y_ + rect.bottom());
    if (this->pixelMap)
        ege::rectangle(rect.left(), rect.top(), rect.right(), rect.bottom(),
                       (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawEllipse(int x, int y, int w, int h) const
{
    if (this->block)
        ege::ege_ellipse(this->block->rect_.x_ + x,
                         this->block->rect_.y_ + y,
                         w, h);
    if (this->pixelMap)
        ege::ege_ellipse(x, y, w, h,
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

void Painter::drawPolygon(const std::vector<Point> &points) const
{
    int *lines = new int[points.size() * 2 + 2];
    for (int i = 0; i < points.size(); i++)
    {
        lines[i * 2] = points[i].x_;
        lines[i * 2 + 1] = points[i].y_;
    }
    lines[points.size() * 2] = points[0].x_;
    lines[points.size() * 2 + 1] = points[0].y_;
    if (this->block)
        ege::drawpoly(points.size() + 1, lines);
    if (this->pixelMap)
        ege::drawpoly(points.size() + 1, lines,
                      (ege::IMAGE *)this->pixelMap->image_);
    delete[] lines;
}

void Painter::drawPolyline(const std::vector<Point> &points) const
{
    int *lines = new int[points.size() * 2];
    for (int i = 0; i < points.size(); i++)
    {
        lines[i * 2] = points[i].x_;
        lines[i * 2 + 1] = points[i].y_;
    }
    if (this->block)
        ege::drawpoly(points.size(), lines);
    if (this->pixelMap)
        ege::drawpoly(points.size(), lines,
                      (ege::IMAGE *)this->pixelMap->image_);
    delete[] lines;
}

void Painter::drawArc(int x, int y, int rx, int ry, int startAngle, int endAngle) const
{
    if (this->block)
        ege::ellipse(x, y, rx, ry,
                     startAngle, endAngle);
    if (this->pixelMap)
        ege::ellipse(x, y, rx, ry,
                     startAngle, endAngle,
                     (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawArc(const Rect &rect, int startAngle, int endAngle) const
{
    if (this->block)
        ege::ellipse(rect.left() + rect.width() / 2,
                     rect.top() + rect.height() / 2,
                     startAngle, endAngle,
                     rect.width() / 2,
                     rect.height() / 2);
    if (this->pixelMap)
        ege::ellipse(rect.left() + rect.width() / 2,
                     rect.top() + rect.height() / 2,
                     startAngle, endAngle,
                     rect.width() / 2,
                     rect.height() / 2,
                     (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawText(int x, int y, const std::string &text) const
{
    if (this->block)
        ege::outtextxy(x, y, text.c_str());
    if (this->pixelMap)
        ege::outtextxy(x, y, text.c_str(),
                       (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawText(int x, int y, const std::wstring &text) const
{
    if (this->block)
        ege::outtextxy(x, y, text.c_str());
    if (this->pixelMap)
        ege::outtextxy(x, y, text.c_str(),
                       (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawText(const Point &pos, const std::string &text) const
{
    if (this->block)
        ege::outtextxy(pos.x_, pos.y_, text.c_str());
    if (this->pixelMap)
        ege::outtextxy(pos.x_, pos.y_, text.c_str(),
                       (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawText(const Point &pos, const std::wstring &text) const
{
    if (this->block)
        ege::outtextxy(pos.x_, pos.y_, text.c_str());
    if (this->pixelMap)
        ege::outtextxy(pos.x_, pos.y_, text.c_str(),
                       (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawText(const Rect &rect, const std::string &text) const
{
    if (this->block)
        ege::outtextrect(rect.left(), rect.top(), rect.right(), rect.bottom(),
                         text.c_str());
    if (this->pixelMap)
        ege::outtextrect(rect.left(), rect.top(), rect.right(), rect.bottom(),
                         text.c_str(),
                         (ege::IMAGE *)this->pixelMap->image_);
}

void Painter::drawText(const Rect &rect, const std::wstring &text) const
{
    if (this->block)
        ege::outtextrect(rect.left(), rect.top(), rect.right(), rect.bottom(),
                         text.c_str());
    if (this->pixelMap)
        ege::outtextrect(rect.left(), rect.top(), rect.right(), rect.bottom(),
                         text.c_str(),
                         (ege::IMAGE *)this->pixelMap->image_);
}

DWORD translateOperationCode(const std::string_view &blendMode)
{
    if ("0" == blendMode)
        return 0x00000042;
    if ("DPSoon" == blendMode)
        return 0x00010289;
    if ("DPSona" == blendMode)
        return 0x00020C89;
    if ("PSon" == blendMode)
        return 0x000300AA;
    if ("SDPona" == blendMode)
        return 0x00040C88;
    if ("DPon" == blendMode)
        return 0x000500A9;
    if ("PDSxnon" == blendMode)
        return 0x00060865;
    if ("PDSaon" == blendMode)
        return 0x000702C5;
    if ("SDPnaa" == blendMode)
        return 0x00080F08;
    if ("PDSxon" == blendMode)
        return 0x00090245;
    if ("DPna" == blendMode)
        return 0x000A0329;
    if ("PSDnaon" == blendMode)
        return 0x000B0B2A;
    if ("SPna" == blendMode)
        return 0x000C0324;
    if ("PDSnaon" == blendMode)
        return 0x000D0B25;
    if ("PDSonon" == blendMode)
        return 0x000E08A5;
    if ("Pn" == blendMode)
        return 0x000F0001;
    if ("PDSona" == blendMode)
        return 0x00100C85;
    if ("DSon" == blendMode)
        return 0x001100A6;
    if ("SDPxnon" == blendMode)
        return 0x00120868;
    if ("SDPaon" == blendMode)
        return 0x001302C8;
    if ("DPSxnon" == blendMode)
        return 0x00140869;
    if ("DPSaon" == blendMode)
        return 0x001502C9;
    if ("PSDPSanaxx" == blendMode)
        return 0x00165CCA;
    if ("SSPxDSxaxn" == blendMode)
        return 0x00171D54;
    if ("SPxPDxa" == blendMode)
        return 0x00180D59;
    if ("SDPSanaxn" == blendMode)
        return 0x00191CC8;
    if ("PDSPaox" == blendMode)
        return 0x001A06C5;
    if ("SDPSxaxn" == blendMode)
        return 0x001B0768;
    if ("PSDPaox" == blendMode)
        return 0x001C06CA;
    if ("DSPDxaxn" == blendMode)
        return 0x001D0766;
    if ("PDSox" == blendMode)
        return 0x001E01A5;
    if ("PDSoan" == blendMode)
        return 0x001F0385;
    if ("DPSnaa" == blendMode)
        return 0x00200F09;
    if ("SDPxon" == blendMode)
        return 0x00210248;
    if ("DSna" == blendMode)
        return 0x00220326;
    if ("SPDnaon" == blendMode)
        return 0x00230B24;
    if ("SPxDSxa" == blendMode)
        return 0x00240D55;
    if ("PDSPanaxn" == blendMode)
        return 0x00251CC5;
    if ("SDPSaox" == blendMode)
        return 0x002606C8;
    if ("SDPSxnox" == blendMode)
        return 0x00271868;
    if ("DPSxa" == blendMode)
        return 0x00280369;
    if ("PSDPSaoxxn" == blendMode)
        return 0x002916CA;
    if ("DPSana" == blendMode)
        return 0x002A0CC9;
    if ("SSPxPDxaxn" == blendMode)
        return 0x002B1D58;
    if ("SPDSoax" == blendMode)
        return 0x002C0784;
    if ("PSDnox" == blendMode)
        return 0x002D060A;
    if ("PSDPxox" == blendMode)
        return 0x002E064A;
    if ("PSDnoan" == blendMode)
        return 0x002F0E2A;
    if ("PSna" == blendMode)
        return 0x0030032A;
    if ("SDPnaon" == blendMode)
        return 0x00310B28;
    if ("SDPSoox" == blendMode)
        return 0x00320688;
    if ("Sn" == blendMode)
        return 0x00330008;
    if ("SPDSaox" == blendMode)
        return 0x003406C4;
    if ("SPDSxnox" == blendMode)
        return 0x00351864;
    if ("SDPox" == blendMode)
        return 0x003601A8;
    if ("SDPoan" == blendMode)
        return 0x00370388;
    if ("PSDPoax" == blendMode)
        return 0x0038078A;
    if ("SPDnox" == blendMode)
        return 0x00390604;
    if ("SPDSxox" == blendMode)
        return 0x003A0644;
    if ("SPDnoan" == blendMode)
        return 0x003B0E24;
    if ("PSx" == blendMode)
        return 0x003C004A;
    if ("SPDSonox" == blendMode)
        return 0x003D18A4;
    if ("SPDSnaox" == blendMode)
        return 0x003E1B24;
    if ("PSan" == blendMode)
        return 0x003F00EA;
    if ("PSDnaa" == blendMode)
        return 0x00400F0A;
    if ("DPSxon" == blendMode)
        return 0x00410249;
    if ("SDxPDxa" == blendMode)
        return 0x00420D5D;
    if ("SPDSanaxn" == blendMode)
        return 0x00431CC4;
    if ("SDna" == blendMode)
        return 0x00440328;
    if ("DPSnaon" == blendMode)
        return 0x00450B29;
    if ("DSPDaox" == blendMode)
        return 0x004606C6;
    if ("PSDPxaxn" == blendMode)
        return 0x0047076A;
    if ("SDPxa" == blendMode)
        return 0x00480368;
    if ("PDSPDaoxxn" == blendMode)
        return 0x004916C5;
    if ("DPSDoax" == blendMode)
        return 0x004A0789;
    if ("PDSnox" == blendMode)
        return 0x004B0605;
    if ("SDPana" == blendMode)
        return 0x004C0CC8;
    if ("SSPxDSxoxn" == blendMode)
        return 0x004D1954;
    if ("PDSPxox" == blendMode)
        return 0x004E0645;
    if ("PDSnoan" == blendMode)
        return 0x004F0E25;
    if ("PDna" == blendMode)
        return 0x00500325;
    if ("DSPnaon" == blendMode)
        return 0x00510B26;
    if ("DPSDaox" == blendMode)
        return 0x005206C9;
    if ("SPDSxaxn" == blendMode)
        return 0x00530764;
    if ("DPSonon" == blendMode)
        return 0x005408A9;
    if ("Dn" == blendMode)
        return 0x00550009;
    if ("DPSox" == blendMode)
        return 0x005601A9;
    if ("DPSoan" == blendMode)
        return 0x00570389;
    if ("PDSPoax" == blendMode)
        return 0x00580785;
    if ("DPSnox" == blendMode)
        return 0x00590609;
    if ("DPx" == blendMode)
        return 0x005A0049;
    if ("DPSDonox" == blendMode)
        return 0x005B18A9;
    if ("DPSDxox" == blendMode)
        return 0x005C0649;
    if ("DPSnoan" == blendMode)
        return 0x005D0E29;
    if ("DPSDnaox" == blendMode)
        return 0x005E1B29;
    if ("DPan" == blendMode)
        return 0x005F00E9;
    if ("PDSxa" == blendMode)
        return 0x00600365;
    if ("DSPDSaoxxn" == blendMode)
        return 0x006116C6;
    if ("DSPDoax" == blendMode)
        return 0x00620786;
    if ("SDPnox" == blendMode)
        return 0x00630608;
    if ("SDPSoax" == blendMode)
        return 0x00640788;
    if ("DSPnox" == blendMode)
        return 0x00650606;
    if ("DSx" == blendMode)
        return 0x00660046;
    if ("SDPSonox" == blendMode)
        return 0x006718A8;
    if ("DSPDSonoxxn" == blendMode)
        return 0x006858A6;
    if ("PDSxxn" == blendMode)
        return 0x00690145;
    if ("DPSax" == blendMode)
        return 0x006A01E9;
    if ("PSDPSoaxxn" == blendMode)
        return 0x006B178A;
    if ("SDPax" == blendMode)
        return 0x006C01E8;
    if ("PDSPDoaxxn" == blendMode)
        return 0x006D1785;
    if ("SDPSnoax" == blendMode)
        return 0x006E1E28;
    if ("PDSxnan" == blendMode)
        return 0x006F0C65;
    if ("PDSana" == blendMode)
        return 0x00700CC5;
    if ("SSDxPDxaxn" == blendMode)
        return 0x00711D5C;
    if ("SDPSxox" == blendMode)
        return 0x00720648;
    if ("SDPnoan" == blendMode)
        return 0x00730E28;
    if ("DSPDxox" == blendMode)
        return 0x00740646;
    if ("DSPnoan" == blendMode)
        return 0x00750E26;
    if ("SDPSnaox" == blendMode)
        return 0x00761B28;
    if ("DSan" == blendMode)
        return 0x007700E6;
    if ("PDSax" == blendMode)
        return 0x007801E5;
    if ("DSPDSoaxxn" == blendMode)
        return 0x00791786;
    if ("DPSDnoax" == blendMode)
        return 0x007A1E29;
    if ("SDPxnan" == blendMode)
        return 0x007B0C68;
    if ("SPDSnoax" == blendMode)
        return 0x007C1E24;
    if ("DPSxnan" == blendMode)
        return 0x007D0C69;
    if ("SPxDSxo" == blendMode)
        return 0x007E0955;
    if ("DPSaan" == blendMode)
        return 0x007F03C9;
    if ("DPSaa" == blendMode)
        return 0x008003E9;
    if ("SPxDSxon" == blendMode)
        return 0x00810975;
    if ("DPSxna" == blendMode)
        return 0x00820C49;
    if ("SPDSnoaxn" == blendMode)
        return 0x00831E04;
    if ("SDPxna" == blendMode)
        return 0x00840C48;
    if ("PDSPnoaxn" == blendMode)
        return 0x00851E05;
    if ("DSPDSoaxx" == blendMode)
        return 0x008617A6;
    if ("PDSaxn" == blendMode)
        return 0x008701C5;
    if ("DSa" == blendMode)
        return 0x008800C6;
    if ("SDPSnaoxn" == blendMode)
        return 0x00891B08;
    if ("DSPnoa" == blendMode)
        return 0x008A0E06;
    if ("DSPDxoxn" == blendMode)
        return 0x008B0666;
    if ("SDPnoa" == blendMode)
        return 0x008C0E08;
    if ("SDPSxoxn" == blendMode)
        return 0x008D0668;
    if ("SSDxPDxax" == blendMode)
        return 0x008E1D7C;
    if ("PDSanan" == blendMode)
        return 0x008F0CE5;
    if ("PDSxna" == blendMode)
        return 0x00900C45;
    if ("SDPSnoaxn" == blendMode)
        return 0x00911E08;
    if ("DPSDPoaxx" == blendMode)
        return 0x009217A9;
    if ("SPDaxn" == blendMode)
        return 0x009301C4;
    if ("PSDPSoaxx" == blendMode)
        return 0x009417AA;
    if ("DPSaxn" == blendMode)
        return 0x009501C9;
    if ("DPSxx" == blendMode)
        return 0x00960169;
    if ("PSDPSonoxx" == blendMode)
        return 0x0097588A;
    if ("SDPSonoxn" == blendMode)
        return 0x00981888;
    if ("DSxn" == blendMode)
        return 0x00990066;
    if ("DPSnax" == blendMode)
        return 0x009A0709;
    if ("SDPSoaxn" == blendMode)
        return 0x009B07A8;
    if ("SPDnax" == blendMode)
        return 0x009C0704;
    if ("DSPDoaxn" == blendMode)
        return 0x009D07A6;
    if ("DSPDSaoxx" == blendMode)
        return 0x009E16E6;
    if ("PDSxan" == blendMode)
        return 0x009F0345;
    if ("DPa" == blendMode)
        return 0x00A000C9;
    if ("PDSPnaoxn" == blendMode)
        return 0x00A11B05;
    if ("DPSnoa" == blendMode)
        return 0x00A20E09;
    if ("DPSDxoxn" == blendMode)
        return 0x00A30669;
    if ("PDSPonoxn" == blendMode)
        return 0x00A41885;
    if ("PDxn" == blendMode)
        return 0x00A50065;
    if ("DSPnax" == blendMode)
        return 0x00A60706;
    if ("PDSPoaxn" == blendMode)
        return 0x00A707A5;
    if ("DPSoa" == blendMode)
        return 0x00A803A9;
    if ("DPSoxn" == blendMode)
        return 0x00A90189;
    if ("D" == blendMode)
        return 0x00AA0029;
    if ("DPSono" == blendMode)
        return 0x00AB0889;
    if ("SPDSxax" == blendMode)
        return 0x00AC0744;
    if ("DPSDaoxn" == blendMode)
        return 0x00AD06E9;
    if ("DSPnao" == blendMode)
        return 0x00AE0B06;
    if ("DPno" == blendMode)
        return 0x00AF0229;
    if ("PDSnoa" == blendMode)
        return 0x00B00E05;
    if ("PDSPxoxn" == blendMode)
        return 0x00B10665;
    if ("SSPxDSxox" == blendMode)
        return 0x00B21974;
    if ("SDPanan" == blendMode)
        return 0x00B30CE8;
    if ("PSDnax" == blendMode)
        return 0x00B4070A;
    if ("DPSDoaxn" == blendMode)
        return 0x00B507A9;
    if ("DPSDPaoxx" == blendMode)
        return 0x00B616E9;
    if ("SDPxan" == blendMode)
        return 0x00B70348;
    if ("PSDPxax" == blendMode)
        return 0x00B8074A;
    if ("DSPDaoxn" == blendMode)
        return 0x00B906E6;
    if ("DPSnao" == blendMode)
        return 0x00BA0B09;
    if ("DSno" == blendMode)
        return 0x00BB0226;
    if ("SPDSanax" == blendMode)
        return 0x00BC1CE4;
    if ("SDxPDxan" == blendMode)
        return 0x00BD0D7D;
    if ("DPSxo" == blendMode)
        return 0x00BE0269;
    if ("DPSano" == blendMode)
        return 0x00BF08C9;
    if ("PSa" == blendMode)
        return 0x00C000CA;
    if ("SPDSnaoxn" == blendMode)
        return 0x00C11B04;
    if ("SPDSonoxn" == blendMode)
        return 0x00C21884;
    if ("PSxn" == blendMode)
        return 0x00C3006A;
    if ("SPDnoa" == blendMode)
        return 0x00C40E04;
    if ("SPDSxoxn" == blendMode)
        return 0x00C50664;
    if ("SDPnax" == blendMode)
        return 0x00C60708;
    if ("PSDPoaxn" == blendMode)
        return 0x00C707AA;
    if ("SDPoa" == blendMode)
        return 0x00C803A8;
    if ("SPDoxn" == blendMode)
        return 0x00C90184;
    if ("DPSDxax" == blendMode)
        return 0x00CA0749;
    if ("SPDSaoxn" == blendMode)
        return 0x00CB06E4;
    if ("S" == blendMode)
        return 0x00CC0020;
    if ("SDPono" == blendMode)
        return 0x00CD0888;
    if ("SDPnao" == blendMode)
        return 0x00CE0B08;
    if ("SPno" == blendMode)
        return 0x00CF0224;
    if ("PSDnoa" == blendMode)
        return 0x00D00E0A;
    if ("PSDPxoxn" == blendMode)
        return 0x00D1066A;
    if ("PDSnax" == blendMode)
        return 0x00D20705;
    if ("SPDSoaxn" == blendMode)
        return 0x00D307A4;
    if ("SSPxPDxax" == blendMode)
        return 0x00D41D78;
    if ("DPSanan" == blendMode)
        return 0x00D50CE9;
    if ("PSDPSaoxx" == blendMode)
        return 0x00D616EA;
    if ("DPSxan" == blendMode)
        return 0x00D70349;
    if ("PDSPxax" == blendMode)
        return 0x00D80745;
    if ("SDPSaoxn" == blendMode)
        return 0x00D906E8;
    if ("DPSDanax" == blendMode)
        return 0x00DA1CE9;
    if ("SPxDSxan" == blendMode)
        return 0x00DB0D75;
    if ("SPDnao" == blendMode)
        return 0x00DC0B04;
    if ("SDno" == blendMode)
        return 0x00DD0228;
    if ("SDPxo" == blendMode)
        return 0x00DE0268;
    if ("SDPano" == blendMode)
        return 0x00DF08C8;
    if ("PDSoa" == blendMode)
        return 0x00E003A5;
    if ("PDSoxn" == blendMode)
        return 0x00E10185;
    if ("DSPDxax" == blendMode)
        return 0x00E20746;
    if ("PSDPaoxn" == blendMode)
        return 0x00E306EA;
    if ("SDPSxax" == blendMode)
        return 0x00E40748;
    if ("PDSPaoxn" == blendMode)
        return 0x00E506E5;
    if ("SDPSanax" == blendMode)
        return 0x00E61CE8;
    if ("SPxPDxan" == blendMode)
        return 0x00E70D79;
    if ("SSPxDSxax" == blendMode)
        return 0x00E81D74;
    if ("DSPDSanaxxn" == blendMode)
        return 0x00E95CE6;
    if ("DPSao" == blendMode)
        return 0x00EA02E9;
    if ("DPSxno" == blendMode)
        return 0x00EB0849;
    if ("SDPao" == blendMode)
        return 0x00EC02E8;
    if ("SDPxno" == blendMode)
        return 0x00ED0848;
    if ("DSo" == blendMode)
        return 0x00EE0086;
    if ("SDPnoo" == blendMode)
        return 0x00EF0A08;
    if ("P" == blendMode)
        return 0x00F00021;
    if ("PDSono" == blendMode)
        return 0x00F10885;
    if ("PDSnao" == blendMode)
        return 0x00F20B05;
    if ("PSno" == blendMode)
        return 0x00F3022A;
    if ("PSDnao" == blendMode)
        return 0x00F40B0A;
    if ("PDno" == blendMode)
        return 0x00F50225;
    if ("PDSxo" == blendMode)
        return 0x00F60265;
    if ("PDSano" == blendMode)
        return 0x00F708C5;
    if ("PDSao" == blendMode)
        return 0x00F802E5;
    if ("PDSxno" == blendMode)
        return 0x00F90845;
    if ("DPo" == blendMode)
        return 0x00FA0089;
    if ("DPSnoo" == blendMode)
        return 0x00FB0A09;
    if ("PSo" == blendMode)
        return 0x00FC008A;
    if ("PSDnoo" == blendMode)
        return 0x00FD0A0A;
    if ("DPSoo" == blendMode)
        return 0x00FE02A9;
    if ("1" == blendMode)
        return 0x00FF0062;
    throw Exception(("Unsupported image blending mode: '" +
                     std::string(blendMode) + "'")
                        .c_str());
}

void Painter::drawPixelMap(int x, int y, const PixelMap &pixelmap,
                           const std::string_view &blendMode) const
{
    auto operationCode = translateOperationCode(blendMode);
    if (this->block)
        ege::putimage(x, y,
                      (ege::IMAGE *)pixelmap.image_,
                      operationCode);
    if (this->pixelMap)
        ege::putimage((ege::IMAGE *)this->pixelMap->image_,
                      x, y,
                      (ege::IMAGE *)pixelmap.image_,
                      operationCode);
}

void Painter::drawPixelMap(const Point &pos, const PixelMap &pixelmap, const std::string_view &blendMode) const
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
                           const std::string_view &blendMode) const
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
