#include "ScrollView.h"
#include "Painter.h"
#include "Size.h"
#include "App.h"

void ScrollView::paintEvent(const PaintEvent &event)
{
    auto &pixelMapPainter = this->view_->beginPaint();
    this->paintEvent(pixelMapPainter);
    this->view_->endPaint();
    auto &painter = event.beginPaint(this);
    painter.setBrushColor(this->style.backgroundColor);
    painter.drawFillRect(painter.rect());
    if (this->view_)
    {
        // 页面内容未超出可视区域
        if (this->view_->getSize().width() <= painter.rect().width() &&
            this->view_->getSize().height() <= painter.rect().height())
        {
            painter.drawPixelMap(Point{0, 0}, *this->view_);
        }
        // 页面内容垂直方向超出可视区域
        else if (this->view_->getSize().width() <=
                     painter.rect().width() - this->style.scrollBarWidth &&
                 this->view_->getSize().height() > painter.rect().height())
        {
            switch (this->verPos_)
            {
            case VScrollPos::Left:
                // 绘制视图内容
                painter.setPenColor(this->style.scrollLineColor);
                painter.drawLine(
                    {
                        this->style.scrollBarWidth,
                        0,
                    },
                    {
                        this->style.scrollBarWidth,
                        this->rect().height(),
                    });
                painter.drawPixelMap(
                    Point{
                        this->style.scrollBarWidth,
                        0,
                    },
                    this->view_->clip({
                        this->clipPos_.x(),
                        this->clipPos_.y(),
                        this->view_->getSize().width(),
                        painter.rect().height(),
                    }));
                break;
            case VScrollPos::Right:
                painter.setPenColor(this->style.scrollLineColor);
                painter.drawLine(
                    {
                        this->rect().width() - this->style.scrollBarWidth,
                        0,
                    },
                    {
                        this->rect().width() - this->style.scrollBarWidth,
                        this->rect().height(),
                    });
                painter.drawPixelMap(
                    Point{0, 0},
                    this->view_->clip({
                        this->clipPos_.x(),
                        this->clipPos_.y(),
                        this->view_->getSize().width(),
                        painter.rect().height(),
                    }));
                break;
            }
        }
        // 页面内容水平方向超出可视区域
        else if (this->view_->getSize().width() > painter.rect().width() &&
                 this->view_->getSize().height() <=
                     painter.rect().height() - this->style.scrollBarWidth)
        {
            switch (this->horPos_)
            {
            case HScrollPos::Top:
                painter.setPenColor(this->style.scrollLineColor);
                painter.drawLine(
                    {
                        0,
                        this->style.scrollBarWidth,
                    },
                    {
                        this->rect().width(),
                        this->style.scrollBarWidth,
                    });
                painter.drawPixelMap(
                    Point{
                        0,
                        this->style.scrollBarWidth,
                    },
                    this->view_->clip({
                        this->clipPos_.x(),
                        this->clipPos_.y(),
                        painter.rect().width(),
                        this->view_->getSize().height(),
                    }));
                break;
            case HScrollPos::Bottom:
                painter.setPenColor(this->style.scrollLineColor);
                painter.drawLine(
                    {
                        0,
                        this->rect().height() - this->style.scrollBarWidth,
                    },
                    {
                        this->rect().width(),
                        this->rect().height() - this->style.scrollBarWidth,
                    });
                painter.drawPixelMap(
                    Point{
                        0,
                        0,
                    },
                    this->view_->clip({
                        this->clipPos_.x(),
                        this->clipPos_.y(),
                        painter.rect().width(),
                        this->view_->getSize().height(),
                    }));
                break;
            }
        }
        // 页面内容全部超出可视区域
        else
        {
            painter.setPenColor(this->style.scrollLineColor);
            switch (this->firstScrollType_)
            {
            // 优先渲染水平方向滚动条
            case ScrollType::Horizontal:
            {
                // 绘制水平滚动条区域
                switch (this->horPos_)
                {
                // 顶部滚动条
                case HScrollPos::Top:
                {
                    painter.drawLine(
                        {
                            0,
                            this->style.scrollBarWidth,
                        },
                        {
                            this->rect().width(),
                            this->style.scrollBarWidth,
                        });
                }
                break;
                // 底部滚动条
                case HScrollPos::Bottom:
                {
                    painter.drawLine(
                        {
                            0,
                            this->rect().height() - this->style.scrollBarWidth,
                        },
                        {
                            this->rect().width(),
                            this->rect().height() - this->style.scrollBarWidth,
                        });
                }
                break;
                }
                // 绘制垂直滚动条区域
                switch (this->verPos_)
                {
                // 左侧滚动条
                case VScrollPos::Left:
                {
                    painter.drawLine(
                        {
                            this->style.scrollBarWidth,
                            this->horPos_ == HScrollPos::Top ? this->style.scrollBarWidth : 0,
                        },
                        {
                            this->style.scrollBarWidth,
                            this->rect().height() - (this->horPos_ == HScrollPos::Bottom ? this->style.scrollBarWidth : 0),
                        });
                }
                break;
                // 右侧滚动条
                case VScrollPos::Right:
                {
                    painter.drawLine(
                        {
                            this->rect().width() - this->style.scrollBarWidth,
                            this->horPos_ == HScrollPos::Top ? this->style.scrollBarWidth : 0,
                        },
                        {
                            this->rect().width() - this->style.scrollBarWidth,
                            this->rect().height() - (this->horPos_ == HScrollPos::Bottom ? this->style.scrollBarWidth : 0),
                        });
                }
                break;
                }
            }
            break;
            // 优先渲染垂直方向滚动条
            case ScrollType::Vertical:
            {
                // 绘制垂直滚动条区域
                switch (this->verPos_)
                {
                // 左侧滚动条
                case VScrollPos::Left:
                {
                    painter.drawLine(
                        {
                            this->style.scrollBarWidth,
                            0,
                        },
                        {
                            this->style.scrollBarWidth,
                            this->rect().height(),
                        });
                }
                break;
                // 右侧滚动条
                case VScrollPos::Right:
                {
                    painter.drawLine(
                        {
                            this->rect().width() - this->style.scrollBarWidth,
                            0,
                        },
                        {
                            this->rect().width() - this->style.scrollBarWidth,
                            this->rect().height(),
                        });
                }
                break;
                }
                // 绘制水平滚动条区域
                switch (this->horPos_)
                {
                // 顶部滚动条
                case HScrollPos::Top:
                {
                    painter.drawLine(
                        {
                            this->verPos_ == VScrollPos::Left
                                ? this->style.scrollBarWidth
                                : 0,
                            this->style.scrollBarWidth,
                        },
                        {
                            this->rect().width() - (this->verPos_ == VScrollPos::Right
                                                        ? this->style.scrollBarWidth
                                                        : 0),
                            this->style.scrollBarWidth,
                        });
                }
                break;
                // 底部滚动条
                case HScrollPos::Bottom:
                {
                    painter.drawLine(
                        {
                            this->verPos_ == VScrollPos::Left
                                ? this->style.scrollBarWidth
                                : 0,
                            this->rect().height() - this->style.scrollBarWidth,
                        },
                        {
                            this->rect().width() - (this->verPos_ == VScrollPos::Right
                                                        ? this->style.scrollBarWidth
                                                        : 0),
                            this->rect().height() - this->style.scrollBarWidth,
                        });
                }
                break;
                }
            }
            break;
            }
            painter.drawPixelMap(
                Point{
                    this->verPos_ == VScrollPos::Left ? this->style.scrollBarWidth : 0,
                    this->horPos_ == HScrollPos::Top ? this->style.scrollBarWidth : 0,
                },
                this->view_->clip({this->clipPos_,
                                   {
                                       painter.rect().width() - this->style.scrollBarWidth,
                                       painter.rect().height() - this->style.scrollBarWidth,
                                   }}));
        }
    }
    event.endPaint();
    if (this->hasHorScroll_)
        this->horScroll_->paintEvent(event);
    if (this->hasVerScroll_)
        this->verScroll_->paintEvent(event);
}

