#include "App.h"
#include "Painter.h"
#include "PaintEvent.h"

class Window :public Block {
protected:
    void paintEvent(PaintEvent& event) override {
        auto& painter = event.beginPaint(this);
        painter.setBrushColor(0x12345678_rgba);
        painter.setPenColor(0x87654371_rgba);
        painter.setFontFamily(L"思源黑体");
        painter.setFontSize(2_em);
        painter.setFontWeight(800);
        painter.setFontItalic(true);
        painter.setFontUnderline(true);
        painter.setFontStrikeOut(true);
        painter.setPenWidth(10);
        painter.clear(0xffffffff_rgba);
        painter.drawText(Point{ 10,10 }, std::to_wstring(App::getFps()));
        painter.drawRect(Rect{ 10,10,100,50 });
        painter.drawFillRect(Rect{ 20,20,100,50 });
        painter.drawLine({ 50,60 }, { 150,60 });
        painter.drawEllipse({ 50,100,100,50 });
        painter.drawArc({ 50,150,100,50 }, 0, 170);
        painter.drawPolygon({ { 50,200 }, { 100,250 }, { 150,200 } });
        painter.setFontSize(1_em);
        painter.drawText(Point{ 50,300 }, L"思源黑体%d");
        painter.drawFillPolygon({ {50,300},{60,350},{70,300},{80,350},{90,400},{60,450} });

        painter.setPenColor(0x0011ff90_rgba);
        painter.setPenWidth(5);
        std::vector<Point> points{ { 200,400 }, { 100,400 }, { 400,500 }, { 200,500 } };
        painter.drawBezier(points[0], points[1], points[2], points[3]);
        painter.setPenWidth(2);
        painter.drawLine(points[0], points[1]);
        painter.drawLine(points[2], points[3]);
        painter.setBrushColor(0xff8000a0_rgba);
        painter.drawFillCircle(points[0], 5);
        painter.drawFillCircle(points[1], 5);
        painter.drawFillCircle(points[2], 5);
        painter.drawFillCircle(points[3], 5);


        event.endPaint(painter);
    }
public:
    Window(const Rect& rect, Block* parent = nullptr) :Block(rect, parent) {

    }
};

int main() {
    Window window{ Rect{0, 0, 1000, 800} };
    App app{ &window };
    app.run();
    return 0;
}
