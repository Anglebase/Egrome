#pragma once

#include <set>
#include "../core/Object.h"
#include "../core/Rect.h"

class MousePressEvent;
class MouseReleaseEvent;
class MouseMoveEvent;
class MouseWheelEvent;
class KeyPressEvent;
class KeyReleaseEvent;
class InputEvent;
class PaintEvent;

class Block : public Object {
    friend class App;
private:
    Rect rect_;
    bool foreach_;

    Block* parent_;
    std::set<Block*> children_;

protected:
    virtual void paintEvent(PaintEvent& event);
    virtual void mousePressEvent(const MousePressEvent& event);
    virtual void mouseReleaseEvent(const MouseReleaseEvent& event);
    virtual void mouseMoveEvent(const MouseMoveEvent& event);
    virtual void mouseWheelEvent(const MouseWheelEvent& event);
    virtual void keyPressEvent(const KeyPressEvent& event);
    virtual void keyReleaseEvent(const KeyReleaseEvent& event);
    virtual void inputEvent(const InputEvent& event);

public:
    Block(const Rect& rect, Block* parent = nullptr);
    virtual ~Block();

    const Rect& rect() const;
    Rect& rect();

    Block* parent();
    std::set<Block*>& children();

    void setParent(Block* parent);
    void addChild(Block* child);
    void removeChild(Block* child);

    void stopForeach();
    void resetForeach();
    bool isForeach() const;
};