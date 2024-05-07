# 定长数组Array

**预览**

---

- 基本介绍
  - 原生数组
  - Array数组
- Array核心实现
  - 类型定义 - 固定类型模板参数
  - 数据初始化 - 列表初始化器的使用
  - BigFive - 行为控制
  - 数据访问 - 下标访问运算符重载
  - 常用函数实现 - size/back
  - 迭代器支持 - 范围for
  - 功能扩展 - 负下标访问支持 
- 总结

---

Array是一个对原生数组轻量级封装的容器, 在性能于原生数组几乎相等的情况下, 携带了大小信息提供了类型安全可以避免许多由于数组边界问题导致的错误。同时Array也相对提供了更丰富的接口, 并且提供了接口标准化可能性, 方便使用数据结构的通用算法。

**原生数组**

```cpp
void arr_init(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = -1;
    }
}

int main() {
    int arr[10];
    arr_init(arr, 10);
    return 0;
}
```

**Array数组**

```cpp
void arr_init(const Array<int, 10> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = -1;
    }
}

template <typename IntArrayType>
void process(const IntArrayType &arr) {
    for (int &val : arr) {
        val *= 2;
    }
}

int main() {
    Array<int, 10> arr;
    arr_init(arr, 10);
    return 0;
}
```

从上面两个简单的例子, 在多数情况下**原生数组**的数据长度信息是需要开发人员额外记忆的, 这可能会引发一些潜在风险, 而对于**Array容器**的对象本身就会携带长度信息, 并且这个携带信息的代价不需要而外的存储空间。此外, 也有利用像`process`这种"通用型算法"的设计。换句话说, Array也能使用更多的通用数据结构算法。

> 注: Array使用栈区内存, Vector使用的是"动态分配"内存, 对于固定大小的数组使用Array要比Vector在性能上更有优势

## Array核心实现

### 类型定义 - 固定类型模板参数

在Array的模板参数中的第二个参数上使用N来标识数组长度信息, 需要注意的是这里的N和类型参数T时有差异的, 它是一个`unsigned int`类型的**非类型模板参数**, 可以简单视为固定类型(指定类型)的信息标识, 在模板参数中就指定类型。

```cpp
template <typename T, unsigned int N>
class Array {

};
```

### 数据初始化 - 列表初始化器的使用

数组的列表初始化, 在编程中非常常用和方便对数据做初始化的方式, 如下:

```cpp
d2ds::Array<int, 5> intArr { 5, 4, 3, 2 /*, 1*/ };
```

对于自定义类型的Array模板, 要想支持这个特性可以使用`initializer_list`来获取列表中的数据, 并且使用迭代器进行数据的访问, 所以在Array中实现一个支持`initializer_list`的构造器即可

```cpp
template <typename T, unsigned int N>
class Array {
public:
    Array(std::initializer_list<T> list) {
        int i = 0;
        for (auto it = list.begin(); it != list.end() && i < N; it++) {
            mData_e[i] = *it;
            i++;
        }
    }

private:
    T mData_e[N == 0 ? 1 : N];
};
```

> 注: 这里N存在为0的情况, 所以使用三目运算`N == 0 ? 1 : N`来保证数组长度至少为1

### BigFive - 行为控制

