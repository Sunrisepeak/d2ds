# 单链表 - SLinkedList

**预览**

---

- 基本介绍
  - 链表 VS 数组
- SLinkedList核心实现
  - 类型及成员定义
  - 数据初始化
  - BigFive - 行为控制
  - 常用函数和数据访问
  - 数据增删
- SLinkedList迭代器实现
  - 迭代器定义
  - 数据访问与类指针行为
  - 迭代器的判等
  - 向前迭代/++操作
  - 支持范围for
  - 迭代器版 - 插入删除操作
- 总结

---

单链表是一个内存离散型的数据结构。由于存储的每一个元素都是一个独立的内存块, 所以在插入和删除元素时的复杂度是O(1)。因此, 链表常用于需要频繁进行插入/删除的场景, 来避免其他元素移动/拷贝的开销。

**数组 VS 链表**

| \ | 数组 | 链表 |
| --- | --- | --- |
| **内存** | 连续 | 离散 |
| **插入** | O(n) | O(1) |
| **删除** | O(n) | O(1) |

链表相对于数组的优势不仅仅**插入/删除**的操作非常快, 而且由于链表的内存是离散的, 所以在增加元素扩容的时候不需要像数组一样需要一个连续的存下所有的元素的大内存块, 只要能满足每个元素的内存大小即可。这样就一定程度的避免了无法使用小内存块的问题

## SLinkedList核心实现

### 类型及数据成员定义

使用两个模板参数一个作为存储的数据类型, 一个作为分配节点的内存分配器。并且定义一个SLinkedListNode模板作为存储数据的链表节点: 它的第一个成员next表示指向下一个节点, 第二个成员data为模板的第一个参数类型, 用来存储实际的数据。同时在数据结构中使用using给节点起一个Node别名方便后续使用

```cpp
template <typename T>
struct SLinkedListNode {
    SLinkedListNode *next;
    T data;
};

template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
    using Node = SLinkedListNode<T>;
private:
    int mSize_e;
    Node mHead_e;
    Node *mTailPtr_e;
};
```

链表的数据成员中, 用Node类型定义一个链表的头节点, 方便对链表的管理。同时使用一个int类型的mSize_e来记录链表的长度, 避免每次都遍历链表来求解长度。最后, 为了单链表的尾插法的实现再加一个指向最后一个元素的节点指针mTailPtr_e。

### 数据成员的初始化

**默认初始化**

```cpp
d2ds::SLinkedList<int> intList;
```

默认初始化对应的构造函数, 需要完成数据成员的初始化。这里构造函数后, 初始化列表的形式对成员进行初始化。其中头节点mHead_e中的next指针和mTailPtr_e初始化为自己/头节点 -- 循环单链表

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    SLinkedList() : mSize_e { 0 }, mHead_e { &mHead_e, T()}, mTailPtr_e { &mHead_e } { 

    }
};
```

**列表初始化**

```cpp
d2ds::SLinkedList<int> intList = { 1, 2, 3 };
```

实现链表的列表初始化形式, 需要实现对应的插入操作 - push_back

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    void push_back(const T &data) {

        auto nodePtr = static_cast<Node *>(Alloc::allocate(sizeof(Node)));

        new (&(nodePtr->data)) T(data);
        nodePtr->next = &mHead_e;

        mTailPtr_e->next = nodePtr;
        mTailPtr_e = nodePtr;

        mSize_e++;
    }
};
```

push_back的实现主要分4个步骤

- 1.使用Alloc, 分配一块节点大小的内存
- 2.使用传进来的data对节点进行初始化, 并把节点的next指针指向头节点
- 3.修改尾节点的next指向新节点, 并更新mTailPtr_e指向新的尾部节点
- 4.size增加1

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    SLinkedList(std::initializer_list<T> list) : SLinkedList() {
        for (auto it = list.begin(); it != list.end(); it++) {
            push_back(*it);
        }
    }
};
```

有了push_back实现后, 只需要遍历list中的元素并使用push_back到最后即可


### BigFive - 行为控制

**析构实现**

析构函数主要是释放所有数据里的资源, 以及每个节点对应的内存块。每次都删除第一个节点, 直到链表为空`mHead_e.next == &mHead_e`

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    ~SLinkedList() {
        while (mHead_e.next != &mHead_e) {
            Node *nodePtr = mHead_e.next;
            mHead_e.next = nodePtr->next;
            nodePtr->data.~T();
            Alloc::deallocate(nodePtr, sizeof(Node));
        }
        mSize_e = 0;
        mTailPtr_e = &mHead_e;
    }
};
```

**拷贝语义**

