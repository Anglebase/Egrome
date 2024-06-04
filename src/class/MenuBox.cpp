#include "MenuBox.h"
#include "Painter.h"
#include "Size.h"
#include "Rect.h"
#include <future>
#include <thread>

Divider::Divider(const Rect &rect, Block *parent)
    : Block(rect, parent) {}

void Divider::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);
    painter.setBrushColor(this->backgroundColor_);
    painter.drawFillRect(painter.rect());
    painter.setPenColor(color_);
    painter.drawLine(
        Point{0, painter.rect().height() / 2},
        Point{painter.rect().width(), painter.rect().height() / 2});
    event.endPaint();
    return Block::paintEvent(event);
}

Divider::Divider(MenuBox *parent)
    : Divider(Rect{0, parent->getHeight(), parent->rect().width(), 5}, parent)
{
    if (parent)
        parent->items_.push_back(this);
}

void Divider::setColor(const Color &color)
{
    color_ = color;
}

void Divider::setBackgroundColor(const Color &color)
{
    backgroundColor_ = color;
}

void MenuItem::paintEvent(const PaintEvent &event)
{
    auto &painter = event.beginPaint(this);

    // 绘制背景色
    if (this->clicked_ || this->clickColorAnim_->isRunning())
        painter.setBrushColor(this->clickColorAnim_->value());
    else if (this->hovered_ || this->hoverColorAnim_->isRunning())
        painter.setBrushColor(this->hoverColorAnim_->value());
    else
        painter.setBrushColor(this->defaultColor_);
    painter.drawFillRect(painter.rect());

    event.endPaint();
    // 子控件绘制绘制文字
    return Block::paintEvent(event);
}

void MenuItem::mousePressEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left &&
        this->rect().contains(pos))
    {
        this->clicked_ = true;
        MenuBox *menuBox = dynamic_cast<MenuBox *>(this->parent());
        this->clickColorAnim_->run();
        this->clicked.emit();
        if (this->childMenu_)
            this->childMenu_->show(this->rect().getTopRight());
        else
            menuBox->hide();
    }
}

void MenuItem::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    if (button == MouseButton::Left && this->clicked_)
    {
        this->clicked_ = false;
        this->clickColorAnim_->run(true);
    }
}

void MenuItem::mouseMoveEvent(const Point &pos)
{
    if (!(this->childMenu_ && this->childMenu_->visible_))
        return Block::mouseMoveEvent(pos);

    Rect rect = this->childMenu_->rect();
    rect.height() = this->childMenu_->getHeight();

    if (pos.inside(this->rect()) || pos.inside(rect))
        return;

    // 如果子菜单的子菜单中有打开的菜单，则不隐藏
    for (auto item : this->childMenu_->items_)
    {
        if (typeid(*item) != typeid(MenuItem))
            continue;

        auto menuItem = dynamic_cast<MenuItem *>(item);
        if (!menuItem->childMenu_)
            continue;

        if (menuItem->childMenu_->isVisible())
            return;
    }
    this->childMenu_->hide();
}

MenuItem::MenuItem(const Rect &rect, MenuBox *parent)
    : Block(rect, parent)
{
    using namespace std::chrono_literals;
    this->label_ = new Label(rect, this);
    this->label_->setAlignment(Label::Left | Label::Middle);
    this->label_->setTextColor(Color::Black);
    this->label_->setText(L"Menu Item");
    this->label_->setPadding(5, 5, 5, 5);

    this->clickColorAnim_ = new Animation<Color>{Color::color_lerp};
    this->clickColorAnim_->set(
        this->hoverColor_,
        this->clickColor_,
        100ms);
    this->hoverColorAnim_ = new Animation<Color>{Color::color_lerp};
    this->hoverColorAnim_->set(
        this->defaultColor_,
        this->hoverColor_,
        100ms);

    this->onEnter.connect(
        [this]()
        {
            this->hovered_ = true;
            if (this->childMenu_)
            {
                this->childMenu_->show(this->rect().getTopRight());
            }
            this->hoverColorAnim_->reset();
            this->hoverColorAnim_->run();
        });
    this->onLeave.connect(
        [this]()
        {
            this->hovered_ = false;
            this->hoverColorAnim_->run(true);
        });
    if (parent)
        parent->items_.push_back(this);
}

MenuItem::~MenuItem()
{
    delete this->label_;
    delete this->clickColorAnim_;
    delete this->hoverColorAnim_;
}

