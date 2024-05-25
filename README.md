# 动手写数据结构 | d2ds - WIP

d2ds(Dive into Data Structures) - 强调**动手实践**的**数据结构**学习项目，其中包含**在线书籍、公开课、练习代码**等子项目

| 阅读 - 练习 - 讨论 - 贡献 |
| ------------------------------------------------------------ |
| [d2ds-book](https://sunrisepeak.github.io/d2ds) - [d2ds-courses](https://sunrisepeak.github.io/d2ds-courses) - [d2ds-dslings](dslings) - [dstruct](https://github.com/Sunrisepeak/dstruct) |

---

## book & courses | 阅读

| d2ds | 材料 | 视频 | 参考 | 备注 |
| --- | --- | --- | --- | --- |
| Array | [chapter1](http://127.0.0.1:3000/chapter_01_array.html) | video1 - video2 | Impl | |
| Vector | chapter2 | video1 - video2 | Impl | | 

## d2ds-dslings | 练习

通过使用dslings自动化检测的**编译器驱动开发模式**来进行代码练习

### 代码下载

```bash
git clone --recursive git@github.com:Sunrisepeak/d2ds.git
```

### 配置环境

**linux/macos**

> 使用bash执行tools目录下的安装脚本

```bash
bash tools/install.unix.sh
```

**windows**

> 执行tools目录下的安装脚本 或 直接双击运行

```bash
tools\install.win.bat
```

### 执行dslings进入练习

```bash
xmake dslings
```

> 注: 更多详情见[dslings使用指南](book/src/dslings.md)

## 工具 | 快捷命令

### xmake dslings

从指定练习开始检测, 支持模糊匹配

```bash
# xmake dslings 默认从第一开始检测
xmake dslings -s [target]
#xmake dslings -s vector
```

### xmake d2ds

查看版本信息

```bash
xmake d2ds info
```

查看工具使用

```bash
xmake d2ds help
```

同步(主仓库)最新代码

```bash
xmake d2ds update
```