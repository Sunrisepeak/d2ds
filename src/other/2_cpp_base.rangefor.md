# 语法糖 | 范围for循环

C++从C++11开始也像很多语言一样提供了范围for循环这个"语法糖"。它是用作对范围中的各个值（如容器中的所有元素）进行操作的较传统for循环更加可读的等价版本。下面我以`std::vector`为例对比并演示一下它的使用:

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

下面我就以一个例子的实现来具体阐述和感受**自定类型**支持范围for的完成过程

## 仿Python中range实现 - py_range

```cpp
class py_range {
public:
    py_range(int start, int end) : py_range(start, 1, end) { }

    py_range(int start, int step, int end) {

        __mLen =  (end - start) / step;

        d2ds_assert(start < end);
        d2ds_assert(step > 0);
        d2ds_assert(__mLen <= 100);

        for (int i = 0; i < __mLen; i++) {
            __mArr[i] = start;
            start = start + step;
        }
    }

public:
    const int * begin() const {
        return __mArr;
    }

    const int * end() const {
        return __mArr + __mLen;
    }

private:
    int __mLen;
    int __mArr[100];
};
```