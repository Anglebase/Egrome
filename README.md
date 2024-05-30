# Egrome

Egrome 是一个原生C++库，它基于开源图形引擎 EGE(Easy Graphics Engine) 开发。它的名称取自 EGE 与 chrome ，旨在通过2D图形渲染的方式来开发图形界面应用程序。

## 核心机制

Egrome 的采用事件循环机制，它将事件分发给各个窗口，并将窗口的渲染结果显示在屏幕上。Egrome 每1/FPS秒渲染一次窗口以及捕获和处理鼠标和键盘事件。