# Egrome

Egrome 是一个基于开源图形引擎 EGE(Easy Graphics Engine) 和原生C++语言的图形界面应用程序框架。它的设计参考了Qt与浏览器内核，并在此基础上予以简化，使得初学者可以通过此框架开发出具有图形界面的应用程序。同时，此框架所利用的C++语言特性较为广泛，可以帮助开发者更好地理解C++编程。

## 特性

- 基于EGE，易于上手，学习成本低
- 丰富的示例程序，帮助开发者快速入门

## 快速入门

1. 下载并安装EGE
2. 下载并安装Egrome
3. 编写基于Egrome的应用程序，编译并运行

## 示例程序

- 基础示例：显示应用程序窗口

```cpp
#include <egrome/App>
#include <egrome/Block>

int main() {
    Block window{ Rect{0, 0, 800, 600} };
    App app{ &window };
    app.run();
    return 0;
}
```

## 许可证

Egrome 使用 MIT 许可证，允许个人和商业使用。你可以在遵守 MIT 许可证的前提下对 Egrome 进行修改，再发布，或者用于商业用途

## 获取 Egrome

你可以通过以下方式获取 Egrome：
+ 通过源代码获取(推荐)
    - 下载此仓库的源码
    - 在源码目录下运行 build.py 脚本
    - 结果将生成在 release 目录下
+ 通过安装包获取
    - 在Github仓库页面的'发行版'栏下下载最新版本的文件压缩包
    - 解压压缩包

## 安装 Egrome

**Egrome 依赖于 EGE，所以在安装 Egrome 之前，你需要先安装 EGE。**

Egrome 安装方式与 EGE 相同，将 include 和 lib 文件夹复制到你的编译器的 include 和 lib 目录下即可

## 使用 Egrome

Egrome 使用起来与 EGE 基本相同，仅需在编译链接参数'-lgraphics64'前额外添加'-legrome'即可，对于GCC编译器而言，命令格式如下：
```
g++ [源文件] -o [输出文件] -legrome -lgraphics64(或-lgraphics) -lgdiplus -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm
```

## 学习 Egrome

*此项目提供了API文档，你可以通过阅读文档来学习 Egrome 的使用方法。*
+ [Egrome 说明书](./docs/mainpage.md)
+ [Egrome API文档(由Doxygen自动生成)](https://anglebase.github.io/Egrome/html/index.html)

## Egrome 官方示例
- [仿QQ登录界面(QQLogin|v1.0之前，不含v1.0)](https://github.com/Anglebase/QQLogin.git)

## 开发者
- [Weiyi Anglebase (Github)](https://github.com/Anglebase)

## 其它

Egrome 版本号序列约定：
vX.Y\[.Z\[.B\[.C\]\]]
- X：主版本号，当库发生不兼容旧版的变化时递增此序号
- Y：次版本号，当有新特性或功能时递增此序号
- Z：修订号，当有bug修复或优化时递增此序号
- B：预览类别组，它是alpha、beta、rc之一
- C：预览类别号，它是预览版本号，一般在B类别下递增此序号