import os,shutil

## 编译代码

os.system("md out")
print("正在编译代码...")
ret = os.system(
    "cd out && g++ -c ../src/class/*.cpp ../src/core/*.cpp ../src/view/*.cpp -I ../include/class/ -I ../include/core/ -I ../include/view/".replace(
        "/", "\\"
    )
)
if ret != 0:
    print("编译失败！")
    exit(1)
print("编译完成！")

## 链接代码

print("正在链接代码...")
ret = os.system("cd out && ar -rc libegrome.a .\\*.o")
if ret != 0:
    print("链接失败！")
    exit(1)
print("链接完成！")

## 复制头文件

if not os.path.exists("release"):
    os.makedirs("release", exist_ok=True)
if os.path.exists("release/egrome-v1.0"):
    shutil.rmtree("release/egrome-v1.0")

print("正在复制头文件...")
shutil.copytree("./include", "release/egrome-v1.0/include/egrome")
print("复制完成！")

## 复制库文件

print("正在复制库文件...")
if os.path.exists("release/egrome-v1.0/lib"):
    shutil.rmtree("release/egrome-v1.0/lib")
os.makedirs("release/egrome-v1.0/lib", exist_ok=True)
shutil.copyfile("out/libegrome.a", "release/egrome-v1.0/lib/libegrome.a")
print("复制完成！")

## 生成C++风格的头文件
print("正在生成C++风格的头文件...")
# 指定文件夹的路径
folder_path = r".\release\egrome-v1.0\include\egrome"


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
                f.write(f'#include "./{file_path[len(folder_path) + 1 :]}"'.replace("\\", "/"))


traverse_folder(folder_path)

print("生成完成！")