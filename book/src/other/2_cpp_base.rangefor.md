# 语法糖 | 范围for循环

**预览**

---

- 基本介绍
  - 使用普通for循环
  - 使用范围for循环
- 自定义类型如何支持这个语法糖？
- 模拟Python中range - 实现PyRange
  - 代码演示
    - Python - range
    - dslings - 测试代码
    - dslings - 检测结果
  - PyRange - 类型定义
  - PyRange - begin 和 end
  - PyRange - 迭代器的 * 和 ++ 操作
  - PyRange - 完整实现
- 总结

---

C++从C++11开始也像很多语言一样提供了范围for循环这个"语法糖"。它是用作对范围中的各个值（如容器中的所有元素）进行操作的较传统for循环更加可读的等价版本。下面以`std::vector`为例对比并演示一下它的使用:

**使用普通for循环**

通过`std::vector`的`begin`和`end`迭代器来获取数据结构(容器)中存储的数据。 其中**迭代器`it`**的行为很像指针, 可以通过*号去"解引用"获取数据, 通过`++`让迭代器指向存储的下一个数据。

```cpp
#include <vector>

int main() {
    std::vector<int> vec { 1, 2, 3, 4 };

    int val;
    for (auto it = vec.begin(); it != vec.end(); it++) {
        val = *it;
        //...
    }

    return 0;
}
```

**使用范围for循环**

通过使用范围for循环简化了对数据结构中数据的访问, 不需要开发者直接去控制和判断迭代器就可以轻松访问到所有数据。这里需要注意的是 —— 其实这个简化了的for循环的本质也是像上面一样使用了迭代器的设计模式, 只是编译器帮我们省去了关于迭代器的相关操作, 原理上可视为等价的。

```cpp
#include <vector>

int main() {
    std::vector<int> vec { 1, 2, 3, 4 };

    for (int val : vec) {
        // ...
    }

    return 0;
}
```

## 自定义类型如何支持这个语法糖？

对于库开发者, 比起使用这个范围for循环, 更让其好奇和兴奋的是 —— **如何让自己写的数据结构也能支持这么好的性质, 这样大家用起来就会更爽了(这可能就是传说中的大家好才是真的好哈哈)**。下面将讨论自定义类型如何支持这个范围for语法糖。

