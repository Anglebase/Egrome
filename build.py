import os, shutil

## 编译代码

VERSION = "v1.0.0"

# 编译器和链接器所在路径，它们通常在同一目录下
# 若不指定具体路径(如下所示)，则指示为环境变量所指定的编译器和链接器(与命令行中使用的相同)
COMPILER = "g++"
LINKER = "ar"

print(VERSION)
input("按Enter键继续...")

os.system("md out")
print("正在编译代码...")
ret = os.system(
    f"cd out && {COMPILER} -c ../src/event/*.cpp ../src/core/*.cpp ../src/view/*.cpp -I ../include/event/ -I ../include/core/ -I ../include/view/ -std=c++17 -DUNICODE -D_UNICODE -O4".replace(
        "/", "\\"
    )
)
if ret != 0:
    print("编译失败！")
    exit(1)
print("编译完成！")

## 链接代码

print("正在链接代码...")
ret = os.system(f"cd out && {LINKER} -rc libegrome.a .\\*.o")
if ret != 0:
    print("链接失败！")
    exit(1)
print("链接完成！")

## 复制头文件

if not os.path.exists("release"):
    os.makedirs("release", exist_ok=True)
if os.path.exists(f"release/egrome-{VERSION}"):
    shutil.rmtree(f"release/egrome-{VERSION}")

print("正在复制头文件...")
shutil.copytree("./include", f"release/egrome-{VERSION}/include/egrome/includes")
print("复制完成！")

## 复制库文件

print("正在复制库文件...")
if os.path.exists(f"release/egrome-{VERSION}/lib"):
    shutil.rmtree(f"release/egrome-{VERSION}/lib")
os.makedirs(f"release/egrome-{VERSION}/lib", exist_ok=True)
shutil.copyfile("out/libegrome.a", f"release/egrome-{VERSION}/lib/libegrome.a")
print("复制完成！")

## 生成C++风格的头文件
print("正在生成C++风格的头文件...")
# 指定文件夹的路径
folder_path = rf".\release\egrome-{VERSION}\include\egrome"


def get_filename_without_extension(file_path):
    file_name_with_extension = os.path.basename(file_path)
    file_name, _ = os.path.splitext(file_name_with_extension)
    return file_name


def traverse_folder(folder_path):
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            file_path = os.path.join(root, file)
            print(file_path[len(folder_path) + 1 :])
            with open(
                folder_path + "\\" + get_filename_without_extension(file_path),
                "w",
                encoding="utf-8",
            ) as f:
                f.write("#pragma once\n")
                f.write(
                    f'#include "./{file_path[len(folder_path) + 1 :]}"'.replace(
                        "\\", "/"
                    )
                )


traverse_folder(folder_path)

print("生成完成！")
