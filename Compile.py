import json, os, re, time, sys

"""
本脚本提供以json配置GCC项目编译的方式

所提供配置项：
    compiler    ::str   ：指定编译器
    src         ::list  ：指定源文件
    target      ::str   ：指定目标文件
    include     ::list  ：指定include目录
    linkdir     ::list  ：指定链接目录
    link        ::list  ：指定链接选项
    std         ::str   ：指定C++标准
    option      ::list  ：其它编译选项
    args        ::list  ：目标程序的命令行参数
    define      ::list  ：指定预定义宏
    start       ::bool  ：是否在编译完成后立即启动测试任务(True则启动)
    compile     ::bool  ：是否执行此任务的编译(True则执行)
**所有的配置参数都会被传递给编译器**

json配置格式：
{
    [task-name1]:{
        [option]:[value],
        [option]:[value],
       ...
    },
    [task-name2]:{
        [option]:[value],
        [option]:[value],
       ...
    },
    ...
}
"""


def Red(s):
    return "\033[91m" + s + "\033[0m"


def Green(s):
    return "\033[38;2;0;255;0m" + s + "\033[0m"


def Blue(s):
    return "\033[94m" + s + "\033[0m"


def Yello(s):
    return "\033[93m" + s + "\033[0m"


def Cyan(s):
    return "\033[38;2;0;255;255m" + s + "\033[0m"


print(Green("正在解析配置文件..."))

conftext: str = open(sys.argv[1], mode="r", encoding="utf-8").read()
conf: dict = json.loads(re.sub(r"\/\*[\s\S]*?\*\/|\/\/.*", "", conftext))

task: list = []
exls: list = []


def complie(conf: dict, name: str):
    if conf.get("compile", True):
        return

    commandline = ""
    # 获取所指定的编译器
    compiler: str = conf.get("compiler", "")
    if compiler:
        commandline += f"{compiler}"
    else:
        print(Red(f"{name}: 未指定编译器[ compiler:str ]"))
        exit(0)

    # 指定源文件列表
    srcfiles: list = conf.get("src", [])
    if srcfiles:
        commandline += f' {" ".join(srcfiles)}'
    else:
        print(Red(f"{name}: 未指定源文件[ src:list ]"))
        exit(0)

    # 获取输出目标
    target: str = conf.get("target", "")
    if target:
        if ".exe" != target[-4:]:
            print(Red(f"{name}: 目标名称不正确[ target:str ]"))
            exit(0)
        commandline += f" -o {target}"
    else:
        print(Red(f"{name}: 未指定输出目标[ target:str ]"))
        exit(0)

    # 指定include目录
    include_path: list = conf.get("include", [])
    if include_path:
        commandline += f' -I {" -I ".join(include_path)}'

    # 指定链接目录
    link_path: list = conf.get("linkdir", [])
    if link_path:
        commandline += f' -L {" -L ".join(link_path)}'

    # 链接目标
    link: list = conf.get("link", [])
    if link:
        commandline += f' -l{" -l".join(link)}'

    # 获取C++标准
    std: str = conf.get("std", "")
    if std:
        commandline += f" -std={std.lower()}"

    # 预定义宏
    define: list = conf.get("define", [])
    if define:
        commandline += f' -D{" -D".join(define)}'

    # 其它编译选项
    options: list = conf.get("option", [])
    if options:
        commandline += f' {" ".join(options)}'

    c = ""
    for ch in commandline:
        if ch == "/":
            c += "\\"
        else:
            c += ch
    commandline = c

    task.append(commandline)

    if conf.get("start", False):
        # 目标的命令行参数
        args: list = conf.get("args", [])
        cmd = f"{target} {' '.join(args)}".strip()

        c = ""
        for ch in cmd:
            if ch == "/":
                c += "\\"
            else:
                c += ch
        cmd = c

        exls.append(cmd)


for name in conf:
    complie(conf[name], name)

print(Yello("开始生成..."))
g_start = time.time()

# 执行编译任务
for cmdline in task:
    print(Blue(f"正在执行：{Cyan(cmdline)}"))
    start = time.time()
    res = os.system(command=cmdline)
    end = time.time()
    print(Green(f"^任务用时 {end-start}s"))
    if res:
        print(Red("生成失败!"))
        exit(0)

g_end = time.time()
print(Yello("生成已完成!"))
print(Green(f"共计用时：{g_end-g_start}s"))

# 执行测试任务
if exls:
    print(Yello("正在启动任务..."))

    for e in exls:
        print(Cyan("{:*<80}".format(e + " ")))
        start = time.time()
        res = os.system(command=e)
        end = time.time()
        print(Yello(f"\n==> return -> {res}; 用时 {end-start}s"))