这里引用一下[cppreference](https://en.cppreference.com)上对它的解释

```cpp
// https://en.cppreference.com/w/cpp/language/range-for
{ // until C++17
    auto && __range = range-expression ;
    for (auto __begin = begin-expr, __end = end-expr; __begin != __end; ++__begin)
    {
        range-declaration = *__begin;
        loop-statement
    }
}
```

为了更好的观察, 我们还是以上面`std::vector`的范围for作为例子, 给出编译对这个语法套进行代码展开的**可能实现**

```cpp
{ // 没有展开的形式
    for (int val : vec) {
        // ...
    }
}
{ // 编译器代码展开的可能实现
    auto && __range = vec;
    for (auto __begin = __range.begin(), __end = __range.end(); __begin != __end; ++__begin) {
        auto && val = *__begin;
        // ...
    }
}
{ // 编译器代码展开的可能实现 -- 易读版
    auto __end = vec.end();
    for (auto it = vec.begin(); it != __end; ++it) {
        int val = *it;
        // ...
    }
}
```

从简化的`易读版`上可以看出, 和前面最开始的普通版本的for循环实现是差不多的, 并且我们可以总结出如下要素:

- 1.需要实现`begin()`
- 2.需要实现`end()`
- 3.`begin()` / `end()` 返回的类型需要具备指针的行为操作(或者至少要满足`*`和`++`操作)

下面我就以一个例子的实现来具体阐述和感受**自定类型**支持范围for的完整过程

## 模拟Python中range - 实现PyRange

range 类型表示不可变的数字序列，通常用于在 for 循环中循环指定的次数。下面我们将简单介绍一下Python中range对象在for循环中的应用, 然后在使用C++实现一个**支持范围for循环的PyRange**来近似模拟它的行为。

**Python - range**

- `range(start, stop)`
- `range(start, stop, step)`

```Python
speak@speak-pc:~/workspace/github/d2ds$ python3
Python 3.10.12 (main, Nov 20 2023, 15:14:05) [GCC 11.4.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> for i in range(0, 10):
...     print(i)
... 
0
1
2
3
4
5
6
7
8
9
>>> for i in range(0, 50,  5):
...     print(i)
... 
0
5
10
15
20
25
30
35
40
45
>>>
```

**dslings - 测试代码**

为了简单PyRange只模拟**Python - range**中在for循环中应用的有限部分。下面是PyRange在范围for循环中生成索引数据(int)的代码示例:

```cpp
// range_for.3.cpp - readonly
//
// 描述:
//  实现PyRange在范围for循环的支持, 并保证数据生成的正确性
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/other/cpp-base/RangeFor.hpp中完成你的代码设计
//  - 通过所有断言检测
//

#include <dstruct.hpp>

#include "common/common.hpp"

#include "exercises/other/cpp-base/RangeFor.hpp"

int main() {
    {
        int index = 0;
        for (int val : d2ds::PyRange(0, 10)) {
            d2ds_assert_eq(val, index);
            index++;
        }
    }

    {
        int index = 0, step = 5;
        for (auto val : d2ds::PyRange(0, 50, step)) {
            d2ds_assert_eq(val, index);
            index += step;
        }
    }

    D2DS_WAIT

    return 0;
}
```

上述代码中, 在接口的使用上为了更像Python中的range, PyRange也遵从了如下设计


| 接口 | 简介 |
| - | - |
| `PyRange(start, stop, step = 1)` | step为值变化步长默认为1.数据生成遵从左闭右开原则 |

**dslings - 检测结果**

```bash
🌏Progress: [=========>---] 9/12

[Target: 2.range_for-3]

✅ Successfully ran tests/other/cpp-base/range_for.3.cpp!

🎉   The code is compiling!   🎉

Output:
====================
[D2DS LOGI]: - ✅ | start < stop
[D2DS LOGI]: - ✅ | step > 0
[D2DS LOGI]: - ✅ | mLen_e <= 100
[D2DS LOGI]: - ✅ | val == index (0 == 0)
[D2DS LOGI]: - ✅ | val == index (1 == 1)
[D2DS LOGI]: - ✅ | val == index (2 == 2)
[D2DS LOGI]: - ✅ | val == index (3 == 3)
[D2DS LOGI]: - ✅ | val == index (4 == 4)
[D2DS LOGI]: - ✅ | val == index (5 == 5)
[D2DS LOGI]: - ✅ | val == index (6 == 6)
[D2DS LOGI]: - ✅ | val == index (7 == 7)
[D2DS LOGI]: - ✅ | val == index (8 == 8)
[D2DS LOGI]: - ✅ | val == index (9 == 9)
[D2DS LOGI]: - ✅ | start < stop
[D2DS LOGI]: - ✅ | step > 0
[D2DS LOGI]: - ✅ | mLen_e <= 100
[D2DS LOGI]: - ✅ | val == index (0 == 0)
[D2DS LOGI]: - ✅ | val == index (5 == 5)
[D2DS LOGI]: - ✅ | val == index (10 == 10)
[D2DS LOGI]: - ✅ | val == index (15 == 15)
[D2DS LOGI]: - ✅ | val == index (20 == 20)
[D2DS LOGI]: - ✅ | val == index (25 == 25)
[D2DS LOGI]: - ✅ | val == index (30 == 30)
[D2DS LOGI]: - ✅ | val == index (35 == 35)
[D2DS LOGI]: - ✅ | val == index (40 == 40)
[D2DS LOGI]: - ✅ | val == index (45 == 45)
[D2DS LOGW]:    main: tests/other/cpp-base/range_for.3.cpp:35 - Delete the D2DS_WAIT to continue...

====================

Book: https://sunrisepeak.github.io/d2ds
```

### PyRange - 类型定义

```cpp
d2ds::PyRange(0, 10);
d2ds::PyRange(0, 5, 200);
```

PyRange的构造函数为了简单, 使用了三个int作为输入参数, 并且为了支持上面两种使用模式最后一个参数step使用了默认参数为1的设置

```cpp
class PyRange {
public:
    PyRange(int start, int stop, int step = 1) {

    }
};
```

### PyRange - begin 和 end

```cpp
d2ds::PyRange range(2, 10);
auto begin = range.begin();
auto end = range.end();
```

给PyRange实现两个无参数的成员函数begin和end, 搭出基本结构

```cpp
class PyRange {
public:
    PyRange(int start, int stop, int step = 1) {

    }

public:
    void * begin() const {
        return nullptr;
    }

    void * end() const {
        return nullptr;
    }
};
```

### PyRange - 迭代器的 * 和 ++ 操作

```cpp
d2ds::PyRange range(0, 10);

auto begin = range.begin();
auto end = range.end();

d2ds_assert_eq(*begin, 0);
++begin;
d2ds_assert_eq(*begin, 1);
```

C++的范围for循环使用的迭代器, 是一种类指针行为的类型。幸运的是原生指针就符合这种迭代器的性质, 所以这里让`begin/end`返回`const int *`类型, 这就自动实现了*操作符解引用获取int类型数据和通过++自增运算符移动到下一个数据。

通过在PyRange内部设置一个数组mArr_e用来存储数据值和一个mLen_e来标识结束位置来简化实现, 虽然它看起来很不优雅。同时在构造函数中暂时也只实现step等于1的情况

```cpp
class PyRange {
public:
    PyRange(int start, int stop, int step = 1) {
        mLen_e = stop - start;
        for (int i = 0; i < mLen_e; i++) {
            mArr_e[i] = i + start;
        }
    }

public:
    const int * begin() const {
        return mArr_e;
    }

    const int * end() const {
        return mArr_e + mLen_e;
    }

private:
    int mLen_e;
    int mArr_e[100];
};

```

> 注: 本文为了简单实现PyRange的方式是不够优雅的, 相对优雅一些的实现见[设计模式 - 迭代器设计模式]()章节中的实现


### PyRange - 完整实现

这里完善了PyRange构造函数中对step的支持和增加了一些参数限制的检测

```cpp
class PyRange {
public:
    PyRange(int start, int stop, int step = 1) {

        mLen_e =  (stop - start) / step;

        d2ds_assert(start < stop);
        d2ds_assert(step > 0);
        d2ds_assert(mLen_e <= 100);

        for (int i = 0; i < mLen_e; i++) {
            mArr_e[i] = start;
            start = start + step;
        }
    }

public:
    const int * begin() const {
        return mArr_e;
    }

    const int * end() const {
        return mArr_e + mLen_e;
    }

private:
    int mLen_e;
    int mArr_e[100];
};
```

## 总结

本小节先是对比了普通for循环和范围for循环的使用, 然后通过分析编译器对**范围for循环**的代码展开结构, 来探究在自定义类型中如何实现**范围for循环**的支持, 最后通过实现一个模拟Python中常用的range对象 —— PyRange, 来进一步通过写代码的方式体验实现**范围for循环**支持的完整过程。那么, 现在快去给自己实现的数据结构添加**范围for循环**的语法糖支持吧(如果你的数据结构内存布局不是连续存储, 你可能还需要阅读[设计模式 - 迭代器设计模式]()章节中的内容)...