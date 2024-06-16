#pragma once

#include <string>
#include <vector>
#include "Block.h"
#include "Point.h"
#include "Color.h"
#include "SignalSlots.hpp"

class TextDocument;
class TextBlock;
class TextLine;

class TextChar : public Block
{
private:
    wchar_t char_;

public:
    struct StyleSheet
    {
        Color fontColor{Color::Black};
        int fontSize{12};
        std::wstring fontName{L"宋体"};
        int fontWeight{400};
        bool bold{false};
        bool italic{false};
        bool underline{false};
        bool deleted{false};
    } style;
protected:
    void paintEvent(const PaintEvent &event) override;
public:
    TextChar(const Rect &rect, TextLine *parent) noexcept;
    ~TextChar() noexcept = default;

    void setChar(wchar_t c) noexcept;
    wchar_t getChar() const noexcept;
};

class TextLine : public Block
{
    std::vector<TextChar> chars_;

public:
    TextLine(const Rect &rect, TextBlock *parent) noexcept;
    ~TextLine() noexcept = default;
};

class TextBlock : public Block
{
private:
    std::vector<TextLine> chars_;

public:
    TextBlock(TextDocument *parent) noexcept;
    ~TextBlock() noexcept = default;
};

class TextDocument : public Block
{
    std::vector<TextBlock> blocks_;

public:
    TextDocument(const Rect &rect, Block *parent) noexcept;
    ~TextDocument() noexcept = default;
};