由于拷贝语义主要是资源的复制。拷贝构造的实现主要就是使用for遍历目标对象, 并使用push_back一个一个添加数据

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    SLinkedList(const SLinkedList &dsObj) : SLinkedList() {
        for (Node *nodePtr = dsObj.mHead_e.next; nodePtr != &(dsObj.mHead_e);) {
            push_back(nodePtr->data);
            nodePtr = nodePtr->next;
        }
    }

    SLinkedList & operator=(const SLinkedList &dsObj) {
        if (this != &dsObj) {
            this->~SLinkedList();
            for (Node *nodePtr = dsObj.mHead_e.next; nodePtr != &(dsObj.mHead_e);) {
                push_back(nodePtr->data);
                nodePtr = nodePtr->next;
            }
        }
        return *this;
    }
};
```

拷贝赋值的主要实现思路和拷贝构造是一样的, 只需要额外做自赋值检查以及资源的提前释放即可

**移动语义**

移动语义的实现的核心是转移链表的管理权, 而链表的管理的核心是:

- mHead_e.next : 第一个节点的地址
- mTailPtr_e : 最后一个节点的地址
- mSize_e : 节点数量

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    SLinkedList(SLinkedList &&dsObj) : SLinkedList() {
        mHead_e.next = dsObj.mHead_e.next;
        mTailPtr_e = dsObj.mTailPtr_e;
        mSize_e = dsObj.mSize_e;
        mTailPtr_e->next = &mHead_e; // Note: update tail node

        // reset
        dsObj.mHead_e.next = &(dsObj.mHead_e);
        dsObj.mTailPtr_e = &(dsObj.mHead_e);
        dsObj.mSize_e = 0;
    }

    SLinkedList & operator=(SLinkedList &&dsObj) {
        if (this != &dsObj) {
            this->~SLinkedList();
            mHead_e.next = dsObj.mHead_e.next;
            mTailPtr_e = dsObj.mTailPtr_e;
            mSize_e = dsObj.mSize_e;
            mTailPtr_e->next = &mHead_e;

            // reset
            dsObj.mHead_e.next = &(dsObj.mHead_e);
            dsObj.mTailPtr_e = &(dsObj.mHead_e);
            dsObj.mSize_e = 0;
        }
        return *this;
    }
};
```

不需要额外的内存分配和释放, 直接转移链表节点的地址。然后在把目标dsObj中的数据重置。这里有一个要注意的点是: **由于是循环单链表, 所以需要更新最后一个节点/尾节点的next指向新的头节点**

### 常用函数

**size/empty**

size的实现可以直接返回mSize_e的记录, 避免重新遍历链表进行计算。而empty直接判断头节点的next是不是指向自己即可

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    int size() const {
        return mSize_e;
    }

    bool empty() const {
        return mHead_e.next == &mHead_e;
    }
};
```

**front/back**

访问第一个元素和最后一个元素可以直接通过头节点的next指针和尾指针来直接访问, 时间复杂度为O(1)

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    T & front() {
        return mHead_e.next->data;
    }

    T & back() {
        return mTailPtr_e->data;
    }
};
```

**数据访问**

```cpp
d2ds::SLinkedList<int> intList = { 0, 1, 2, 3, 4, 5 };
for (int i = 0; i < intList.size(); i++) {
    d2ds_assert_eq(intList[i], i);
}
```

由于链表内存是离散的, 所以不支持随机访问。所以通过索引的方式访问元素的算法复杂度为O(n)。即每次都是通过遍历链表来找到对应位置的数据再返回(**链表数据结构一般不提供直接的索引访问方式**)。这里我们通过**模拟随机访问的方式**, 使用下标运算符来进行数据访问。

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    T & operator[](int index) {
        // d2ds_assert(index < mSize_e && mSize != 0);
        Node *nodePtr = mHead_e.next;
        for (int i = 0; i < index; i++) {
            nodePtr = nodePtr->next;
        }
        return nodePtr->data;
    }
};
```

### 数据增删

**push_back/_pop_back**

通过这两个操作, 可以实现再数据结构尾部进行增删数据。其中push_back在最开始已经实现了。而对于单链表来说, 可以使用尾部指针来优化push_back的复杂度到O(1)。 而_pop_back的实现要麻烦很多。由于删除一个节点需要找到它的前一个节点, 所以需要先遍历链表找到最后一个节点的前一个节点。然后, 再删除尾节点并把内存给释放了。步骤可以总结如下:

- 1.找到尾节点的前一个节点
- 2.从链表中删除节点
- 3.释放节点的数据和对应的内存
- 4.size减1并更新尾部节点

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    void _pop_back() {
        // assert(size() > 0);
        Node *nodePtr = &mHead_e;
        while (nodePtr->next != mTailPtr_e) {
            nodePtr = nodePtr->next;
        }
        // delete mTailPtr_e from list
        nodePtr->next = &mHead_e;
        // release
        mTailPtr_e->data.~T();
        Alloc::deallocate(mTailPtr_e, sizeof(Node));
        mSize_e--;

        mTailPtr_e = nodePtr; // update
    }
};
```