void ScrollView::paintEvent(const Painter &painter)
{
    painter.setPenColor(Color::Green);
    painter.drawRect(painter.rect().adjusted(0, 0, -1, -1));
}

void ScrollView::mouseWheelEvent(const Point &pos, MouseWheel wheel)
{
    if (!pos.inside(this->rect()))
        return Block::mouseWheelEvent(pos, wheel);
    if (this->shifting_)
    {
        switch (wheel)
        {
        case MouseWheel::Down:
            this->clipPos_.x() += this->step_;
            break;
        case MouseWheel::Up:
            this->clipPos_.x() -= this->step_;
            break;
        }
    }
    else
    {
        switch (wheel)
        {
        case MouseWheel::Down:
            this->clipPos_.y() += this->step_;
            break;
        case MouseWheel::Up:
            this->clipPos_.y() -= this->step_;
            break;
        }
    }
    if (this->clipPos_.x() < 0)
        this->clipPos_.x() = 0;
    if (this->clipPos_.y() < 0)
        this->clipPos_.y() = 0;

    bool endx = false;
    bool endy = false;
    // 范围限制
    if (this->clipPos_.x() >
        this->view_->getSize().width() -
            (this->rect().width() - ((this->hasVerScroll_)
                                         ? this->style.scrollBarWidth
                                         : 0)))
    {
        this->clipPos_.x() =
            this->view_->getSize().width() -
            (this->rect().width() - ((this->hasVerScroll_)
                                         ? this->style.scrollBarWidth
                                         : 0));
        endx = true;
    }
    if (this->clipPos_.y() >
        this->view_->getSize().height() -
            (this->rect().height() - ((this->hasHorScroll_)
                                          ? this->style.scrollBarWidth
                                          : 0)))
    {
        this->clipPos_.y() =
            this->view_->getSize().height() -
            (this->rect().height() - ((this->hasHorScroll_)
                                          ? this->style.scrollBarWidth
                                          : 0));
        endy = true;
    }
    this->updateScroll();
    // 端点修正
    // 不进行修正会由于浮点误差造成滚动条的位置与应当显示的位置相差1像素
    if (endx)
    {
        this->horScroll_->rect().setTopRight({
            this->rect().right() - ((this->hasVerScroll_ &&
                                     this->firstScrollType_ == ScrollType::Vertical &&
                                     this->verPos_ == VScrollPos::Right)
                                        ? this->style.scrollBarWidth
                                        : 0),
            this->horScroll_->rect().top(),
        });
    }
    if (endy)
    {
        this->verScroll_->rect().setBottomLeft({
            this->verScroll_->rect().left(),
            this->rect().bottom() - ((this->hasHorScroll_ &&
                                      this->firstScrollType_ == ScrollType::Horizontal &&
                                      this->horPos_ == HScrollPos::Bottom)
                                         ? this->style.scrollBarWidth
                                         : 0),
        });
    }
    return Block::mouseWheelEvent(pos, wheel);
}

