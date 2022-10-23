# AvZScript

[AsmVsZombies](https://github.com/vector-wlc/AsmVsZombies) 的公开脚本仓库


# 使用说明
## 下载

方法1、点击本页面右上方的按钮 **Code▼** ，下载整个仓库的 ZIP 压缩包；

方法2、安装 [Sourcetree](https://sourcetreeapp.com/) 或其他 [Git](https://git-scm.com/) 管理软件，将本仓库同步到您的设备；

方法3、安装 [Tampermonkey](https://www.tampermonkey.net/) 或其他浏览器用户脚本管理扩展和 [Github 增强 - 高速下载](https://greasyfork.org/zh-CN/scripts/412245-github-%E5%A2%9E%E5%BC%BA-%E9%AB%98%E9%80%9F%E4%B8%8B%E8%BD%BD/) ，在本页面直接下载文件；

## 运行

1、后缀名为cpp的代码文件不能通过直接点击运行，请遵循 [AsmVsZombies教程](https://github.com/vector-wlc/AsmVsZombies/blob/master/tutorial/catalogue.md) 安装 AsmVsZombies 并在 Vscode 中查看并运行脚本。

2、脚本如果适用于特定的游戏模式和进度，会附带配套的的存档文件，此时您需要在运行脚本前将其替换相应的本地存档文件；

​	本地存档保存于名为 userdata 的文件夹，通常位于 C:\ProgramData\PopCap Games\PlantsVsZombies\ 或 PlantsVsZombies 的安装目录；

​	存档文件是文件名为以下格式的文件：game*[x]*_*[y]*.dat，其中 *[x]* 为该存档对应的用户编号，您可以将其修改为当前用户编号或在游戏主菜单的左上角切换用户，其中 *[y]* 为该存档对应的游戏模式，例如，game1_13.dat 保存着第 1 个用户在 Survival:Endless 模式中的游戏进度。


# 上传说明

## 文件夹结构

请按以下结构组织您的脚本文件再上传至本库：

```
仓库根目录
+--作者名
|  +--脚本名
|  |  +--*.cpp
|  |  +--*.h
|  |  +--game*_*.dat
|  |  +--*.jpg/png
|  |  +--README.md/txt
|  |  |   +--bin
```

其中：

*.cpp 为 void Script() 所在的代码文件；

*.h 为相关库文件，用于实现脚本所需的接口；

game\*_\*.dat 为存档文件，用于提供相应的游戏进度；

*.jpg/png 为说明图片，用于展示脚本效果或存档情况；

README.md/txt 为说明文档，其内容会被展示于仓库页面，您可以在此说明脚本适用的 AsmVsZombies 版本和运行效果；

bin 为便携版脚本，用于提供点击即用的可执行程序；

如果您要上传的脚本中包含 10MB 及以上的大文件，请在 README 中添加该文件的外部链接，而非直接上传至本库。

## 开源许可声明

如果插件中包含了 AsmVsZombies 的部分代码，那么必须以 GPL 发布，其他情况下可以使用兼容 GPL 的常规开源许可，不强制使用 GPL。
