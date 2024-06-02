# Egrome

Egrome 是一个原生C++库，它基于开源图形引擎 EGE(Easy Graphics Engine) 开发。

## 依赖
目前 Egrome 依赖于 EGE20.08 ，需要先安装 EGE20.08 

## 项目编译
Egrome 并不依赖任何构建系统，通过运行test.py即可进行自动编译，但要确保您已安装GCC编译器和EGE库，编译结果会生成在release文件夹下

## 配置
您需要将您编译项目所生成的文件夹(include和lib)复制到GCC编译器所在目录下

## 基于Egrome的应用程序编译
通过运行
```
g++ [源文件] -o [输出文件] -legrome -lgraphics64 -lgdiplus -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm
```
即可编译

## 其它
此项目可使用 Doxygen 生成说明文档，请参考 Doxygen 安装指南。也可查阅[在线文档](https://anglebase.github.io/Egrome/html/index.html)
