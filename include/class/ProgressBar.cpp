#include "ProgressBar.h"
#include "Painter.h"

void ProgressBar::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);

    painter.setPenColor(this->borderColor);
    painter.setBrushColor(this->backgroundColor);
    painter.drawFillRect(painter.rect());
    painter.setPenWidth(this->borderWidth);
    painter.drawRect(painter.rect());
    painter.setBrushColor(this->progressColor);
    painter.drawFillRect(Rect{
        painter.rect().x(),
        painter.rect().y(),
        static_cast<int>(static_cast<double>(painter.rect().width()) * this->progress),
        painter.rect().height()
    });

    event.endPaint();
}

ProgressBar::ProgressBar(const Rect &rect, Block *parent)
    : Block(rect, parent)
{
    this->beZero.emit();
}

void ProgressBar::setProgress(double progress)
{
    this->progress = progress;
    if(this->progress < 0.0)
        this->progress = 0.0;
    if(this->progress > 1.0)
        this->progress = 1.0;
    this->progressChanged.emit(this->progress);
    if(this->progress >= 1.0 - 1e-10)
        this->finished.emit();
    if(this->progress <= 1e-10)
        this->beZero.emit();
}

double ProgressBar::getProgress() const
{
    return this->progress;
}
