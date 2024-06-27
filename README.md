# 动手写数据结构 | d2ds - WIP

Dive into Data Structures - 强调**动手实践**的**数据结构**学习项目，其中包含**在线书籍、公开课、练习代码**等子项目

| [项目主页](https://sunrisepeak.github.io/d2ds-courses) |
| ------------------------------------------------------------ |
| [d2ds-book](https://sunrisepeak.github.io/d2ds) - [d2ds-courses](https://sunrisepeak.github.io/d2ds-courses) - [d2ds-dslings](dslings) - [dstruct](https://github.com/Sunrisepeak/dstruct) |

---

## 目标

- **1.** 任何人都可以在网上**免费获取**
- **2.** 不仅强调原理, 更**强调动手实践**
- **3.** **自动化的代码练习系统**, 让使用者轻松**从零实现一个数据结构**
- **4.** **强调共建共享**, 让更多的人加入d2ds社区, 快速迭代和提升内容
- **5.** 提供社区成员用于**代码分享、技术交流、的论坛和群组**


## book & courses | 阅读

| d2ds | 材料 | 视频 | 参考 | 备注 |
| --- | --- | --- | --- | --- |
| Array | [chapter1](https://sunrisepeak.github.io/d2ds/chapter_01_array.html) | [video1](https://www.bilibili.com/video/BV1hD421T7sU) - [video2](https://www.bilibili.com/video/BV16t421w7c2) | [dstruct::Array](https://github.com/Sunrisepeak/dstruct/blob/main/core/ds/array/Array.hpp) | [备用地址](https://zhuanlan.zhihu.com/p/693936490) |
| Vector | [chapter2](https://sunrisepeak.github.io/d2ds/chapter_01_array.html) | [video1](https://www.bilibili.com/video/BV1K1421z7kt) - [video2](https://www.bilibili.com/video/BV1yb421B7ZG) | [dstruct::Vector](https://github.com/Sunrisepeak/dstruct/blob/main/core/ds/array/Vector.hpp) | [备用地址](https://zhuanlan.zhihu.com/p/696455403) |
| SinglyLink | [chapter3](https://sunrisepeak.github.io/d2ds/chapter_04_embeddedlist.html) | [video1](https://www.bilibili.com/video/BV1ND421V7Wn) - [video2](https://www.bilibili.com/video/BV1ir421w71C) | [dstruct::SinglyLink](https://github.com/Sunrisepeak/dstruct/blob/main/core/ds/linked-list/EmbeddedList.hpp#L15) | [备用地址](https://zhuanlan.zhihu.com/p/699299313) |
| X | [chapterX]() | [video1]() - [video2]() | [dstruct::X]() | [备用地址]() |

## d2ds-dslings | 练习

通过使用dslings自动化检测的**编译器驱动开发模式**来进行代码练习

[环境配置&使用指南](book/src/dslings.md)

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

> 更多详情见[dslings使用指南](book/src/dslings.md)

```bash
xmake dslings
```

## 社区 | 交流

### ShowYourCode-2024

> 代码分享、交流、解读

| id | 练习代码 | 视频解读 | 文章解读 | 交流 |
| --- | --- | --- | --- | --- |
| [Sunrisepeak](https://github.com/Sunrisepeak) | [d2ds-sunrisepeak](https://github.com/UnknownBugs/d2ds-sunrisepeak) |  |  | [discussion-pages](https://github.com/Sunrisepeak/d2ds/discussions/19) |

**创建讨论页**

在[d2ds论坛](https://github.com/Sunrisepeak/d2ds/discussions)创建一个你的ShowYourCode讨论/交流页主版(用于后续表格中) - 格式见[ShowYourCode-2024 | Sunrisepeak 交流讨论页](https://github.com/Sunrisepeak/d2ds/discussions/19)

**向本仓库发起PR**

填写自己的相关链接到上述表格中, 并向本仓库发起PR

**表格介绍**

- **练习代码:** 包含自己练习代码实现的d2ds的fork仓库
- **视频解读:** 对自己的代码实现的解读、做练习的过程等其他d2ds相关的代码分析
- **文章解读:** 相关的代码分析的文章(如上视频解读)

> 注:
> 
> - 关于链接: 视频/文章解读, 最好是视频合集/专栏的链接, 或者是一个目录页链接
> - 费曼学习法: 学习练习之后, 尝试把自己学到的内容进行分享给他人, 在尽力让其他人听懂的过程中, 促使自己更加深入的理解

### 交流渠道

- **即时交流(QQ群):** 167535744
- **论坛:** [github-discussions](https://github.com/Sunrisepeak/d2ds-courses/discussions)
- **问题交流&反馈:** [github-issues](https://github.com/Sunrisepeak/d2ds-courses/issues)

## 贡献方式 | 贡献

- **参与社区交流:** 反馈问题、参与社区问题讨论
- **参与项目开发:** 修复Bug、开发&优化新功能/模块
- **参与项目的宣传和推广:** 让更多的人能参与到项目的学习和建设当中, 以至于帮助到更多同学
