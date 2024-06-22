#include "PixelMap.h"
#include "Painter.h"
#include "XString.h"
#include "Block.h"

#include <ege.h>
#include <cwchar>

void* getTarget(Painter* painter) {
    if (painter->block_)return nullptr;
    if (painter->pixelMap_)
        return (void*)painter->pixelMap_->image_;
    return nullptr;
}

Point transfrom(Painter* painter, const Point& pos) {
    if (painter->block_) {
        return pos + painter->block_->rect().pos();
    }
    if (painter->pixelMap_) {
        return pos;
    }
    return Point();
}

int operator""_em(long double value) {
    static float dpi = (
        ::GetDeviceCaps(ege::getHDC(), LOGPIXELSY) +
        ::GetDeviceCaps(ege::getHDC(), LOGPIXELSX)
        ) / 2.0f;
    float axis = (float)value * dpi / 96.0f;
    return static_cast<int>(axis * 24);
}

int operator""_em(unsigned long long value) {
    static float dpi = (
        ::GetDeviceCaps(ege::getHDC(), LOGPIXELSY) +
        ::GetDeviceCaps(ege::getHDC(), LOGPIXELSX)
        ) / 2.0f;
    float axis = (float)value * dpi / 96.0f;
    return static_cast<int>(axis * 24);
}

TextAligns::TextAligns(int aligns) noexcept : aligns(aligns) {}
TextAligns operator|(TextAlign a, TextAlign b) { return TextAligns(a | b); }
TextAligns operator|(TextAligns a, TextAlign b) { return TextAligns(a.aligns | b); }
TextAligns operator|(TextAlign a, TextAligns b) { return TextAligns(a | b.aligns); }
TextAligns operator|(TextAligns a, TextAligns b) { return TextAligns(a.aligns | b.aligns); }
bool operator&(TextAligns a, TextAlign b) { return (a.aligns & b) != 0; }
bool operator&(TextAlign a, TextAligns b) { return (a & b.aligns) != 0; }

