# d2ds-dslings | 代码练习

通过使用dslings自动化检测的**编译器驱动开发模式**来进行代码练习

## 代码下载

```bash
git clone --recursive git@github.com:Sunrisepeak/d2ds.git
```

## 安装xmake

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

## dslings使用流程

### 第一步: 开启代码检测

在本地[d2ds仓库](https://github.com/Sunrisepeak/d2ds)的根目录执行如下命令

```bash
xmake dslings
```

程序开始自动的测试/校验, 直到一个没有完成(或检测不通过)的练习代码。dslings会在控制台输出提示信息。如:

- 练习进度
- 练习的代码路径信息
- 编译期错误信息提示
- 运行时错误提示

> **注**
> 
> - 执行命令前, 请确保电脑已经配置了C++环境, 并安装了[xmake](https://github.com/xmake-io/xmake)构建工具
>
> - 建议使用vscode作为代码练习的编辑器, 用**ctrl+鼠标左键**点击路径就可以自动转跳到目标位置
>
> - 由于vscode的C/C++插件会检测文件变化, 可以参考[issue-5](https://github.com/Sunrisepeak/d2ds/issues/5)来避免卡顿

### 第二步: 根据dslings提示, 找到对应的练习代码

```bash
🌏Progress: [>-----------------------------] 0/29

[Target: 0.dslings-0]

❌ Error: Compilation/Running failed for tests/dslings.0.cpp:

 The code exist some error!

Output:
====================
[ 50%]: cache compiling.release tests/dslings.0.cpp
error: tests/dslings.0.cpp:20:11: error: ‘MaxValue’ is not a member of ‘d2ds’
   20 |     d2ds::MaxValue mVal(2);
      |           ^~~~~~~~
In file included from tests/dslings.0.cpp:14:
tests/dslings.0.cpp:22:20: error: ‘mVal’ was not declared in this scope
   22 |     d2ds_assert_eq(mVal.get(), 2);
      |                    ^~~~
./common/common.hpp:28:9: note: in definition of macro ‘d2ds_assert_eq’
   28 |     if (a != b) {\
      |         ^
  > in tests/dslings.0.cpp


====================

Homepage: https://github.com/Sunrisepeak/d2ds-courses
```

执行命令后dslings程序会停在最近的未完成的练习, 并会"实时"检测和这个练习相关的数据结构代码的实现。我们可以根据dslings在控制台的输出找到对应的练习代码:

```cpp
// dslings.0.cpp - readonly
//
// 描述:
//  通过实现一个MaxVal类型(保存最大值), 来介绍dslings的"编译器驱动开发"
//  即根据编译器的错误提示来完成这个训练流程的演示Demo, 并且通常为了降低难度会把一个'数据结构'的实现分成多个检测模块.
//  如: dslings.0.cpp dslings.1.cpp dslings.2.cpp
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/dslings.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/dslings.hpp"

int main() {

    d2ds::MaxValue mVal(2);

    d2ds_assert_eq(mVal.get(), 2);

    HONLY_LOGI_P("Hello D2DS!");

    D2DS_WAIT

    return 0;
}
```

### 第三步: 阅读练习描述和要求并完成练习

根据对应的练习代码中给的描述和要求完成该练习, 过程中可以结合dslings在控制台的提示来进行相关数据结构练习的代码设计。当正确完成代码后, dslings就会更新控制的输出给出对应的提示

```bash
🌏Progress: [>-----------------------------] 0/29

[Target: 0.dslings-0]

✅ Successfully ran tests/dslings.0.cpp!

🎉   The code is compiling!   🎉

Output:
====================
[D2DS LOGI]: - ✅ | mVal.get() == 2 (2 == 2)
[D2DS LOGI]: - Hello D2DS!
[D2DS LOGW]: main: tests/dslings.0.cpp:26 - 🥳 Delete the D2DS_WAIT to continue...

====================

Homepage: https://github.com/Sunrisepeak/d2ds-courses
```

### 第四步: 注释D2DS_WAIT, 进入下一个练习

根据dslings在控制台的提示信息, 找到`tests/dslings.0.cpp:26`, 并进行注释或者删除。
dslings就会进入下一个练习并进行检测

```bash
int main() {

    d2ds::MaxValue mVal(2);

    d2ds_assert_eq(mVal.get(), 2);

    HONLY_LOGI_P("Hello D2DS!");

    //D2DS_WAIT

    return 0;
}
```

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