void ScrollView::keyPressEvent(Key key, KeyFlag flag)
{
    if (key == Key::Shift)
    {
        this->shifting_ = true;
    }
    return Block::keyPressEvent(key, flag);
}

void ScrollView::keyReleaseEvent(Key key, KeyFlag flag)
{
    if (key == Key::Shift)
    {
        this->shifting_ = false;
    }
    return Block::keyReleaseEvent(key, flag);
}

ScrollView::ScrollView(const Rect &rect, Block *parent)
    : Block(rect, parent), view_(nullptr)
{
    this->horScroll_ = new ScrollBar{Rect{0, 0, 0, 0}, this};
    this->horScroll_->setEnabled(true, false);
    this->horScroll_->setReference(Ref::Window);
    this->horScroll_->dragged.connect(
        [this](const Point &pos)
        {
            long offsetLeft = 0;
            long offsetRight = 0;
            if (this->hasVerScroll_ && this->firstScrollType_ == ScrollType::Vertical)
            {
                switch (this->verPos_)
                {
                case VScrollPos::Left:
                    offsetLeft = this->style.scrollBarWidth;
                    offsetRight = 0;
                    break;
                case VScrollPos::Right:
                    offsetLeft = 0;
                    offsetRight = this->style.scrollBarWidth;
                    break;
                }
            }
            // 范围限制
            if (this->rect().left() + offsetLeft > this->horScroll_->rect().left())
            {
                this->horScroll_->rect().setTopLeft({
                    this->rect().left() + offsetLeft,
                    this->horScroll_->rect().top(),
                });
            }
            else if (this->rect().right() - offsetRight < this->horScroll_->rect().right())
            {
                this->horScroll_->rect().setTopRight({
                    this->rect().right() - offsetRight,
                    this->horScroll_->rect().top(),
                });
            }
            // 页面裁剪位置
            auto cilpX = static_cast<long>(
                (pos.x() - this->rect().left() - offsetLeft) *
                this->view_->getSize().width() /
                (this->rect().width() - ((this->hasVerScroll_ &&
                                          this->firstScrollType_ == ScrollType::Vertical)
                                             ? this->style.scrollBarWidth
                                             : 0)));
            if (cilpX < 0)
                cilpX = 0;
            else if (cilpX > this->view_->getSize().width() -
                                 (this->rect().width() - (this->hasVerScroll_ ? this->style.scrollBarWidth : 0)))
                cilpX = this->view_->getSize().width() -
                        (this->rect().width() - (this->hasVerScroll_ ? this->style.scrollBarWidth : 0));
            this->clipPos_.x() = cilpX;
        });

    this->verScroll_ = new ScrollBar{Rect{0, 0, 0, 0}, this};
    this->verScroll_->setEnabled(false, true);
    this->verScroll_->setReference(Ref::Window);
    this->verScroll_->dragged.connect(
        [this](const Point &pos)
        {
            long offsetTop = 0;
            long offsetBottom = 0;
            if (this->hasHorScroll_ && this->firstScrollType_ == ScrollType::Horizontal)
            {
                switch (this->horPos_)
                {
                case HScrollPos::Top:
                    offsetTop = this->style.scrollBarWidth;
                    offsetBottom = 0;
                    break;
                case HScrollPos::Bottom:
                    offsetTop = 0;
                    offsetBottom = this->style.scrollBarWidth;
                    break;
                }
            }
            // 范围限制
            if (this->rect().top() + offsetTop > this->verScroll_->rect().top())
            {
                this->verScroll_->rect().setTopLeft({
                    this->verScroll_->rect().left(),
                    this->rect().top() + offsetTop,
                });
            }
            else if (this->rect().bottom() - offsetBottom < this->verScroll_->rect().bottom())
            {
                this->verScroll_->rect().setBottomLeft({
                    this->verScroll_->rect().left(),
                    this->rect().bottom() - offsetBottom,
                });
            }
            // 页面裁剪位置
            auto cilpY = static_cast<long>(
                (pos.y() - this->rect().top() - offsetTop) *
                this->view_->getSize().height() /
                (this->rect().height() - ((this->hasHorScroll_ &&
                                           this->firstScrollType_ == ScrollType::Horizontal)
                                              ? this->style.scrollBarWidth
                                              : 0)));
            if (cilpY < 0)
                cilpY = 0;
            else if (cilpY > this->view_->getSize().height() - (this->rect().height() - (this->hasHorScroll_ ? this->style.scrollBarWidth : 0)))
                cilpY = this->view_->getSize().height() - (this->rect().height() - (this->hasHorScroll_ ? this->style.scrollBarWidth : 0));
            this->clipPos_.y() = cilpY;
        });
    // 屏蔽两滚动条的焦点捕获
    this->verScroll_->onFocused.connect(
        [this](Block *block)
        {
            App::setFocusBlock(this);
        });
    this->horScroll_->onFocused.connect(
        [this](Block *block)
        {
            App::setFocusBlock(this);
        });
}

