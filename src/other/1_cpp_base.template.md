# template | 模板 : 范型编程初识

**预览**

---

- 基本介绍
- 函数模板 - max
  - 代码演示
    - dslings - 测试代码
    - dslings - 检测结果
  - max函数 - 重载版本实现
  - max函数 - 函数模板版本实现
- 类模板 - Box
  - 代码演示
    - dslings - 测试代码
    - dslings - 检测结果
  - Box类模板 - 类型定义
  - Box类模板 - 具体实现
- 总结

---

**范型编程**是一种**代码生成技术**, 它能帮助我们节省写大量重复代码的时间。例如, 在我们实现数据结构的时候, 使用**范型编程**技术可以让我们写一套代码就能应用到多种类型的效果。当然, 要想深度掌握**范型编程**技术不是一个简单的事情, 它的难度不亚于学习一门新的语言。 但是幸运的是在[**d2ds**](https://sunrisepeak.github.io/d2ds/)中我们只涉及其最基础的部分, 下面我们将来简单的介绍它们。


## 函数模板 - max

实现`d2ds::max`函数, 实现获取两个a和b变量中的最大值

**dslings - 测试代码**

```cpp
// template.0.cpp - readonly
//
// 描述:
//  实现max函数模板
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/other/cpp-base/Template.hpp中完成你的代码设计
//  - 通过所有断言检测
//

#include <dstruct.hpp>

#include "common/common.hpp"

#include "exercises/other/cpp-base/Template.hpp"

int main() {
    { // int
        int a = -1, b = 1;
        d2ds_assert_eq(d2ds::max(a, b), dstruct::max(a, b));
    }

    { // unsigned int
        unsigned int a = 4294967295, b = 1;
        d2ds_assert_eq(d2ds::max(a, b), dstruct::max(a, b));
    }

    { // double
        double a = 1.3, b = 3.1;
        d2ds_assert_eq(d2ds::max(a, b), dstruct::max(a, b));
    }

    return 0;
}
```

**dslings - 检测结果**

```bash
🌏Progress: [===>---------] 3/12

[Target: 1.template-0]

✅ Successfully ran tests/other/cpp-base/template.0.cpp!

🎉   The code is compiling!   🎉

Output:
====================
[D2DS LOGI]: - ✅ | d2ds::max(a, b) == dstruct::max(a, b) (1 == 1)
[D2DS LOGI]: - ✅ | d2ds::max(a, b) == dstruct::max(a, b) (4294967295 == 4294967295)
[D2DS LOGI]: - ✅ | d2ds::max(a, b) == dstruct::max(a, b) (3.100000 == 3.100000)
[D2DS LOGW]:    main: tests/other/cpp-base/template.0.cpp:35 - Delete the D2DS_WAIT to continue...

====================

Book: https://sunrisepeak.github.io/d2ds
```

### max函数 - 重载版本实现

通过C++的函数**重载技术(overload)**, 我们分别对`int` | `unsigned int` | `double` 类型版本的max进行实现

```c++
int max(int a, int b) {
    return a > b ? a : b;
}

unsigned int max(unsigned int a, unsigned int b) {
    return a > b ? a : b; 
}

double max(double a, double b) {
    return a > b ? a : b; 
}
```

这里通过观察**max函数**这三个类型的实现, 可以轻易感觉到它们只有参数和返回值类型不一样, 而函数体的代码都是一样的。此时的需求开发越多, 就会让开发者产生在做**重复工作**的感觉。部分想"偷懒"的程序员, 可能会借助IDE来设置代码模板来减轻工作量。幸运由于大多数程序员对这种"偷懒"的必要性达成了共识, 这促使了多数的编程语言对**范型编程|模板**做了支持, 在C++中对应的就是`template`。

### max函数 - 函数模板版本实现

通过函数模板, 可以写一套代码实现上面(重载实现)三套代码的效果

```c++
template <typename T>
T max(T a, T b) {
    return a > b ? a : b; 
}
```

| 标识 | 解释 |
| - | - |
| `template` | 模板标识 |
| `<>` | 范形参数类型列表(可以有多个参数) |
| `typename T` | `typename`为类型名修饰符, 后面跟着类型名标识`T` |

在数据结构实现中使用模板技术
- **第一个好处:** 只需要实现一套代码逻辑实现就可以支撑多种类型
- **第二个好处:** 编译器在编译期只会对使用到的类型做模板实例化, 对于没有用到的类型不会进行代码生成

如当只使用`int` 和 `double` 类型时:

```cpp
d2ds::max(1, 2);
d2ds::max(1.1, 0.8);
```

编译器通过按需进行代码生成来减少代码量, 只会实例化出如下两个版本:

```cpp
int max(int a, int b) {
    return a > b ? a : b;
}

double max(double a, double b) {
    return a > b ? a : b; 
}
```

> 注: 模板的代码生成技术在特定情况下, 也可能造成代码膨胀(code bloat)的问题

## 类模板 - Box

实现`d2ds::Box`用于存储**指定类型**(原生类型和自定义类型)的值

**dslings - 测试代码**

```cpp
// template.2.cpp - readonly
//
// 描述:
//  实现Box类模板, 来存储指定类型的值
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/other/cpp-base/Template.hpp中完成你的代码设计
//  - 通过所有断言检测
//

#include <dstruct.hpp>

#include "common/common.hpp"

#include "exercises/other/cpp-base/Template.hpp"


int main() {
    {
        d2ds::Box<int> box;
        box.set_value(2);
        d2ds_assert_eq(box.get_value(), 2);
    }

    {
        d2ds::Box<dstruct::String> box;
        box.set_value("Hello, d2ds!");
        d2ds_assert(box.get_value() == dstruct::String("Hello, d2ds!"));
    }

    D2DS_WAIT

    return 0;
}
```

**dslings - 检测结果**

```bash
🌏Progress: [=====>-------] 5/12

[Target: 1.template-2]

✅ Successfully ran tests/other/cpp-base/template.2.cpp!

🎉   The code is compiling!   🎉

Output:
====================
[D2DS LOGI]: - ✅ | box.get_value() == 2 (2 == 2)
[D2DS LOGI]: - ✅ | box.get_value() == dstruct::String("Hello, d2ds!")
[D2DS LOGW]:    main: tests/other/cpp-base/template.2.cpp:33 - Delete the D2DS_WAIT to continue...

====================

Book: https://sunrisepeak.github.io/d2ds
```

### Box类模板 - 类型定义

```cpp
d2ds::Box<int> intBox;
d2ds::Box<dstruct::String> stringBox;
```

类模板的定义和函数模板的定义是类似的, 都是在类名(函数签名)前使用`template`进行标识

```cpp
template <typename T>
class Box {

};
```

### Box类模板 - 具体实现

在类模板的作用域中, 可以直接把类型`T`当成一个正常的类型符号使用以及用它来完成对应的代码实现

```cpp
template <typename T>
class Box {
public:
    Box() : mVal_e{} { }

    T get_value() const {
        return mVal_e;
    }

    void set_value(const T &val) {
        mVal_e = val;
    }

private:
    T mVal_e;
};
```

在Box的实现中, 使用`T mVal_e;`定义了一个存储用户指定类型值的成员变量。并且在`get_value`和`set_value`成员函数中也像使用正常的类型一样使用**类型名`T`**。它是一个未确定的类型的标识符, 在编译期编译器将会根据使用者指定的类型来去实例化出对应的版本, 就像上面函数模板一样。总之, 在编写模板代码的时候我们可以把`T`当成一个**未知类型名**, 像正常大多数类型名的用法一样来使用它。

> 注:
> 
> 关于**模板**, 不同的群体有不同的称呼偏好。如: 模板XX - (模板函数 模板类) 也有 XX模板 - (函数模板 类模板), 。总体来说, 习惯性的称谓没有固定的统一形式(或者不必定要强制统一)。
> 
> 但是为了避免歧义和方便交流讨论, 在同一本书中保持一致性是有必要的, 本书基本遵从后者(代码特征后置)的习惯, 即 XX类 | XX模板 | XX函数 分别对应的是 类 | 模板 | 函数 

## 总结

本小节介绍了C++中**范型编程**中最基础和常用的两个部分 -- **函数模板**和**类模板**的定义方法。通过使用模板的编译器**代码生成**可以让我们设计的数据结构支持多种类型, 而又不用编写多份代码。如果你已经掌握了本节内容, 那就快去到数据结构实现的部分去实际使用C++的范型编程技术吧。