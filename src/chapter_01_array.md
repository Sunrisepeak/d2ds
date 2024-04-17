# Array数组

**预览**

---

- 基本介绍
  - 原生数组
  - Array数组
- Array核心实现
  - 类型定义 - 固定类型模板参数
  - 数据初始化 - 列表初始化器的使用
  - BigFive - 构造/析构/拷贝/移动
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


## Array核心实现

### 类型定义 - 固定类型模板参数

在Array的模板参数中的第二个参数上使用N来标识数组长度信息, 需要注意的是这里的N和类型参数T时有差异的, 它是一个`unsigned int`类型的**非类型模板参数**, 可以简单视为固定类型(指定类型)的信息标识, 在模板参数中就指定类型。

```cpp
template <typename T, unsigned int N>
class Array {

};
```

### 数据初始化 - 列表初始化器的使用

在Array的模板参数中的第二个参数上使用N来标识数组长度信息, 需要注意的是这里的N和类型参数T时有差异的, 它是一个`unsigned int`类型的**非类型模板参数**, 可以简单视为固定类型(指定类型)的信息标识, 在模板参数中就指定类型。

```cpp
template <typename T, unsigned int N>
class Array {

public:
    Array(std::initializer_list<T> list) {
        int i = 0;
        for (auto it = list.end(); it != list.end(); it++) {
            mData_e[i] = *it;
            i++;
        }
    }

private:
    T mData_e[N == 0 ? 1 : N];
};
```