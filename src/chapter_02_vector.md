# 动态数组Vector

**预览**

---

- 基本介绍
  - 定长数据
  - 变长数组
- Vector核心实现
  - 类型定义和数据初始化 - 自定义分配器支持
  - BigFive - 行为控制
  - 常用函数和数据访问
  - 数据增删和扩容机制 - resize
  - 迭代器支持 - 范围for
  - 功能扩展 - 向量加减法
- 总结

---

Vector是一个动态大小的数组, 元素存储在一个动态分配的连续空间。在使用中, 可以向Vector添加元素或删除数据结构中已有的元素, 内部会自动的根据数据量的大小进行扩大或缩小容量

**手动管理**

```cpp
int main() {
    int *intArr = (int *)malloc(sizeof(int) * 2);
    intArr[0] = 1; intArr[1] = 2; // init

    // do something

    int *oldIntArr = intArr;
    intArr = (int *)malloc(sizeof(int) * 4);

    intArr[0] = oldIntArr[0]; intArr[1] = oldIntArr[1]; // copy
    free(oldIntArr);

    intArr[2] = 3;
    intArr[3] = 4;

    for (int i = 0; i < 4; i++) {
        std::cout << intArr[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << intArr[i] << " ";
    }

    free(intArr);

    return 0;
};

```

**自动管理**

```cpp
int main() {
    d2ds::Vector<int> intArr = { 1, 2 };

    intArr.push_back(3);
    intArr.push_back(4);

    for (int i = 0; i < 4; i++) {
        std::cout << intArr[i] << " ";
    }
    std::cout << std::endl;

    intArr.pop_back();
    intArr.pop_back();

    for (int i = 0; i < intArr.size() /* 2 */; i++) {
        std::cout << intArr[i] << " ";
    }

    return 0;
};
```

**输出结果**

```cpp
1 2 3 4
1 2
```

上面使用`Vector`创建了一个`intArr`数组, 并在使用中通过`push_back`和`pop_back`改变了数组的长度, 而关于存储数据的内存的扩大和缩小全由`Vector`内部完成, 对使用者是"透明"的, 从而降低了开发者手动去管理内存分配的负担

## Vector核心实现

### 类型定义和数据初始化

**统一分配器接口**

使用一个分配器类型作为作用域标识, 类型中包含两个静态成员函数用于内存的分配和释放

```cpp
struct Allocator {
    static void * allocate(int bytes);
    static void deallocate(void *addr, int bytes);
};
```

其中`allocate`用于分配内存, 它的参数为请求的内存字节数; `deallocate`用于内存的释放, addr为内存块地址, bytes为内存块的大小

**类型定义**

第一个模板参数用于接收数据类型, 第二个参数用于接收一个满足上面标准的分配器类型。为了方便使用, 使用`DefaultAllocator`作为分配器模板参数的默认类型, 这样开发者在不明确指定分配器的时候就会使用默认的分配器进行内存分配

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {

};
```

> 注: `DefaultAllocator`是一个已经定义在`d2ds`命名空间的分配器。文件: common/common.hpp

**数据初始化**

```cpp
d2ds::Vector<int> vec1;
d2ds::Vector<int> vec2(10);
d2ds::Vector<int> vec3 = { 1, 2, 3 };
```

定义数据成员, 并实现常见的默认初始化、指定长度的初始化、列表初始化器初始化

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:

    Vector() : mSize_e { 0 }, mDataPtr_e { nullptr } { }

    Vector(int size) : mSize_e { size } {
        mDataPtr_e = static_cast<T *>(Alloc::allocate(sizeof(T) * mSize_e));
        for (int i = 0; i < mSize_e; i++) {
            new (mDataPtr_e + i) T();
        }
    }

    Vector(std::initializer_list<T> list) {
        mSize_e = list.end() - list.begin();
        mDataPtr_e = static_cast<T *>(Alloc::allocate(sizeof(T) * mSize_e));
        auto it = list.begin();
        T *dataPtr = mDataPtr_e;
        while (it != list.end()) {
            new (dataPtr) T(*it);
            it++; dataPtr++;
        }
    }

private:
    int mSize_e;
    T * mDataPtr_e;
};
```