static DWORD translateOperationCode(BlendMode blendMode) {
    switch (blendMode) {
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

#define Get ((ege::IMAGE*)getTarget(this))

Painter::Painter(Block* block) noexcept
    : block_(block), pixelMap_(nullptr),
    penColor_(0xffffff_rgb), brushColor_(0x000000_rgb) {
    ege::ege_enable_aa(true);
}

Painter::Painter(PixelMap* pixelMap) noexcept
    : block_(nullptr), pixelMap_(pixelMap),
    penColor_(0xffffff_rgb), brushColor_(0x000000_rgb) {
    ege::ege_enable_aa(true, (ege::PIMAGE)pixelMap->image_);
}

Painter::~Painter() noexcept = default;

void Painter::enabbleAntiAliasing(bool enable) noexcept {
    ege::ege_enable_aa(enable, Get);
}

void Painter::setPenColor(const Color& color) noexcept {
    this->penColor_ = color;
    ege::setcolor(EGEARGB(color.alpha(), color.red(), color.green(), color.blue()), Get);
}

void Painter::setPenWidth(int width) noexcept {
    ege::setlinewidth(width);
}

void Painter::setBrushColor(const Color& color) noexcept {
    this->brushColor_ = color;
    ege::setfillcolor(EGEARGB(color.alpha(), color.red(), color.green(), color.blue()), Get);
}

void Painter::setFontFamily(const String& fontName) noexcept {
    LOGFONTW logfont;
    ege::getfont(&logfont, Get);
    std::wstring font = (std::wstring)fontName;
    std::wcsncpy(logfont.lfFaceName, font.c_str(), LF_FACESIZE - 1);
    ege::setfont(&logfont, Get);
}

void Painter::setFontSize(int size) noexcept {
    LOGFONTW logfont;
    ege::getfont(&logfont, Get);
    logfont.lfHeight = size;
    ege::setfont(&logfont, Get);
}

void Painter::setFontWeight(int weight) noexcept {
    LOGFONTW logfont;
    ege::getfont(&logfont, Get);
    logfont.lfWeight = weight;
    ege::setfont(&logfont, Get);
}

void Painter::setFontItalic(bool italic) noexcept {
    LOGFONTW logfont;
    ege::getfont(&logfont, Get);
    logfont.lfItalic = italic;
    ege::setfont(&logfont, Get);
}

void Painter::setFontUnderline(bool underline) noexcept {
    LOGFONTW logfont;
    ege::getfont(&logfont, Get);
    logfont.lfUnderline = underline;
    ege::setfont(&logfont, Get);
}

void Painter::setFontStrikeOut(bool strikeOut) noexcept {
    LOGFONTW logfont;
    ege::getfont(&logfont, Get);
    logfont.lfStrikeOut = strikeOut;
    ege::setfont(&logfont, Get);
}

void Painter::clear(const Color& color) noexcept {
    if (this->block_) {
        ege::setfillcolor(EGEARGB(color.alpha(), color.red(), color.green(), color.blue()));
        ege::ege_fillrect(
            this->block_->rect().x(), this->block_->rect().y(),
            this->block_->rect().width(), this->block_->rect().height()
        );
        ege::setfillcolor(
            EGEARGB(
                this->brushColor_.alpha(), this->brushColor_.red(),
                this->brushColor_.green(), this->brushColor_.blue()
            )
        );
    }
    if (this->pixelMap_) {
        ege::setbkcolor(EGEARGB(color.alpha(), color.red(), color.green(), color.blue()),
            (ege::PIMAGE)this->pixelMap_->image_);
        ege::cleardevice((ege::PIMAGE)this->pixelMap_->image_);
    }
}

void Painter::drawPixel(const Point& pos_) noexcept {
    auto pos = transfrom(this, pos_);
    ege::putpixel(static_cast<int>(pos.x()), static_cast<int>(pos.y()),
        EGEARGB(this->penColor_.alpha(), this->penColor_.red(),
            this->penColor_.green(), this->penColor_.blue()), Get);
}

void Painter::drawLine(const Point& p1_, const Point& p2_) noexcept {
    auto p1 = transfrom(this, p1_);
    auto p2 = transfrom(this, p2_);
    ege::line_f(p1.x(), p1.y(), p2.x(), p2.y(), Get);
}

void Painter::drawRect(const Rect& rect_) noexcept {
    auto rect = rect_;
    rect.pos() = transfrom(this, rect.pos());
    ege::ege_rectangle(rect.x(), rect.y(), rect.width(), rect.height(), Get);
}

void Painter::drawPolygon(const std::vector<Point>& points) noexcept {
    std::vector<ege::ege_point> egePoints(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        egePoints[i].x = transfrom(this, points[i]).x();
        egePoints[i].y = transfrom(this, points[i]).y();
    }
    egePoints.push_back(egePoints.front());
    ege::ege_drawpoly(egePoints.size(), egePoints.data(), Get);
}

void Painter::drawPolyline(const std::vector<Point>& points) noexcept {
    std::vector<ege::ege_point> egePoints(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        egePoints[i].x = transfrom(this, points[i]).x();
        egePoints[i].y = transfrom(this, points[i]).y();
    }
    ege::ege_drawpoly(egePoints.size(), egePoints.data(), Get);
}

void Painter::drawArc(const Rect& rect, float startAngle, float range) noexcept {
    auto rect_ = rect;
    rect_.pos() = transfrom(this, rect_.pos());
    ege::ege_arc(rect_.x(), rect_.y(), rect_.width(), rect_.height(),
        startAngle, range, Get);
}

void Painter::drawEllipse(const Rect& rect) noexcept {
    auto rect_ = rect;
    rect_.pos() = transfrom(this, rect_.pos());
    ege::ege_ellipse(rect_.x(), rect_.y(), rect_.width(), rect_.height(), Get);
}

void Painter::drawCircle(const Point& o, float radius) noexcept {
    this->drawEllipse(Rect(o.x() - radius, o.y() - radius, radius * 2, radius * 2));
}

void Painter::drawPie(const Rect& rect, float startAngle, float range) noexcept {
    auto rect_ = rect;
    rect_.pos() = transfrom(this, rect_.pos());
    ege::ege_pie(rect_.x(), rect_.y(), rect_.width(), rect_.height(),
        startAngle, range, Get);
}
void Painter::drawBezier(const Point& p1_, const Point& c1_, const Point& p2_, const Point& c2_) noexcept {
    auto p1 = transfrom(this, p1_);
    auto c1 = transfrom(this, c1_);
    auto p2 = transfrom(this, p2_);
    auto c2 = transfrom(this, c2_);
    ege::ege_point egePoints[4] = {
        {p1.x(), p1.y()},
        {c1.x(), c1.y()},
        {c2.x(), c2.y()},
        {p2.x(), p2.y()}
    };
    ege::ege_bezier(4, egePoints, Get);
}

void Painter::drawFillRect(const Rect& rect) noexcept {
    auto rect_ = rect;
    rect_.pos() = transfrom(this, rect_.pos());
    ege::ege_fillrect(rect_.x(), rect_.y(), rect_.width(), rect_.height(), Get);
}

void Painter::drawFillPolygon(const std::vector<Point>& points) noexcept {
    std::vector<ege::ege_point> egePoints(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        egePoints[i].x = transfrom(this, points[i]).x();
        egePoints[i].y = transfrom(this, points[i]).y();
    }
    egePoints.push_back(egePoints.front());
    ege::ege_fillpoly(egePoints.size(), egePoints.data(), Get);
}

void Painter::drawFillEllipse(const Rect& rect) noexcept {
    auto rect_ = rect;
    rect_.pos() = transfrom(this, rect_.pos());
    ege::ege_fillellipse(rect_.x(), rect_.y(), rect_.width(), rect_.height(), Get);
}

void Painter::drawFillCircle(const Point& o, float radius) noexcept {
    this->drawFillEllipse(Rect(o.x() - radius, o.y() - radius, radius * 2, radius * 2));
}

void Painter::drawFillPie(const Rect& rect, float startAngle, float range) noexcept {
    auto rect_ = rect;
    rect_.pos() = transfrom(this, rect_.pos());
    ege::ege_fillpie(rect_.x(), rect_.y(), rect_.width(), rect_.height(),
        startAngle, range, Get);
}

void Painter::drawText(const Point& pos_, const String& text) noexcept {
    auto pos = transfrom(this, pos_);
    // ege::outtextxy(pos.x(), pos.y(), ((std::wstring)text).c_str(), Get);

    ege::settarget((ege::PIMAGE)Get);
    ege::ege_drawtext(((std::wstring)text).c_str(), pos.x(), pos.y());
    ege::settarget(nullptr);
}

void Painter::drawText(const Rect& rect, const String& text, TextAligns aligns) noexcept {
    Point p;
    if (aligns & TextAlign::Left) {
        p.x() = 0;
    }
    else if (aligns & TextAlign::Center) {
        p.x() = rect.width() / 2 - ege::textwidth(((std::wstring)text).c_str(), Get) / 2;
    }
    else if (aligns & TextAlign::Right) {
        p.x() = rect.width() - ege::textwidth(((std::wstring)text).c_str(), Get);
    }
    if (aligns & TextAlign::Top) {
        p.y() = 0;
    }
    else if (aligns & TextAlign::Middle) {
        p.y() = rect.height() / 2 - ege::textheight(((std::wstring)text).c_str(), Get) / 2;
    }
    else if (aligns & TextAlign::Bottom) {
        p.y() = rect.height() - ege::textheight(((std::wstring)text).c_str(), Get);
    }
    this->drawText(rect.pos() + p, text);
}

void Painter::drawPixmap(const Point& pos, const PixelMap& pixmap, BlendMode mode) noexcept {
    auto pos_ = transfrom(this, pos);
    if (this->block_) {
        ege::putimage(pos_.x(), pos_.y(),
            (ege::PIMAGE)pixmap.image_,
            translateOperationCode(mode));
    }
    if (this->pixelMap_) {
        ege::putimage((ege::PIMAGE)this->pixelMap_->image_,
            pos_.x(), pos_.y(), (ege::PIMAGE)pixmap.image_,
            translateOperationCode(mode));
    }
}

void Painter::drawPixmap(const Rect& rect, const PixelMap& pixmap, BlendMode mode) noexcept {
    auto rect_ = rect;
    rect_.pos() = transfrom(this, rect_.pos());
    if (this->block_) {
        ege::putimage(rect_.x(), rect_.y(), rect_.width(), rect_.height(),
            (ege::PIMAGE)pixmap.image_,
            0, 0, pixmap.size().width(), pixmap.size().height(),
            translateOperationCode(mode));
    }
    if (this->pixelMap_) {
        ege::putimage((ege::PIMAGE)this->pixelMap_->image_,
            rect_.x(), rect_.y(), rect_.width(), rect_.height(),
            (ege::PIMAGE)pixmap.image_,
            0, 0, pixmap.size().width(), pixmap.size().height(),
            translateOperationCode(mode));
    }
}