BigFive核心指的是一个类型对象的**拷贝语义**和**移动语义**, 也常被称为**三五原则**(见[cppreference](https://en.cppreference.com/w/cpp/language/rule_of_three))。 多数情况下编译器是能自动生成这些代码的, 但作为一个库的话(特别是个数据结构容器库), 往往需要明确每个数据结构的行为, 这对数据结构中的数据复制和移动中的性能优化也是非常有帮助的。我们可以通过下面的类成员来实现其行为控制:

| 类成员 | 简述 |
|---|---|
| `~ClassName()` | 析构 |
| `ClassName(const ClassName &)` | 拷贝构造 |
| `ClassName & operator=(const ClassName &)` | 拷贝赋值 |
| `ClassName(ClassName &&)` | 移动构造 |
| `ClassName & operator=(ClassName &&)` | 移动赋值 |

**析构行为**

由于Array中也是使用原生数组来进行存储数据的, 这里使用使用默认的构造函数和析构和原生数组行为保持一致

```cpp
template <typename T, unsigned int N>
class Array {
public: // bigFive
    Array() = default;
    ~Array() = default;
//...
};
```

**拷贝语义**

主要是方便数据结构中数据复制的方便

拷贝构造

```cpp
d2ds::Array<BigFiveTest::Obj, 5> intArr1;
d2ds::Array<BigFiveTest::Obj, 5> intArr2(intArr1);
```

拷贝构造函数常用于"**一个同类型已存在的对象来初始化一个新对象**"的场景, 对于Array来说主要实现把已存在对象中的数据进行复制到新对象中即可

```cpp
template <typename T, unsigned int N>
class Array {
public: // bigFive
//...
    Array(const Array &dsObj) {
        for (int i = 0; i < N; i++) {
            mData_e[i] = dsObj.mData_e[i];
        }
    }
//...
};
```

> Note: 这里也可使用 `placement new` 来构造数据结构中的对象, 他的主要功能是把内存分配和对象构造进行分离--即在已有的内存上进行构造对象。更多关于**new/delete运算符的分析**将放到[C++基础]()章节

拷贝赋值

```cpp
d2ds::Array<BigFiveTest::Obj, 5> intArr1, intArr2;
// ...
intArr1 = intArr2;
```

通过赋值`=`运算符, 把一个Array中的数据复制到另一个数组中

```cpp
template <typename T, unsigned int N>
class Array {
public: // bigFive
//...
    Array & operator=(const Array &dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        for (int i = 0; i < N; i++) {
            mData_e[i] = dsObj.mData_e[i];
        }
        return *this;
    }
//...
};
```

**移动语义**

有些场景为了性能会使用**移动语义**, 只去改变数据的**所有权**来避免数据资源的重复制、频繁分配/释放带来的开销

移动构造

```cpp
d2ds::Array<BigFiveTest::Obj, 5> intArr1;
//...
d2ds::Array<BigFiveTest::Obj, 5> intArr2 { std::move(intArr1) };
```

这里假设intArr1后续不在使用, 如果使用**拷贝构造**, 可能就会造成`BigFiveTest::Obj`中动态分配的资源没有必要的分配和复制。例如, 对象中有一个指针并指向一块资源, 使用移动构造去触发对象只复制资源的地址, 而不需要重新分配并做数据复制。**移动构造**中不仅要把数据结构的资源进行移动, 一些情况也要把**移动语义**传给直接管理的数据

```cpp
template <typename T, unsigned int N>
class Array {
public: // bigFive
//...
    Array(Array &&dsObj) {
        for (int i = 0; i < N; i++) {
            mData_e[i] = std::move(dsObj.mData_e[i]);
        }
    }
//...
};
```

移动赋值

```cpp
d2ds::Array<BigFiveTest::Obj, 5> intArr1, intArr2;
// ...
intArr1 = std::move(intArr2);
```

移动赋值和移动构造一样

```cpp
template <typename T, unsigned int N>
class Array {
public: // bigFive
//...
    Array & operator=(Array &&dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        for (int i = 0; i < N; i++) {
            mData_e[i] = std::move(dsObj.mData_e[i]);
        }
        return *this;
    }
//...
};
```

> Note1: D2DS_SELF_ASSIGNMENT_CHECKER 宏是防止对象自我赋值情况的一个检测。例如:对象myObj赋值给自己(`myObj = myObj;`)。 该宏的实现原理(`if (this == &dsObj) return *this;`)是通过地址检查来规避这种情况

> Note2: 对于Array的移动语义是不够直观的, 在Vector实现中有更直观的使用, 且更多关于BigFive-**拷贝语义**和**移动语义**的介绍将放到**C++基础章节**

### 数据访问 - 下标运算符重载

```cpp
intArr[1] = 6;
intArr[4] = intArr[0];
```

实现类数组的下标访问的核心就是, 在对应类型中实现对下标运算符`[]`的重载

```cpp
template <typename T, unsigned int N>
class Array {
public:
//...
    T & operator[](int index) {
        return mData_e[index];
    }
//...
};
```

### 常用函数实现

```cpp
d2ds::Array<int, 5> intArr { 0, 1, 2, 3, 4 };
for (int i = 0; i < intArr.size(); i++) {
    d2ds_assert_eq(i, intArr[i]);
}
d2ds_assert_eq(4, intArr.back());
```

获取数据结构中的元素数量, 和获取最后一个元素都是常用的功能

**size**

```cpp
template <typename T, unsigned int N>
class Array {
public:
    unsigned int size() const {
        return N;
    }
//...
};
```

**back**

```cpp
template <typename T, unsigned int N>
class Array {
public:
    T back() const {
        return mData_e[N != 0 ? N - 1 : 0];
    }
//...
};
```

### 迭代器支持

对于Array的迭代器, 由于内部是使用数组来存储数据, 数据是在连续内存空间上的, 可以直接使用类型的指针作为迭代器类型来做迭代器支持和范围for的使用

```cpp
template <typename T, unsigned int N>
class Array {
public:
    T * begin() {
        return mData_e;
    }

    T * end() {
        return mData_e + N;
    }
//...
};
```

> Note: 关于范围for和迭代器相关的内容见**相关主体**部分

### 扩展功能 - 负下标访问

在里在给Array添加一个**扩展功能**, 像其他一些语言来支持负号下标访问

```cpp
template <typename T, unsigned int N>
class Array {
public:
//...
    T & operator[](int index) {
        // add start
        if (index < 0)
            index = N + index;
        // add end
        d2ds_assert(index >= 0 && index < N);
        return mData_e[index];
    }
//...
};
```

## 总结

本章节介绍了固定长度的数据结构Array实现, 它既具备了原生数组的性能又具备了现代数据结构容器的安全性和扩展性。同时也介绍了很多来支持Array模板实现的技术和编程技巧: 列表初始化器、类行为控制、自定义下标访问等, 下一章我们将开始介绍不定长数组(动态数组)Vector的核心功能实现