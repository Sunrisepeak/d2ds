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
  - 功能扩展1 - 自定义扩容规则
  - 功能扩展2 - 向量加法
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

**push_back 和 扩容**

**pop_back 和 缩容**

**resize实现**