定义一个`mSize_e`来标识元素数量, 使用`Alloc`进行内存分配来存储数据, 并由`mDataPtr_e`来管理。
同时配合使用**定位new**(placenment new)来完成数据的构造。这里把元素对象的创建划分成了两步: 第一步, 分配对应的内存; 第二步, 基于获得的内存进行构造对象

> 注: C++中使用`new Obj()`创建对象, 可以看作是`ptr = malloc(sizeof(Obj)); new (ptr) Obj();`这两步的组合。详情见[深入理解new/delete]()章节


### BigFive - 行为控制

**析构行为**

由于使用了内存分配和对象构造分离的模式, 所以在析构函数中需要对数据结构中的元素要先析构, 最后再释放内存。即需要满足如下构造/析构链, 让对象的创建和释放步骤对称:

- 分配对象内存A
- 基于内存A构造对象B
- 析构对象B
- 释放B对应的内存A

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    ~Vector() {
        if (mSize_e) {
            for (int i = 0; i < mSize_e; i++) {
                (mDataPtr_e + i)->~T();
            }
            Alloc::deallocate(mDataPtr_e, mSize_e * sizeof(T));
        }
    }
}
```

**拷贝语义**

在拷贝构造函数中, 使用`new (addr) T(const T &)`把**拷贝构造语义**传递给数据结构中存储的元素

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    Vector(const Vector &dsObj) : mSize_e { dsObj.mSize_e } {
        mDataPtr_e = (T *) Alloc::allocate(sizeof(T) * mSize_e);
        for (int i = 0; i < mSize_e; i++) {
            new (mDataPtr_e + i) T(dsObj.mDataPtr_e[i]);
        }
    }
}
```

在拷贝赋值函数中, 先调用析构函数进行数据清理, 同时也使用`operator=`进行语义传递

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    Vector & operator=(const Vector &dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        this->~Vector();
        mSize_e = dsObj.mSize_e;
        mDataPtr_e = static_cast<T *>(Alloc::allocate(sizeof(T) * mSize_e));
        for (int i = 0; i < mSize_e; i++) {
            mDataPtr_e[i] = dsObj.mDataPtr_e[i];
        }
        return *this;
    }
}
```

**移动语义**

在移动构造函数中, 只需要把要目标对象的资源移动到该对象, 然后对被移动的对象做重置操作即可。对于Vector来说, 只需进行**浅拷贝**数据成员, 并对被移动的对象置空

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    Vector(Vector &&dsObj) : mSize_e { dsObj.mSize_e } {
        mDataPtr_e = dsObj.mDataPtr_e;
        // reset
        dsObj.mSize_e = 0;
        dsObj.mDataPtr_e = nullptr;
    }
}
```

在移动赋值函数中, 比移动构造多了对对象本身资源的释放操作

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    Vector & operator=(Vector &&dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        this->~Vector();
        mSize_e = dsObj.mSize_e;
        mDataPtr_e = dsObj.mDataPtr_e;
        // reset
        dsObj.mSize_e = 0;
        dsObj.mDataPtr_e = nullptr;
        return *this;
    }
}
```

### 常用函数和数据访问

**常用函数 - size / empty**

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    int size() const {
        return mSize_e;
    }

    bool empty() const {
        return mSize_e == 0;
    }
}
```

**数据访问**

```cpp
d2ds::Vector<int> intArr3 = { -1, -2, -3 };
const d2ds::Vector<int> constIntArr3 = { 1, 2, 3 };
```

Vector存在被`const`修饰的情况, 所以`operator=`也要对应实现一个`const`版本, 返回值为`const T &`

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    T & operator[](int index) {
        return mDataPtr_e[index];
    }

    const T & operator[](int index) const {
        return mDataPtr_e[index];
    }
}
```

### 数据增删 - 扩容和缓存机制

当动态数组Vector执行push操作进行添加元素时, 如果每次都需要重新分配内存这会极大的影响效率

```cpp
void push(const int &obj) {
    newDataPtr = malloc(sizeof(int) * (size + 1)); // 分配内存
    copy(newDataPtr, oldDataPtr); // 复制数据
    free(oldDataPtr); // 释放内存
    newDataPtr[size + 1] = obj; // 添加新元素
    size++; // 数量加1
}
```

通过引入内存容量的缓存或者说预分配机制, 来避免过多的内存分配释放, 可以有效的降低它的影响。所以就需要引入另外一个标识`mCapacity_e`来标识当前内存最大容量, 而`mSize_e`用来标识当前数据结构中的实际元素数量, 所以`mCapacity_e`是大于等于`mSize_e`的

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
private:
    int mSize_e, mCapacity_e;
    T * mDataPtr_e;
}
```