void MenuItem::setText(const std::wstring &text)
{
    this->label_->setText(text);
}

const std::wstring &MenuItem::getText() const
{
    return this->label_->getText();
}

void MenuItem::setTextColor(const Color &color)
{
    this->label_->setTextColor(color);
}

void MenuItem::setHoverColor(const Color &color)
{
    hoverColor_ = color;
}

void MenuItem::setClickColor(const Color &color)
{
    clickColor_ = color;
}

void MenuItem::setDefaultColor(const Color &color)
{
    defaultColor_ = color;
}

void MenuItem::addChildMenu(MenuBox *menu)
{
    this->childMenu_ = menu;
}

void MenuBox::paintEvent(const PaintEvent &event)
{
    if (!this->visible_)
        return;
    return Block::paintEvent(event);
}

void MenuBox::mousePressEvent(const Point &pos, MouseButton button)
{
    if (!this->visible_)
        return;
    Rect rect = this->rect();
    rect.height() = this->getHeight();
    if (button == MouseButton::Left &&
        !rect.contains(pos))
    {
        auto result = std::async(
            std::launch::async,
            [this]()
            {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(20ms);
                if (typeid(*this->parent()) == typeid(MenuItem))
                    return;
                this->hide();
            });
    }
    return Block::mousePressEvent(pos, button);
}

void MenuBox::mouseReleaseEvent(const Point &pos, MouseButton button)
{
    if (!this->visible_)
        return;
    return Block::mouseReleaseEvent(pos, button);
}

void MenuBox::mouseMoveEvent(const Point &pos)
{
    if (!this->visible_)
        return;
    return Block::mouseMoveEvent(pos);
}

MenuBox::MenuBox(const Rect &rect, Block *parent)
    : Block(rect, parent) {}

void MenuBox::addItem(MenuItem *item)
{
    if (std::find(this->items_.begin(),
                  this->items_.end(),
                  (Block *)item) != this->items_.end())
        return;
    item->rect().x() = 0;
    item->rect().y() = this->getHeight();
    item->rect().width() = this->rect().width();
    this->items_.push_back(item);
}

void MenuBox::removeItem(int itemIndex)
{
    for (int i = itemIndex; i < this->items_.size(); i++)
    {
        this->items_[i]->rect().y() -= this->items_[itemIndex]->rect().height();
    }
    this->items_.erase(this->items_.begin() + itemIndex);
}

void MenuBox::addDivider(Divider *divider)
{
    if (std::find(this->items_.begin(),
                  this->items_.end(),
                  (Block *)divider) != this->items_.end())
        return;
    divider->rect().x() = 0;
    divider->rect().y() = this->getHeight();
    divider->rect().width() = this->rect().width();
    this->items_.push_back(divider);
}

void MenuBox::clearItems()
{
    this->items_.clear();
}

void MenuBox::show(const Point &pos)
{
    int height = 0;
    this->rect().x() = pos.x();
    this->rect().y() = pos.y();
    for (auto item : this->items_)
    {
        item->rect().x() = this->rect().x();
        item->rect().y() = this->rect().y() + height;
        height += item->rect().height();
        if (typeid(*item) == typeid(MenuItem))
        {
            auto menuItem = dynamic_cast<MenuItem *>(item);
            menuItem->label_->rect() = item->rect();
            menuItem->hovered_ = false;
            menuItem->clicked_ = false;
            menuItem->clickColorAnim_->reset();
            menuItem->hoverColorAnim_->reset();
        }
    }
    this->rect().height() = height;
    this->visible_ = true;
    this->shown.emit();
}

void MenuBox::hide()
{
    this->visible_ = false;
    for (auto item : this->items_)
    {
        if (typeid(*item) == typeid(MenuItem))
        {
            auto menuItem = dynamic_cast<MenuItem *>(item);
            menuItem->clicked_ = false;
            menuItem->hovered_ = false;
            menuItem->clickColorAnim_->reset();
            menuItem->hoverColorAnim_->reset();
        }
    }
    this->hidden.emit();
}

int MenuBox::getItemCount() const
{
    return this->items_.size();
}

int MenuBox::getHeight() const
{
    int height = 0;
    for (auto item : this->items_)
    {
        if (item)
            height += (item->rect().height());
    }
    return height;
}

bool MenuBox::isVisible() const
{
    return this->visible_;
}
