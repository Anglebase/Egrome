#include <ege.h>
#include "Painter.h"
#include "view/Painter.h"
#include "core/Exception.h"
#include "view/Painter.h"
#include "view/Color.h"
#include "core/Point.h"
#include "core/Rect.h"
#include "core/Size.h"

PainterEvent::~PainterEvent()
{
    this->endPaint();
}

const Painter &PainterEvent::beginPaint(const Block *block)
{
    if (block == nullptr)
        throw Exception("'block' can not be 'nullptr' in beginPaint()");
    if (this->painter)
        return *this->painter;
    this->painter = new Painter(block);
    return *this->painter;
}

void PainterEvent::endPaint()
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
    if (this->block)
    {
        delete this->block;
        this->block = nullptr;
    }
}

void Painter::setPenColor(const Color &color)
{
    ege::setcolor(EGERGB(color.red, color.green, color.blue));
}

void Painter::setPenWidth(int width)
{
    ege::setlinewidth(width);
}

void Painter::setPenStyle(PenStyle style)
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

void Painter::setBrushColor(const Color &color)
{
    *this->brushColor = color;
    ege::setfillcolor(EGERGB(color.red, color.green, color.blue));
}

void Painter::setBrushStyle(BrushStyle style)
{
    ege::setfillstyle(static_cast<int>(style),
                      EGERGB(this->brushColor->red,
                             this->brushColor->green,
                             this->brushColor->blue));
}

void Painter::setFont(const std::string &fontName, int size)
{
    ege::setfont(size, 0, fontName.c_str());
}

void Painter::setFont(const std::wstring &fontName, int size)
{
    ege::setfont(size, 0, fontName.c_str());
}

void Painter::setTextAlign(TextHAlign halign, TextVAlign valign)
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

void Painter::drawLine(int x1, int y1, int x2, int y2)
{
    ege::line(x1, y1, x2, y2);
}

void Painter::drawLine(const Point &p1, const Point &p2)
{
    ege::line(p1.x, p1.y, p2.x, p2.y);
}

void Painter::drawRect(int x, int y, int w, int h)
{
    ege::rectangle(x, y, x + w, y + h);
}

void Painter::drawRect(const Rect &rect)
{
    ege::rectangle(rect.left(), rect.top(), rect.right(), rect.bottom());
}

void Painter::drawEllipse(int x, int y, int w, int h)
{
    ege::ege_ellipse(x, y, x + w, y + h);
}

void Painter::drawEllipse(const Rect &rect)
{
    ege::ege_ellipse(rect.left(), rect.top(), rect.right(), rect.bottom());
}

void Painter::drawPolygon(const std::vector<Point> &points)
{
    int *lines = new int[points.size() * 2 + 2];
    for (int i = 0; i < points.size(); i++)
    {
        lines[i * 2] = points[i].x;
        lines[i * 2 + 1] = points[i].y;
    }
    lines[points.size() * 2] = points[0].x;
    lines[points.size() * 2 + 1] = points[0].y;
    ege::drawpoly(points.size() + 1, lines);
    delete[] lines;
}

void Painter::drawPolyline(const std::vector<Point> &points)
{
    int *lines = new int[points.size() * 2];
    for (int i = 0; i < points.size(); i++)
    {
        lines[i * 2] = points[i].x;
        lines[i * 2 + 1] = points[i].y;
    }
    ege::drawpoly(points.size(), lines);
    delete[] lines;
}

void Painter::drawArc(int x, int y, int rx, int ry, int startAngle, int endAngle)
{
    ege::ellipse(x, y, rx, ry, startAngle, endAngle);
}

void Painter::drawArc(const Rect &rect, int startAngle, int endAngle)
{
    ege::ellipse(rect.left() + rect.getSize().getWidth() / 2,
                 rect.top() + rect.getSize().getHeight() / 2,
                 startAngle, endAngle,
                 rect.getSize().getWidth() / 2,
                 rect.getSize().getHeight() / 2);
}

void Painter::drawText(int x, int y, const std::string &text)
{
    ege::outtextxy(x, y, text.c_str());
}

void Painter::drawText(int x, int y, const std::wstring &text)
{
    ege::outtextxy(x, y, text.c_str());
}

void Painter::drawText(const Point &pos, const std::string &text)
{
    ege::outtextxy(pos.x, pos.y, text.c_str());
}

void Painter::drawText(const Point &pos, const std::wstring &text)
{
    ege::outtextxy(pos.x, pos.y, text.c_str());
}

void Painter::drawText(const Rect &rect, const std::string &text)
{
    ege::outtextrect(rect.left(), rect.top(), rect.right(), rect.bottom(),
                     text.c_str());
}
void Painter::drawText(const Rect &rect, const std::wstring &text)
{
    ege::outtextrect(rect.left(), rect.top(), rect.right(), rect.bottom(),
                     text.c_str());
}