ScrollView::~ScrollView()
{
    delete this->horScroll_;
    delete this->verScroll_;
}

void ScrollView::updateScroll()
{
    if (this->view_)
    {
        // 页面内容垂直方向超出可视区域
        if (this->view_->getSize().width() <= this->rect().width() &&
            this->view_->getSize().height() <= this->rect().height())
        {
            this->hasVerScroll_ = false;
            this->hasHorScroll_ = false;
        }
        else if (this->view_->getSize().width() <=
                     this->rect().width() - this->style.scrollBarWidth &&
                 this->view_->getSize().height() > this->rect().height())
        {
            this->hasVerScroll_ = true;
            this->hasHorScroll_ = false;
            this->verScroll_->rect().setSize({
                this->style.scrollBarWidth,
                static_cast<long>(this->rect().height() * this->rect().height() * 1. /
                                  this->view_->getSize().height()),
            });
            switch (this->verPos_)
            {
            case VScrollPos::Left:
                this->verScroll_->rect().setTopLeft({
                    this->rect().left(),
                    this->rect().top() +
                        static_cast<long>(this->rect().height() * this->clipPos_.y() * 1. /
                                          this->view_->getSize().height()),
                });
                break;
            case VScrollPos::Right:
                this->verScroll_->rect().setTopRight({
                    this->rect().right(),
                    this->rect().top() +
                        static_cast<long>(this->rect().height() * this->clipPos_.y() * 1. /
                                          this->view_->getSize().height()),
                });
                break;
            }
        }
        // 页面内容水平方向超出可视区域
        else if (this->view_->getSize().width() > this->rect().width() &&
                 this->view_->getSize().height() <=
                     this->rect().height() - this->style.scrollBarWidth)
        {
            this->hasVerScroll_ = false;
            this->hasHorScroll_ = true;
            this->horScroll_->rect().setSize({
                static_cast<long>(this->rect().width() * this->rect().width() * 1. /
                                  this->view_->getSize().width()),
                this->style.scrollBarWidth,
            });
            switch (this->horPos_)
            {
            case HScrollPos::Top:
                this->horScroll_->rect().setTopLeft({
                    this->rect().left() +
                        static_cast<long>(this->rect().width() * this->clipPos_.x() * 1. /
                                          this->view_->getSize().width()),
                    this->rect().top(),
                });
                break;
            case HScrollPos::Bottom:
                this->horScroll_->rect().setBottomLeft({
                    this->rect().left() +
                        static_cast<long>(this->rect().width() * this->clipPos_.x() * 1. /
                                          this->view_->getSize().width()),
                    this->rect().bottom(),
                });
                break;
            }
        }
        // 页面内容全部超出可视区域
        else
        {
            this->hasVerScroll_ = true;
            this->hasHorScroll_ = true;
            // 渲染优先级判定
            switch (this->firstScrollType_)
            {
            // 优先渲染水平方向滚动条
            case ScrollType::Horizontal:
            {
                // 水平方向滚动条
                this->horScroll_->rect().setSize({
                    static_cast<long>((this->rect().width() - this->style.scrollBarWidth) *
                                      this->rect().width() *
                                      1. /
                                      this->view_->getSize().width()),
                    this->style.scrollBarWidth,
                });
                // 水平滚动条渲染位置
                switch (this->horPos_)
                {
                // 顶部
                case HScrollPos::Top:
                    this->horScroll_->rect().setTopLeft({
                        this->rect().left() +
                            static_cast<long>(this->rect().width() *
                                              this->clipPos_.x() *
                                              1. /
                                              this->view_->getSize().width()),
                        this->rect().top(),
                    });
                    break;
                // 底部
                case HScrollPos::Bottom:
                    this->horScroll_->rect().setBottomLeft({
                        this->rect().left() +
                            static_cast<long>(this->rect().width() *
                                              this->clipPos_.x() *
                                              1. /
                                              this->view_->getSize().width()),
                        this->rect().bottom(),
                    });
                    break;
                }
                // 垂直方向滚动条
                this->verScroll_->rect().setSize({
                    this->style.scrollBarWidth,
                    static_cast<long>((this->rect().height() - this->style.scrollBarWidth) *
                                      (this->rect().height() - this->style.scrollBarWidth) * 1. /
                                      this->view_->getSize().height()),
                });
                switch (this->verPos_)
                {
                case VScrollPos::Left:
                    this->verScroll_->rect().setTopLeft({
                        this->rect().left(),
                        this->rect().top() + (this->horPos_ == HScrollPos::Top ? this->style.scrollBarWidth : 0) +
                            static_cast<long>((this->rect().height() - this->style.scrollBarWidth) *
                                              this->clipPos_.y() *
                                              1. /
                                              this->view_->getSize().height()),
                    });
                    break;
                case VScrollPos::Right:
                    this->verScroll_->rect().setTopRight({
                        this->rect().right(),
                        this->rect().top() + (this->horPos_ == HScrollPos::Top ? this->style.scrollBarWidth : 0) +
                            static_cast<long>((this->rect().height() - this->style.scrollBarWidth) *
                                              this->clipPos_.y() *
                                              1. /
                                              this->view_->getSize().height()),
                    });
                    break;
                }
            }
            break;
            // 优先渲染垂直方向滚动条
            case ScrollType::Vertical:
            {
                // 垂直方向滚动条
                this->verScroll_->rect().setSize({
                    this->style.scrollBarWidth,
                    static_cast<long>((this->rect().height() - this->style.scrollBarWidth) *
                                      this->rect().height() *
                                      1. /
                                      this->view_->getSize().height()),
                });
                switch (this->verPos_)
                {
                case VScrollPos::Left:
                    this->verScroll_->rect().setTopLeft({
                        this->rect().left(),
                        this->rect().top() +
                            static_cast<long>(this->rect().height() *
                                              this->clipPos_.y() *
                                              1. /
                                              this->view_->getSize().height()),
                    });
                    break;
                case VScrollPos::Right:
                    this->verScroll_->rect().setTopRight({
                        this->rect().right(),
                        this->rect().top() +
                            static_cast<long>(this->rect().height() *
                                              this->clipPos_.y() *
                                              1. /
                                              this->view_->getSize().height()),
                    });
                    break;
                }
                // 水平方向滚动条
                this->horScroll_->rect().setSize({
                    static_cast<long>((this->rect().width() - this->style.scrollBarWidth) *
                                      (this->rect().width() - this->style.scrollBarWidth) *
                                      1. /
                                      this->view_->getSize().width()),
                    this->style.scrollBarWidth,
                });
                switch (this->horPos_)
                {
                case HScrollPos::Top:
                    this->horScroll_->rect().setTopLeft({
                        this->rect().left() + (this->verPos_ == VScrollPos::Left ? this->style.scrollBarWidth : 0) +
                            static_cast<long>((this->rect().width() - this->style.scrollBarWidth) *
                                              this->clipPos_.x() *
                                              1. /
                                              this->view_->getSize().width()),
                        this->rect().top(),
                    });
                    break;
                case HScrollPos::Bottom:
                    this->horScroll_->rect().setBottomLeft({
                        this->rect().left() + (this->verPos_ == VScrollPos::Left ? this->style.scrollBarWidth : 0) +
                            static_cast<long>((this->rect().width() - this->style.scrollBarWidth) *
                                              this->clipPos_.x() *
                                              1. /
                                              this->view_->getSize().width()),
                        this->rect().bottom(),
                    });
                    break;
                }
            }
            break;
            }
        }
    }
}

void ScrollView::setView(PixelMap *view)
{
    this->view_ = view;
}

PixelMap *ScrollView::view() const
{
    return this->view_;
}

void ScrollView::setHScrollPos(HScrollPos pos)
{
    this->horPos_ = pos;
}

HScrollPos ScrollView::hScrollPos() const
{
    return this->horPos_;
}

void ScrollView::setVScrollPos(VScrollPos pos)
{
    this->verPos_ = pos;
}

VScrollPos ScrollView::vScrollPos() const
{
    return this->verPos_;
}

void ScrollView::setFirstScrollType(ScrollType type)
{
    this->firstScrollType_ = type;
}

ScrollType ScrollView::firstScrollType() const
{
    return this->firstScrollType_;
}

void ScrollBar::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);
    painter.setBrushColor(this->style.barColor);
    painter.drawFillRect(painter.rect());
    event.endPaint();
}

ScrollBar::ScrollBar(const Rect &rect, ScrollView *parent)
    : Drag(rect, parent), parent_(parent)
{
}