> 注: 可以重新实现mTailPtr_e, 让其指向倒数第二个节点来实现


**push_front/pop_front**

push_front的实现流程和push_back的实现类似, 只是插入节点的前置节点换成了头节点, 并且在push数据的时候要更新一下尾指针指向该节点

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    void push_front(const T &data) {

        auto nodePtr = static_cast<Node *>(Alloc::allocate(sizeof(Node)));
        new (&(nodePtr->data)) T(data);

        nodePtr->next = mHead_e.next;
        mHead_e.next = nodePtr;
        mSize_e++;

        if (mSize_e == 1) {
            mTailPtr_e = nodePtr;
        }
    }

    void pop_front() {
        Node *nodePtr = mHead_e.next;
        // delete from list
        mHead_e.next = nodePtr->next;
        // release
        nodePtr->data.~T();
        Alloc::deallocate(nodePtr, sizeof(Node));
        mSize_e--;

        if (mSize_e == 0) {
            mTailPtr_e = &mHead_e; // update
        }
    }
};
```

pop_front的实现相对于_pop_back, 减少了前置节点的查找过程。所以它实现的算法复杂度是O(1).通过头节点的next指针找到要删除的节点, 并把next更新到删除节点的下一个节点, 然后释放目标节点。同时, 这里也需要在删除到链表为空时, 重置mTailPtr_e尾部节点指针

## SLinkedList迭代器实现

迭代器是一种访问数据的设计模式 - 它把数据的访问抽象成统一的操作/行为。如:

- `*` : 取数据
- `->` : 访问成员
- `++` : 移动到下一个数据
- `--` : 返回上一个数据

### 迭代器类型定义

在迭代器中定义一个指向目标节点的指针, 用来访问数据以及迭代到下一个数据。所以它的构造函数的输入只需要目标节点的指针即可

```cpp
template <typename T>
struct SLinkedListIterator {
    using Node = SLinkedListNode<T>;
    SLinkedListIterator() : mNodePtr { nullptr } { }
    SLinkedListIterator(Node *nodePtr) : mNodePtr { nodePtr } { }
    Node *mNodePtr;
};
```

同时在SLinkedList定义一个数据结构对应的具体类型(T)的迭代器别名, 方便后面的使用

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    using Iterator = SLinkedListIterator<T>;
}
```

### 数据访问与类指针行为

```cpp
struct MyObj {
    char a;
    int b;
    float c;
};
MyObj obj {'a', 1, 1.1};

d2ds::SLinkedListNode<MyObj> node;
node.data = obj;

d2ds::SLinkedList<MyObj>::Iterator iterator(&node);
d2ds_assert_eq(iterator->a, obj.a);
d2ds_assert_eq(iterator->b, obj.b);
d2ds_assert_eq(iterator->c, obj.c);

d2ds_assert_eq(*(iterator).c, 1.1f);
```

迭代器的本质是一个类, 但它使用起来就像是所管理数据类型的指针。可以通过`->`运算符访问对应的成员数据。同时也可以通过`*`元算符号访问到对象

```cpp
template <typename T>
struct SLinkedListIterator {
    T * operator->() {
        return &(mNodePtr->data);
    }

    T & operator*() {
        return mNodePtr->data;
    }
};
```

实现这种类指针的行为, 只需要重载并实现`operator*`和`operator->`

- `operator*` : 返回数据的引用
- `operator->` : 返回数据的指针

### 迭代器的判等

```cpp
d2ds::SLinkedListNode<int> node;
d2ds::SLinkedList<int>::Iterator iterator1(&node);
d2ds::SLinkedList<int>::Iterator iterator2(&node);
d2ds::SLinkedList<int>::Iterator iterator3(nullptr);

d2ds_assert(iterator1 == iterator2);
d2ds_assert(iterator2 != iterator3);
```

对于单链表的迭代器, 不用通过判断节点中的数据是否相等, 而是通过直接判断迭代器中管理的节点地址是否相等, 这样即可以判断数据有可以判断是否属于同一个链表

```cpp
template <typename T>
struct SLinkedListIterator {
    bool operator==(const SLinkedListIterator &it) const {
        return mNodePtr == it.mNodePtr;
    }

    bool operator!=(const SLinkedListIterator &it) const {
        return mNodePtr != it.mNodePtr;
    }
};
```

