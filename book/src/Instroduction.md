# 导读

**预览**

---

- 基本介绍
- 章节结构
  - 数据结构接口使用 | 代码演示
    - dslings - 测试代码
    - dslings - 检测结果
    - 代码接口介绍
  - 数据结构接口实现 | 类型定义
  - 数据结构接口实现 | 接口实现
  - 数据结构接口实现 | 完整代码
- 代码练习dslings
  - 代码下载
  - 安装xmake
  - dslings自动检测
    - 错误提示
    - 代码通过提示
    - D2DS_WAIT - dslings等待标志
- 总结

---

动手写数据结构(d2ds)是一本强调动手实践的开源电子书, 每一章节都会介绍一个数据结构的基本用法和对应的具体实现。本书使用C++作为数据结构的开发语言, 并使用"编译器驱动开发模式"面向接口编程的形式, 来介绍常见数据结构的主体功能和实现。同时, 在[d2ds仓库](https://github.com/Sunrisepeak/d2ds)中也为每章节配有对应的练习代码和dslings检测程序, 真正让读者感受到"动手写"的感觉。下面我们就来详细的介绍一下 章节结构 和 dslings的使用。

> 注: 练习代码采用了类似rustlings的代码检测风格


## 章节结构

核心分两大部分, **数据结构接口使用 + 数据结构接口实现**。如下:

### 数据结构接口使用

**dslings - MaxValue代码示例**

```cpp
// dslings.2.cpp - readonly
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

#include <dstruct.hpp>

#include "common/common.hpp"
#include "exercises/dslings.hpp"

int main() {

    d2ds::MaxValue mVal(2);

    d2ds_assert_eq(mVal.get(), 2);

    mVal.set(-1);
    d2ds_assert_eq(mVal.get(), 2);

    mVal.set(100);
    d2ds_assert_eq(mVal.get(), 100);

// random test
    dstruct::Array<int, 10> data;
    d2ds::random_data_generator(data, 0, 200);
    d2ds::ds_print(data);

    int maxVal = 0;
    for (int i = 0; i < data.size(); i++) {
        mVal.set(data[i]);
        if (data[i] > maxVal) {
            maxVal = data[i];
        }
    }

    d2ds_assert_eq(mVal.get(), maxVal);

    D2DS_WAIT

    return 0;
}
```

**dslings - 检测结果**

```bash
🌏Progress: [==>----------] 2/12

[Target: 0.dslings-2]

✅ Successfully ran tests/dslings.2.cpp!

🎉   The code is compiling!   🎉

Output:
====================
[D2DS LOGI]: - ✅ | mVal.get() == 2 (2 == 2)
[D2DS LOGI]: - ✅ | mVal.get() == 2 (2 == 2)
[D2DS LOGI]: - ✅ | mVal.get() == 100 (100 == 100)
[D2DS LOGI]: - ✅ | mVal.get() == maxVal (191 == 191)
[D2DS LOGW]:    main: tests/dslings.2.cpp:46 - Delete the D2DS_WAIT to continue...

====================

Book: https://sunrisepeak.github.io/d2ds
```

**代码接口介绍**

MaxValue一个数据最大值检查器

MaxValue构造函数设置默认值

```cpp
    d2ds::MaxValue mVal(2);
```

get函数获取当前最大值

```cpp
    d2ds_assert_eq(mVal.get(), 2);
```

set函数设置一个值

> 如果当前最大值小于这个值则需要进行替换

```cpp
    mVal.set(-1);
    d2ds_assert_eq(mVal.get(), 2);

    mVal.set(100);
    d2ds_assert_eq(mVal.get(), 100);
```

MaxVal的应用测试 - 获取最大数组中最大值

```cpp
// random test
    dstruct::Array<int, 10> data;
    d2ds::random_data_generator(data, 0, 200);
    d2ds::ds_print(data);

    int maxVal = 0;
    for (int i = 0; i < data.size(); i++) {
        mVal.set(data[i]);
        if (data[i] > maxVal) {
            maxVal = data[i];
        }
    }

    d2ds_assert_eq(mVal.get(), maxVal);

```

### 数据结构接口实现

根据代码示例和接口描述来实现这个数据结构

#### 类型定义

```cpp
class MaxValue {
public:
    MaxValue(int val) : mMaxVal_e { val } { }

private:
    int mMaxVal_e;
};
```

#### get接口实现

```cpp
class MaxValue {
public:
    //...
    int get() {
        return mMaxVal_e;
    }

private:
    int mMaxVal_e;
};
```

#### set接口实现

```cpp
class MaxValue {
public:
    //...
    void set(int val) {
        if (val > mMaxVal_e) {
            mMaxVal_e = val;
        }
    }

private:
    int mMaxVal_e;
};
```

## 代码练习dslings

用dslings的**编译器驱动开发模式**来进行代码练习

### 代码下载

```bash
git clone --recursive git@github.com:Sunrisepeak/d2ds.git
```

### 安装xmake

```bash
sudo add-apt-repository ppa:xmake-io/xmake
sudo apt-get update
sudo apt-get install g++ gdb xmake make -y
```

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

**错误提示**

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

#include "common/common.hpp"

#include "exercises/dslings.hpp"

int main() {

    d2ds::MaxValue mVal(2);

    d2ds_assert_eq(mVal.get(), 2);

    return 0;
}
```

根据对应的练习代码中给的描述和要求完成该练习, 过程中可以结合dslings在控制台的提示来进行相关数据结构练习的代码设计。当正确完成代码后, dslings就会更新控制的输出给出对应的提示。

**代码通过提示**

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

**D2DS_WAIT - dslings等待标志**

当完整完成一个小节的练习的时候, dslings检测程序会进入等待状态, 并且打印出类似如下的提示消息

```bash
[D2DS LOGW]:    main: tests/dslings.2.cpp:46 - Delete the D2DS_WAIT to continue...
```

按照消息中给出的文件地址, 选择注释掉(或删除)程序中的`D2DS_WAIT`标志, dslings就会进入下一个练习并开启自动检测

## 总结

好的, 到这里你应该已经了解了本书的叙述逻辑和结构 - **[数据结构使用 + 数据结构实现 + 对应代码练习]**。但该项目现任处于持续构建中(WIP), 依然存在相当多的问题。如果你在这个过程中你发现了一些项目的问题或自己遇到了一些问题, 欢迎到[d2ds讨论区](https://github.com/Sunrisepeak/d2ds-courses/discussions)反馈和交流。那么下面可以开始你的**动手写数据结构**之旅了...