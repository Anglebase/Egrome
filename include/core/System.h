#pragma once

#include "./XString.h"
class Size;

namespace Sys{
    String getCilpBoardText();
    void setCilpBoardText(String text);
    Size getScreenSize();
}