这里需要先说明一下, 扩容(缩容)机制通常是包含两个概念或步骤:

- 第一个是, 扩容(缩容)的条件, 也是执行实际操作的时机。通常扩容发生再数据增加操作, 缩容发生数据删除操作中
- 第二个是, 具体的扩容(缩容)规则。最简单的就是二倍扩容(缩容)

> 注: 成员变量的变动, 意味着对应的**BigFive**也需要修改

**push_back 和 扩容**

在每次扩容的时候, 可以选择基于当前容量的二倍进行扩容。例如: 当`mCapacity_e`等于4时, 做扩容时应该分配可以容纳8个元素的内存

```cpp
d2ds::Vector<int> intArr = {0, 1, 2, 3};
intArr.push_back(4);
/*
old: mCapacity_e == 4, mSize_e == 4
              +---------------+
mDataPtr_e -> | 0 | 1 | 2 | 3 |
              +---------------+
new: mCapacity_e == 8, mSize_e == 5
              +-------------------------------+
mDataPtr_e -> | 0 | 1 | 2 | 3 | 4 |   |   |   |
              +-------------------------------+
*/
```

什么时候扩容? 最直观的是增加元素, 但容量又不够的时候。执行push_back时, 当`mSize_e + 1 > mCapacity_e`时就需要扩容来获取更大的空间用于新数据/元素的存放, 既是否扩容需要在存储新元素操作之前

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    void push_back(const T &element) {
        if (mSize_e + 1 > mCapacity_e) {
            resize(mCapacity_e == 0 ? 2 : 2 * mCapacity_e);
        }
        new (mDataPtr_e + mSize_e) T(element);
        mSize_e++;
    }
}
```

**pop_back 和 缩容**

当数据量减少时, 同样需要释放过多的内存容量来避免内存浪费。这时就引入一个问题, 如果使用二倍原则, 是当数据结构中的真实数据量等于最大容量的1/2时进行重新分配吗? 考虑一下这样的场景:

```cpp
d2ds::Vector<int> intArr = { 1, 2, 3, 4 };
for (int i = 0; i < 10; i++) {
    intArr.push_back(i); // 触发扩容
    // ...
    intArr.pop_back(); // 触发缩容
}
```

当频繁小数据量的增加和减少, 就会造成Vector内部不停的扩容和缩容操作, 这种现象也称为——**抖动**。

为了近可能的避免这种情况, 在执行缩容之后也应该保留/缓存一部分未使用的内存空间, 用于后续可能的数据增加操作。即扩容或者缩容都要保证一定的空闲内存, 用于后续可能的操作。如: 下面就是1/3触发条件, 2倍(1/2)扩容机制的内存变化情况

```cpp
mCapacity_e == 8, mSize_e == 5
              +-------------------------------+
mDataPtr_e -> | 0 | 1 | 2 | 3 | 4 |   |   |   |
              +-------------------------------+

intArr.pop_back();

mCapacity_e == 8, mSize_e == 4
              +-------------------------------+
mDataPtr_e -> | 0 | 1 | 2 | 3 |   |   |   |   |
              +-------------------------------+

intArr.pop_back();

mCapacity_e == 8, mSize_e == 3
              +-------------------------------+
mDataPtr_e -> | 0 | 1 | 2 |   |   |   |   |   |
              +-------------------------------+

intArr.pop_back();

mCapacity_e == 4, mSize_e == 2
              +---------------+
mDataPtr_e -> | 0 | 1 |   |   |
              +---------------+
```

当`mSize_e <= mCapacity_e / 3`时就触发一次二倍扩容机制的执行, 把容量从8缩小一半到4, 此时实际存储的数据量`mSize_e == 2`。这里需要注意的是, 虽然`pop_back`不一定会释放Vector管理的内存, 但依然需要去调用被删除元素的析构函数去释放它额外管理的资源(如果存在)

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    void pop_back() {
        mSize_e--;
        (mDataPtr_e + mSize_e)->~T();
        if (mSize_e <= mCapacity_e / 3) {
            resize(mCapacity_e / 2);
        }
    }
}
```

