# 动手写数据结构(d2ds)

强调**动手实践**的数据结构开源[书 + 代码]

## 文档/书籍

[在线阅读](https://sunrisepeak.github.io/d2ds/)

## 代码练习

用dslings的**编译器驱动开发模式**来进行代码练习

### dslings自动检测

在本地[d2ds仓库](https://github.com/Sunrisepeak/d2ds)的根目录执行如下命令

```bash
xmake dslings
```

程序就开始自动的测试/校验, 直到一个没有完成(或错误的)练习代码, 并给出对应的练习位置以及相关的错误信息提示

> **注**
> 
> - 执行命令前, 请确保电脑已经配置了C++环境, 并安装了[xmake](https://github.com/xmake-io/xmake)构建工具
>
> - 强烈建议使用vscode作为代码练习的编辑器, 这样dslings在控制台给出的练习代码路径, 只需要用**ctrl+鼠标左键**点击就可以自动转跳到目标位置
> 

### 错误提示

```text
🌏Progress: [>-----] 0/5

[Target: 0.dslings-0]

❌ Error: Compilation/Running failed for tests/dslings.0.cpp:

 The code exist some error!

Output:
====================
[ 25%]: cache compiling.release tests/dslings.0.cpp
error: tests/dslings.0.cpp:20:11: error: ‘MaxValue’ is not a member of ‘d2ds’
   20 |     d2ds::MaxValue mVal(2);
      |           ^~~~~~~~
In file included from /usr/include/c++/11/cassert:44,
                 from ./tests/common.hpp:6,
                 from tests/dslings.0.cpp:14:
tests/dslings.0.cpp:22:12: error: ‘mVal’ was not declared in this scope
   22 |     d2ds_assert_eq(mVal.get(), 2);
      |            ^~~~
  > in tests/dslings.0.cpp


====================

Book: https://sunrisepeak.github.io/d2ds
```

执行命令后dslings程序会停在最近的未完成的练习, 并会"实时"检测和这个练习相关的数据结构代码的实现。
我们可以根据dslings在控制台的输出找到对应的练习代码:

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

#include <tests/common.hpp>

#include <exercises/dslings.hpp>

int main() {

    d2ds::MaxValue mVal(2);

    d2ds_assert_eq(mVal.get(), 2);

    return 0;
}
```

根据对应的练习代码中给的描述和要求完成该练习, 过程中可以结合dslings在控制台的提示来进行相关数据结构练习的代码设计。当正确完成代码后, dslings就会更新控制的输出给出对应的提示。

### 代码通过提示

```text
🌏Progress: [=>----] 1/5

[Target: 0.dslings-0]

✅ Successfully ran tests/dslings.0.cpp!

🎉   The code is compiling!   🎉

Output:
====================

====================

Book: https://sunrisepeak.github.io/d2ds

```

---

[开源课程](https://github.com/Sunrisepeak/d2ds-courses) | [DStruct开源库](https://github.com/Sunrisepeak/DStruct)