### 向前迭代/++操作

```cpp
d2ds_assert(++iterator1 == iterator3);
d2ds_assert(iterator2++ != iterator3);
d2ds_assert(iterator2 == iterator3);
```

单链表只有一个next指向下一个节点, 所以对应的迭代器也只能向前迭代。所以这里只需要实现迭代器的++操作

- `Self & operator++()` : 对应的是前置++
- `Self operator++(int)` : 对应的是后置++

```cpp
template <typename T>
struct SLinkedListIterator {
    SLinkedListIterator & operator++() {
        mNodePtr = mNodePtr->next;
        return *this;
    }

    SLinkedListIterator operator++(int) {
        auto old = *this;
        mNodePtr = mNodePtr->next;
        return old;
    }
};
```

其中前置++操作的实现, 只需要修改节点指针让其指向下一个节点, 然后返回自己。而由于后置++的特性(在下一条语句中才生效, 当前语句不变), 所以需要先保留一份旧数据, 然会更新mNodePtr指向下一个节点。最后返回旧数据, 这样就能实现 - **在下一条语句生效的性质**


### 支持范围for

```cpp
d2ds::SLinkedList<int> intList = { 5, 4, 3, 2, 1 };

auto it = intList.begin();

d2ds_assert_eq(*it, 5);
it++; d2ds_assert_eq(*it, 4);
it++; d2ds_assert_eq(*it, 3);
it++; d2ds_assert_eq(*it, 2);
it++; d2ds_assert_eq(*it, 1);

d2ds_assert(++it == intList.end());

int tmp = 5; 
for (auto val : intList) {
    d2ds_assert_eq(val, tmp);
    tmp--;
}
```

在有了迭代器后, 就可以通过实现数据结构的begin/end来支持范围for循环

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    Iterator begin() {
        return mHead_e.next;
    }

    Iterator end() {
        return &mHead_e;
    }
};
```

begin返回第一个节点对应的迭代器, 由于`Iterator`的构造函数接受Node类型的指针, 所以直接返回节点的指针就可以自动匹配返回值的迭代器类型。而end迭代器是指向最后节点的下一个节点 -- 头节点。用含头节点的地址的迭代器标识结束

### 迭代器版本 - 插入删除操作

```cpp
d2ds::SLinkedList<int> intList = { 5, 4, 3, 2, 1 };
auto it = intList.begin();
intList.erase_after(it);
++it; d2ds_assert_eq(*it, 3);
for (int val : intList) {
    std::cout << " " << val;
}
/*
[D2DS LOGI]: - ✅ | *it == 3 (3 == 3)
 5 3 2 1
*/
```

由于单链表的节点只有next指针的限制, 只能删除当前迭代器的下一个节点。所以只能实现erase_after/insert_after。并且他们的实现步骤和push/pop操作的流程是一样的, 不一样的是前驱节点由传入的迭代器中获取的

```cpp
template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {
public:
    void erase_after(Iterator pos) {
        // assert(pos.mNodePtr->next != &mHead_e);
        Node *nodePtr = pos.mNodePtr->next;
        pos.mNodePtr->next = nodePtr->next;

        nodePtr->data.~T();
        Alloc::deallocate(nodePtr, sizeof(Node));
        mSize_e--;

        if (pos.mNodePtr->next == &mHead_e) {
            mTailPtr_e = pos.mNodePtr->next;
        }
    }

    void insert_after(Iterator pos, const T &data) {
        auto nodePtr = static_cast<Node *>(Alloc::allocate(sizeof(Node)));
        new (&(nodePtr->data)) T(data);

        nodePtr->next = pos.mNodePtr->next;
        pos.mNodePtr->next = nodePtr;
        mSize_e++;

        if (nodePtr->next == &mHead_e) {
            mTailPtr_e = nodePtr;
        }
    }
};
```

## 总结

本章先是介绍了链表和数组的区别, 然后又从单链表的节点定义定义开始开始一步一步实现数据初始化、拷贝/移动语义、常用的函数、以及单链表一般不直接提供的功能(pop_back/operator[]), 从实现的角度来解释为什么不提的原因。最后, 又介绍了链表数据结构对应的迭代器的实现。其中关键的是对各种运算符(`*`/`->`/...)进行重载来实现类指针的行为。从单链表的实现上看, 它自身具有一定的限制在给定一个节点只能向下寻找, 这限制了迭代器的--操作的实现。并且不能直接删除当前节点(需要前驱节点)。下一章我们将开始介绍链表中最常使用的双链表的实现, 它能很好解决单链表的一些问题。