**resize实现**

对于resize的实现, 需要关注的核心点:

- 新老内存的分配和释放
- 老数据的迁移

首先进行分配一块能存n个元素的内存块, 然后在对数据进行迁移, 最后释放老的内存块。在进行数据迁移的过程中, 如果使用拷贝语义则需要通过**显式调用**析构进行释放老的内存, 如果使用移动语语义则可以避免**在所管理元素对象内部的资源的频繁分配释放**。为了能呈现主要骨架但有不过于复杂, 下面只实现了`mSize_e <= n`的情况的简化版本

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
    void resize(int n) { // only mSize_e <= n
        auto newDataPtr = n == 0 ? nullptr : static_cast<T *>(Alloc::allocate(n * sizeof(T)));

        for (int i = 0; i < mSize_e; i++) {
            new (newDataPtr + i) T(mDataPtr_e[i]);
            (mDataPtr_e + i)->~T();
        }

        if (mDataPtr_e) {
            // Note:
            //  memory-size is mCapacity_e * sizeof(T) rather than mSize_e * sizeof(T)
            Alloc::deallocate(mDataPtr_e, mCapacity_e * sizeof(T));
        }

        mCapacity_e = n;
        mDataPtr_e = newDataPtr;
    }
}
```

### 迭代器支持

由于Vector用于存储数据元素的内存是连续的, 所以可以使用原生指针作为数据访问的迭代器

```cpp
const d2ds::Vector<int> constIntArr = intArr;
int sum = 0;
for (auto &val : constIntArr) {
    sum += val;
}
```

为了让被`const`修饰的Vector, 可以正常使用迭代器访问数据, 所以可以再实现一套const版本的begin和end

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    T * begin() {
        return mDataPtr_e;
    }

    T * end() {
        return mDataPtr_e + mSize_e;
    }

    const T * begin() const {
        return mDataPtr_e;
    }

    const T * end() const {
        return mDataPtr_e + mSize_e;
    }
};
```

### 功能扩展 - 向量加减法

假设有如下**OQ**、**OP**、**QP**三个向量

```cpp
^
|   * P(2, 4)
|
|       *Q(4, 1)
*-------------->
O(0, 0)
```

```cpp
d2ds::Vector<int> OQ = { 4, 1 };
d2ds::Vector<int> OP = { 2, 4 };
d2ds::Vector<int> QP = { -2, 3 };  
d2ds_assert(OQ + QP == OP);
d2ds_assert(OP - OQ == QP);
```

下面通过重载`operator+`和`operator-`来扩展下Vector再向量中的应用。这里为了直观我们直接假设向量是2维的, 在运算符重载函数中分别再实现向量的加减算法即可。怎么支持N维向量? 想必你心中已有答案


```cpp
namespace d2ds {

template <typename T>
bool operator==(const Vector<T> &v1, const Vector<T> &v2) {
    bool equal = v1.size() == v2.size();
    if (equal) {
        for (int i = 0; i < v1.size(); i++) {
            if (v1[i] != v2[i]) {
                equal = false;
                break;
            }
        }
    }
    return equal;
}

template <typename T>
Vector<T> operator+(const Vector<T> &v1, const Vector<T> &v2) {
    Vector<T> v(2);
    v[0] = v1[0] + v2[0];
    v[1] = v1[1] + v2[1];
    return std::move(v);
}

template <typename T>
Vector<T> operator-(const Vector<T> &v1, const Vector<T> &v2) {
    Vector<T> v(2);
    v[0] = v1[0] - v2[0];
    v[1] = v1[1] - v2[1];
    return std::move(v);
}

}
```

## 总结

本章节先是对比了一下, 对变长数组有需求的场景下。使用Vector自动管理内存和手动管理内存的差异和优势。然后，介绍了需要动态分配内存的数据结构如何去支持用户自定义分配的方法; 以及在内部自动管理内存的扩容机制的核心原理和对应**二倍扩容机制**的简单实现; 最后, 介绍了一个对Vector进行在向量领域的扩展应用。当然, 为了能够在呈现出动态数组Vector的核心原理下, 但又不过于复杂和拘迂细节, 本章中并没有去实现同样很常用的一些功能如: erase、back、data等。**但我相信在你学习完本章内容后的此时此刻, 你已基本具备自己去实现他们的能力**