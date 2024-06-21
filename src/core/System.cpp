#include "System.h"
#include <ege.h>
#include <windows.h>

#include "./Size.h"

String system::getCilpBoardText() {
    HWND hWnd = ege::getHWnd();
    ::OpenClipboard(hWnd);
    HANDLE hClipMemory = ::GetClipboardData(CF_UNICODETEXT);
    DWORD dwLength = ::GlobalSize(hClipMemory);
    LPBYTE lpClipMemory = (LPBYTE)::GlobalLock(hClipMemory);
    auto text = std::wstring((wchar_t*)lpClipMemory);
    ::GlobalUnlock(hClipMemory);
    ::CloseClipboard();
    return String(text);
}

void system::setCilpBoardText(String text_) {
    auto text = (std::wstring)text_;
    DWORD dwLength = text.size() + 1;
    HANDLE hGlobalMemory = ::GlobalAlloc(GHND, dwLength * 2 + 2);
    LPBYTE lpGlobalMemory = (LPBYTE)::GlobalLock(hGlobalMemory);
    for (int i = 0; i < dwLength; i++) {
        *lpGlobalMemory++ = (text[i] & 0xff);
        *lpGlobalMemory++ = (text[i] >> 8) & 0xff;
    }
    *lpGlobalMemory++ = (L'\0' & 0xff);
    *lpGlobalMemory = (L'\0' >> 8) & 0xff;
    ::GlobalUnlock(hGlobalMemory);
    HWND hWnd = ege::getHWnd();
    ::OpenClipboard(hWnd);
    ::EmptyClipboard();
    ::SetClipboardData(CF_UNICODETEXT, hGlobalMemory);
    ::CloseClipboard();
}

Size system::getScreenSize() {
    return Size{
        static_cast<float>(GetSystemMetrics(SM_CXSCREEN)),
        static_cast<float>(GetSystemMetrics(SM_CYSCREEN)),
    };
}
