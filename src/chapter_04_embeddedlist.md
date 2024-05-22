# 嵌入式单链表

**预览**

---

- 核心原理
  - 结构 - 链域和数据域
  - 操作 - 链表的逻辑抽象
  - 使用 - 数据存储和访问
- 设计/使用技巧
  - 通信库 - 组合式
  - Linux内核 - 嵌入式
  - V8引擎 - 继承式(C++)
- 总结

---

嵌入式链表是一种高性能且范型支持的链表。同时也是一种"底层"的数据结构。它在内存效率和性能上的优秀的表现, 使得在[Linux内核](https://github.com/torvalds/linux/blob/master/include/linux/list.h)、[浏览器的v8引擎](https://source.chromium.org/chromium/chromium/src/+/main:v8/src/heap/list.h?q=ListNode&ss=chromium%2Fchromium%2Fsrc)、[Redis数据库](https://github.com/redis/redis/blob/unstable/src/adlist.h)等许多大型的开源项目中都有使用。对于大多数的数据结构实现, 关注的核心点可以归为**内存管理**、**类型控制**、**操作**这三个方面。通常这是库作者的工作, 而使用者只需要关心数据。而在嵌入式链表的使用中**内存管理**、**类型控制**是常需要使用者来显示控制的, 这使得它的使用难度远大于普通数据结构。这也是为什么它常应用到一些追求性能的系统模块, 而应用软件中却很少见到它的身影, 下面我们将从它的最小代码实现开始一步一步介绍其设计理念和使用技巧

### 结构 - 链域和数据域

```cpp
struct ListNode {
    struct ListNode *next; // link区域
    int data; // data区域
};
```

一个链表节点可以分成**link区域**和**数据区域**。其中，数据区用于储存数据，link区域用于存储指向下一个节点的指针，把分散的节点串连成一个链表。

### 操作 - 链表的逻辑抽象

如果我们像上面一样, 把数据类型和链表进行耦合。就会发现, 每定义一个链表就**只能给特定的数据类型使用**, 很难实现通用数据结构。当然, 在C++中有很多方法来实现这种通用性。例如: 编译器代码生成技术 - 模板

```cpp
template <typename T>
struct ListNode {
    struct ListNode *next; // link区域
    T data; // data区域
};
```

但模板的本质就是需要手写两遍的代码量, 转为编译器来帮你手写了。从底层角度看**数据类型**和**链表**依然是耦合的, 并且C语言中是不支持模板的。对于链表的很多操作一定要和存储的数据类型进行绑定吗？显然，链表的操作从逻辑上是和数据类型无关的。例如下面把**数据区域**丢弃的链表代码:

```cpp
struct SinglyLink {
    struct SinglyLink *next;
};

static void insert(SinglyLink *prev, SinglyLink *target) {
    target->next = prev->next;
    prev->next = target;
}

static void remove(SinglyLink *prev, SinglyLink *target) {
    prev->next = target->next;
    target->next = target;
}
```

这是不是链表? 是。但不存数据的链表有什么意义呢? 如果这时我说——这就是**嵌入式链表**的最小原型。你会不会产生如下疑问:

- 它的使用方法?
- 它存储和管理数据的原理？

下面我们将逐一回答

### 使用 - 数据存储和访问

开头的简介里也说了, 嵌入式链表只管理数据, 内存的分配和释放是由使用者完成的。这样只要节点中包含一个统一的**SinglyLink链接区域**, 所有节点就可以被组织起来

```cpp
struct ListNodeInt {
    SinglyLink link; // link区域
    int data; // data区域
};

struct ListNodeDouble {
    SinglyLink link; // link区域
    double data; // data区域
};

int main() {
    ListNodeInt node1;
    auto node2Ptr = new ListNodeInt();

    insert(&(node1.link), (SinglyLink *)node2Ptr);

    auto linkPtr = (SinglyLink *)(&node1);
    while (linkPtr != nullptr) {
        auto nodePtr = (ListNodeInt *)linkPtr;
        std::cout << nodePtr->data << std::endl;
        linkPtr = linkPtr->next;
    }
    delete node2Ptr;
}
```

嵌入式链表, 可以**忽视**一个节点中除去link以外的数据。通过操作每个节点中link对链表做增加、删除和遍历的操作。在循环遍历链表时, link下面的数据类型的处理是交给使用这显示控制的, 即通过类型转换把link类型转为它本身的节点或数据类型, 进而区访问这个节点真实携带的数据信息。而这些数据的结构、大小等细节链表操作是不关心的, 它只关注对link区域的处理

### 优点

**C语法实现通用链表**

不需要使用复杂的代码生成技术和范型编程支持, 就可以实现高效的通用数据结构

**性能更好**

对于可变数据, 不使用二次分配内存的方式。link区域和data区域是位于同一块连续内存上, Cache更友好(相对两次分配)。同时相对于std::list在链表数据迁移的时候不需要额外释放和分配内存。

**节点可位于多个链表**

一个节点可以同时位于多个链表中。如: 一个Task节点可以同时位于eventList和runList中

```cpp
struct Task {
    SinglyLink eventList;
    // ...
    SinglyLink runList;
};
```

## 设计/使用技巧

虽然上面介绍了嵌入式链表的总体设计思想——**只关心统一的链表操作**。而**数据类型**和**内存分配**的处理上会有些许不同, 下面就介绍三种经典的处理方法:

### 通信库 - 组合式

在很多消息通信的场景, 每个消息携带的数据量可能是不一样的。管理消息的链表, 可以通过组合的形式把Link域和变长数据域的内存做**物理拼接**

```cpp
template <unsigned int N>
struct Msg {
    int size;
    char data[N];

    static void init(void *msg) {
        reinterpret_cast<Msg *>(msg)->size = N;
        // fill data
    }
};

int main() {
    auto node1 = (SinglyLink *) malloc(sizeof(SinglyLink) + sizeof(Msg<1024>));
    auto node2 = (SinglyLink *) malloc(sizeof(SinglyLink) + sizeof(Msg<1024 * 3>));
    auto node3 = (SinglyLink *) malloc(sizeof(SinglyLink) + sizeof(Msg<1024 * 2>));

    Msg<1024>::init(node1 + 1);
    Msg<1024 * 3>::init(node2 + 1);
    Msg<1024 * 2>::init(node3 + 1);

    SinglyLink msg_list;

    insert(&msg_list, node1);
    insert(&msg_list, node2);
    insert(&msg_list, node3);

    //...

    free(node1);
    free(node2);
    free(node3);
    return 0;
}
```
在使用malloc分配内存时, 申请的大小是`sizeof(link) + sizeof(data)`, 这样在物理上数据和只有link的嵌入式链表的节点在一块连续的内存上。在链表视角相当于 在每个节点下面挂载了一个**隐藏**的消息数据

```bash
        +-------+    +-------+           +-------+
List:   | next  | -> | next  | -> ... -> | next  |
        +-------+    +-------+           +-------+
        +-------+    +-------+           +-------+
Data:   |payload|    |       |           |       |
        +-------+    |payload|           |payload|
                     |       |           +-------+
                     +-------+
```

这样可以使得每个链表节点的消息负载(长度)是可变的。数据的使用者解析时只需要对节点地址做1单位的偏移, 就能去解析数据的结构/格式。并由于link和data是通过一次申请来分配的, 所以在解析失败或节点释放的时候可以直接通过`free(nodePtr)`去释放内存块, 而不需要分两次释放

### Linux内核 - 嵌入式

在最开始介绍设计思想的时候使用的就是者中把`SinglyLink`"嵌入"到一个数据结构中的形式

```cpp
struct MemBlock {
    SinglyLink link;
    int size;
};
```

由于link是被嵌入数据结构的第一个数据成员(无继承), 所以从link到MemBlock和MemBlock到link的转换都比较方便, 可以直接通过强制类型转换来实现

```cpp
auto mbPtr = new MemBlock;
auto linkPtr = static_cast<SinglyLink *>(mbPtr);
//...
auto mbPtr_tmp = static_cast<SinglyLink *>(linkPtr);
```

但是在内核源码中常可以见到如下的**嵌入方式**

```cpp
struct Demo {
    char member1;
    int member2
    SinglyLink link;
    double member3;
};
```
link成员并不是结构的第一个成员, 这个时候怎么做地址和类型的相互转换呢?

**成员偏移量计算**

```cpp
#define offset_of(Type, member) ((size_t) & ((Type *)0)->member)

int main() {
    auto offset = offset_of(Demo, link);
    /*
    demoPtr = (Demo *)0;
    linkPtr = &(demoPtr->link);
    offset = (size_t) linkPtr - 0;
    */
    return 0;
}
```

这里通过把0转为一个Demo指针类型, 在取这个对象中link的地址。由于对象的基地址是0, 那么Demo中link成员的地址就是该成员相对Demo对象首地址的偏移量。由于中间设计到对空指针的操作, 虽然没有访问数据。但有些编译器上可能不生效或产生未知行为, 我们可以按照这个思路把0换成一个有效地址即可

```cpp
#define offset_of(Type, member) \
[]() { Type t; return ((size_t) & (&t)->member - (size_t)&t); } ()

int main() {
    auto offset = offset_of(Demo, link);
    /*
    auto offset_of_func = []() {
        Demo t;
        Demo ptr = &t;
        baseAddr = (size_t)ptr;
        memberAddr = (size_t) & (ptr->link);
        return memberAddr - baseAddr;
    };
    offset = offset_of_func();
    */
    return 0;
}
```

以上只是为了解释**成员偏移量计算**的原理和可行性, 实际上编译器内部已经帮我们实现了这样的"函数", 我们直接使用就可以了

```cpp
#include <cstddef>
size_t offset = offsetof(Demo, link);
```

**通用类型转换操作**

```cpp
#define to_link(nodePtr) (&((nodePtr)->link))
#define to_node(linkPtr, NodeType, member) \
    (NodeType *)( (size_t)linkPtr - offset_of(NodeType, member) )
```

通过node指针转向link指针可以直接通过取成员地址实现, 而通过link指针**还原为原来的node指针**则需要上面介绍的**成员偏移量计算**工具的辅助。即: link指针 - link成员偏移量 -> 原数据结构地址

```cpp
int main() {
    Demo nodeList;
    Demo node1, node2, node3

    insert(to_link(&nodeList), to_link(&node1));
    insert(to_link(&nodeList), to_link(&node2));
    insert(to_link(&nodeList), to_link(&node3));

    // ...

    SinglyLink *p = nodeList.link.next;
    while (p != to_link(&nodeList)) {
        Demo *demo = to_node(p, Demo, link);
        std::cout << demo->member1 << std::endl;
        p = p->next;
    }
    return 0;
}
```

### V8引擎 - 继承式(C++)

继承的好处是, 子类指针可以向上转型, 自动完成从实际数据结构到link的转换。同时在link中通过模板来携带类型信息(并未有额外定义)。通过直接继承SinglyLink<Demo>(编译期多态)来使用链表功能

```cpp
template <typename T>
struct SinglyLink {
    struct T *next;
};

struct Demo : public SinglyLink<Demo> {
    int a;
    double b;
};
```

这里的SinglyLink<Demo>里只使用了Demo类型的指针, 并不会引起循环定义问题。

```cpp
int main() {

    SinglyLink<Demo> demoList;
    Demo d1, d2, d3

    insert(&demoList, &d1);
    insert(&demoList, &d2);
    insert(&demoList, &d3);

    for (auto it = demoList.next; it != nullptr; it = it->next) {
        std::cout << it->a << std::endl;
    }

    return 0;
}
```

这样实现的链表, 在节点遍历和数据访问上实现了一定的统一, 避免了使用to_link和to_node等类型转换操作


## 总结

本章节介绍了嵌入式(侵入式)链表的核心原理, 及常见的几种实现/使用方式。虽然嵌入式链表在性能和控制力上有一些优势, 但其使用上的复杂度对开发人员确是一种"负担"。所以, 它常出现在追求性能的系统编程场景, 而对于应用软件的开发, 往往封装度完整的链表(如:std::list)会更加适合。总的来说, 数据结构的选择是一个`trade-off`权衡的结果