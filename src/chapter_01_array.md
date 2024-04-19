# Array数组

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
  - 负下标访问支持 
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

**析构行为**

由于Array中也是使用原生数组来进行存储数据的, 这里使用使用默认的构造函数和析构和原生数组行为保持一致

```cpp
template <typename T, unsigned int N>
class Array {
public: // bigFive
    Array() = default;
    ~Array() = default;
//....
};
```

**拷贝行为**

拷贝构造

```cpp
template <typename T, unsigned int N>
class Array {
public: // bigFive
//...
    Array(const Array &dsObj) {
        for (int i = 0; i < N; i++) {
            new (mData_e + i) T(dsObj.mData_e[i]);
        }
    }
//....
};
```

拷贝赋值

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
//....
};
```

**移动行为**

移动构造

```cpp
template <typename T, unsigned int N>
class Array {
public: // bigFive
//...
    Array(Array &&dsObj) {
        for (int i = 0; i < N; i++) {
            new (mData_e + i) T(std::move(dsObj.mData_e[i]));
        }
    }
//....
};
```

移动赋值

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
//....
};
```

> 注意: D2DS_SELF_ASSIGNMENT_CHECKER 宏是防止对象自我赋值情况的一个检测。例如:对象myObj赋值给自己(`myObj = myObj;`)。 该宏的实现原理(`if (this == &dsObj) return *this;`)是通过地址检查来规避这种情况

