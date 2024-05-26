#include <ege.h>
#include "Painter.h"
#include "view/Painter.h"
#include "core/Exception.h"
#include "view/Painter.h"
#include "view/Color.h"
#include "core/Point.h"
#include "core/Rect.h"
#include "core/Size.h"

PaintEvent::~PaintEvent()
{
    this->endPaint();
}

const Painter &PaintEvent::beginPaint(const Block *block) const
{
    if (block == nullptr)
        throw Exception("'block' can not be 'nullptr' in beginPaint()");
    if (this->painter)
        return *this->painter;
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
    ege::setcolor(EGERGB(color.red, color.green, color.blue));
}

void Painter::setPenWidth(int width) const
{
    ege::setlinewidth(width);
}

void Painter::setPenStyle(PenStyle style) const
{
    int linestyle;
    int linewidth;
    ege::getlinestyle(&linestyle, nullptr, &linewidth);
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
    ege::setlinestyle(linestyle, NULL, linewidth);
}

void Painter::setBrushColor(const Color &color) const
{
    *this->brushColor = color;
    ege::setfillcolor(EGERGB(color.red, color.green, color.blue));
}

void Painter::setBrushStyle(BrushStyle style) const
{
    ege::setfillstyle(static_cast<int>(style),
                      EGERGB(this->brushColor->red,
                             this->brushColor->green,
                             this->brushColor->blue));
}

void Painter::setFont(const std::string &fontName, int size) const
{
    ege::setfont(size, 0, fontName.c_str());
}

void Painter::setFont(const std::wstring &fontName, int size) const
{
    ege::setfont(size, 0, fontName.c_str());
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
    ege::settextjustify(h, v);
}

void Painter::drawLine(int x1, int y1, int x2, int y2) const
{
    ege::line(x1, y1, x2, y2);
}

void Painter::drawLine(const Point &p1, const Point &p2) const
{
    ege::line(p1.x_, p1.y_, p2.x_, p2.y_);
}

void Painter::drawRect(int x, int y, int w, int h) const
{
    ege::rectangle(x, y, x + w, y + h);
}

void Painter::drawRect(const Rect &rect) const
{
    ege::rectangle(rect.left(), rect.top(), rect.right(), rect.bottom());
}

void Painter::drawEllipse(int x, int y, int w, int h) const
{
    ege::ege_ellipse(x, y, x + w, y + h);
}

void Painter::drawEllipse(const Rect &rect) const
{
    ege::ege_ellipse(rect.left(), rect.top(), rect.right(), rect.bottom());
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
    ege::drawpoly(points.size() + 1, lines);
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
    ege::drawpoly(points.size(), lines);
    delete[] lines;
}

void Painter::drawArc(int x, int y, int rx, int ry, int startAngle, int endAngle) const
{
    ege::ellipse(x, y, rx, ry, startAngle, endAngle);
}

void Painter::drawArc(const Rect &rect, int startAngle, int endAngle) const
{
    ege::ellipse(rect.left() + rect.width() / 2,
                 rect.top() + rect.height() / 2,
                 startAngle, endAngle,
                 rect.width() / 2,
                 rect.height() / 2);
}

void Painter::drawText(int x, int y, const std::string &text) const
{
    ege::outtextxy(x, y, text.c_str());
}

void Painter::drawText(int x, int y, const std::wstring &text) const
{
    ege::outtextxy(x, y, text.c_str());
}

void Painter::drawText(const Point &pos, const std::string &text) const
{
    ege::outtextxy(pos.x_, pos.y_, text.c_str());
}

void Painter::drawText(const Point &pos, const std::wstring &text) const
{
    ege::outtextxy(pos.x_, pos.y_, text.c_str());
}

void Painter::drawText(const Rect &rect, const std::string &text) const
{
    ege::outtextrect(rect.left(), rect.top(), rect.right(), rect.bottom(),
                     text.c_str());
}
void Painter::drawText(const Rect &rect, const std::wstring &text) const
{
    ege::outtextrect(rect.left(), rect.top(), rect.right(), rect.bottom(),
                     text.c_str());
}
