# 嵌入式双链表 - DoublyLink

**预览**

---

- 基本介绍
  - 单链表 VS 双链表
- DoublyLink核心实现
  - 定义和初始化
  - 插入和删除操作
  - 逆序遍历
- 使用示例
  - 组合式
  - 嵌入式
  - 继承式
- 总结

---

前面介绍过了**嵌入式单链表**, 但其并不支持向前查找。本章节就将介绍链表中最常用的双链表对应的"无数据域"的 -- **嵌入式双链表**

**内存使用对比**

在双链表中, 每一个节点都比单链表多了一个指向前一个节点的指针`prev`, 所以对应的在存储相同数据量的元素N时, 内存的使用要比单链表多N x 8字节(设:指针占8字节)。但多数时候大家都原因花费这个内存的代价来换取使用的便利

```cpp
struct SinglyLink {
    struct SinglyLink *next;
};

struct DoublyLink {
    struct DoublyLink *prev, *next;
};
```

**单链表的局限性**

双链表引入的这个`prev`指针就是为了解决单链表无法向前查找的问题, 这里我们可以用删除当前节点的操作来演示使用场景

- target: 我们需要删除的节点
- del: 链表删除操作

```cpp
SinglyLink::del(prevNodePtr ?, &target);
DoublyLink::del(target.prev, &target);
```

通过代码可以直观的看出, 由于**从链表中删除节点需要知道该节点的前一个节点**, 所以从单链中删除target, 而找到target的前一个节点并不能很高效的完成。对于双链表只需要O(1)的复杂度。

## DoublyLink核心实现

采用节点 + 静态成员函数的方式进行定义DoublyLink

### 定义和初始化

只包含两个指针, 一个指向前驱节点, 一个指向后继节点。节点的初始化就是把这两个指针指向自己。可以把这样的节点视为一个没有数据的链表头结点, 或一个不在链表中的节点

```cpp
struct DoublyLink {
    struct DoublyLink *prev, *next;

    static void init(struct DoublyLink *target) {
        target->prev = target->next = target;
    }
};
```

### 插入和删除操作

双链表的插入操作, 需要处理三个节点中的4个指针。它们分别是:

- target的next指针 - 指向prev节点的next
- target的prev指针 - 指向prev节点
- prev的下一个节点的prev指针 - 指向target
- prev的next指针 - 指向target

```cpp
struct DoublyLink {
    static void insert(DoublyLink *prev, DoublyLink *target) {
        target->next = prev->next;
        target->prev = prev;
        prev->next->prev = target;
        prev->next = target;
    }

    static void del(DoublyLink *prev, DoublyLink *target) {
        prev->next = target->next;
        target->next->prev = prev;
    }
};
```

双链表的删除操作, 只需要更新删除节点的

- 前一个节点的next指针 - 指向target的下一个节点
- 后一个节点的prev指针 - 指向target的前一个节点

> 注:
>   对于双链表的del接口, 其实可以不用显示的传前一个节点的指针prev。但这里为了和单链表的节点格式进行统一保留了prev。等价形式:
>  - del(target)
>  - del(target->prev, target)


### 逆序遍历

通过prev指针, 从后向前遍历将变的异常容易。如下的逆序遍历for循环的代码框架几乎和向后遍历一致的

```cpp
// Node : linkPtr = malloc(sizeof(Link) + sizeof(Data))
for (auto linkPtr = head.prev; linkPtr != &head; linkPtr = linkPtr->prev) {
    MyData *dataPtr = reinterpret_cast<MyData *>(linkPtr + 1);
    // do something
}
```

## 使用示例

在**嵌入式单链表**章节从设计者视角详细的介绍了常用的使用示例。本章将中从实用角度出发来介绍。通过使用**组合式、嵌入式、继承式**的方式来实现同样一个功能来进行对比

### 组合式

```cpp
// embedded-dlist.2.cpp - write
//
// 描述:
//   嵌入式双链表 - 组合式
//
// 目标/要求:
//  - 在对应的SHOW_YOUR_CODE代码块实现 逆序遍历 和 链表的释放
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/EmbeddedList.hpp"

using d2ds::DefaultAllocator;

struct MyData {
    int id;
    char data;
};

int main() {

    d2ds::DefaultAllocator::debug() = true;

    d2ds::DoublyLink head;

    d2ds::DoublyLink::init(&head);

    for (int i = 0; i < 10; i++) {
        auto linkPtr = ( d2ds::DoublyLink* ) d2ds::DefaultAllocator::malloc(sizeof(d2ds::DoublyLink) + sizeof(MyData));
        d2ds::DoublyLink::init(linkPtr);
        auto dataPtr = (MyData *)(linkPtr + 1);
        dataPtr->id = i;
        dataPtr->data = 'a' + i;
        d2ds::DoublyLink::insert(&head, linkPtr);
    }

    dstruct::Stack<MyData> dataStack;
    for (auto linkPtr = head.next; linkPtr != &head; linkPtr = linkPtr->next) {
        auto dataPtr = reinterpret_cast<MyData *>(linkPtr + 1);
        dataStack.push(*dataPtr);
    }

    SHOW_YOUR_CODE({ // reverse traverse
        for (auto linkPtr = head.prev; linkPtr != &head; linkPtr = linkPtr->prev) {
            MyData *dataPtr = reinterpret_cast<MyData *>(linkPtr + 1);
            
            DONT_CHANGE(
                auto myData = dataStack.top();
                d2ds_assert_eq(dataPtr->id, myData.id);
                d2ds_assert_eq(dataPtr->data, myData.data);
                dataStack.pop();
            )
        }
    })

    d2ds_assert(dataStack.empty());

    SHOW_YOUR_CODE({ // use DefaultAllocator::free(addr) to release
        d2ds::DoublyLink *target = head.next;
        while (target != &head) {
            d2ds::DoublyLink::del(&head, target);
            DefaultAllocator::free(target);
            target = head.next;
        }
    })

    d2ds_assert(head.next == &head);

    XLINGS_WAIT

    return 0;
}
```

### 嵌入式

```cpp
// embedded-dlist.3.cpp - write
//
// 描述:
//   嵌入式双链表 - 嵌入式
//
// 目标/要求:
//  - 在对应的SHOW_YOUR_CODE代码块实现 逆序遍历 和 链表的释放
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/EmbeddedList.hpp"

using d2ds::DefaultAllocator;

struct MyData {
    d2ds::DoublyLink link;
    int id;
    char data;
};

int main() {

    d2ds::DefaultAllocator::debug() = true;

    d2ds::DoublyLink head;

    d2ds::DoublyLink::init(&head);

    for (int i = 0; i < 10; i++) {
        auto dataPtr = (MyData *) d2ds::DefaultAllocator::malloc(sizeof(MyData));
        d2ds::DoublyLink::init(&(dataPtr->link));
        dataPtr->id = i;
        dataPtr->data = 'a' + i;
        d2ds::DoublyLink::insert(&head, &(dataPtr->link));
    }

    dstruct::Stack<MyData> dataStack;
    for (auto linkPtr = head.next; linkPtr != &head; linkPtr = linkPtr->next) {
        auto dataPtr = reinterpret_cast<MyData *>(linkPtr);
        dataStack.push(*dataPtr);
    }

    SHOW_YOUR_CODE({ // reverse traverse
        for (auto linkPtr = head.prev; linkPtr != &head; linkPtr = linkPtr->prev) {
            MyData *dataPtr = reinterpret_cast<MyData *>(linkPtr);
            
            DONT_CHANGE(
                auto myData = dataStack.top();
                d2ds_assert_eq(dataPtr->id, myData.id);
                d2ds_assert_eq(dataPtr->data, myData.data);
                dataStack.pop();
            )
        }
    })

    d2ds_assert(dataStack.empty());

    SHOW_YOUR_CODE({ // use DefaultAllocator::free(addr) to release
        d2ds::DoublyLink *target = head.next;
        while (target != &head) {
            d2ds::DoublyLink::del(&head, target);
            DefaultAllocator::free(target);
            target = head.next;
        }
    })

    d2ds_assert(head.next == &head);

    XLINGS_WAIT

    return 0;
}
```

### 继承式

```cpp
// embedded-dlist.4.cpp - write
//
// 描述:
//   嵌入式双链表 - 继承式
//
// 目标/要求:
//  - 在对应的SHOW_YOUR_CODE代码块实现 逆序遍历 和 链表的释放
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/EmbeddedList.hpp"

using d2ds::DefaultAllocator;

template <typename T>
struct ENode : d2ds::DoublyLink {
    ENode * prev() {
        return static_cast<ENode *>(d2ds::DoublyLink::prev);
    }

    ENode * next() {
        return static_cast<ENode *>(d2ds::DoublyLink::next);
    }

    T * data() {
        return static_cast<T *>(this);
    }
};

struct MyData : ENode<MyData> {
    int id;
    char data;
};

int main() {

    d2ds::DefaultAllocator::debug() = true;

    ENode<MyData> head;

    d2ds::DoublyLink::init(&head);

    for (int i = 0; i < 10; i++) {
        auto dataPtr = (MyData *) d2ds::DefaultAllocator::malloc(sizeo(MyData));
        d2ds::DoublyLink::init(dataPtr);
        dataPtr->id = i;
        dataPtr->data = 'a' + i;
        d2ds::DoublyLink::insert(&head, dataPtr);
    }

    dstruct::Stack<MyData> dataStack;
    for (auto nodePtr = head.next(); nodePtr != &head; nodePtr = nodePtr->nex()) {
        auto dataPtr = nodePtr->data();
        dataStack.push(*dataPtr);
    }

    SHOW_YOUR_CODE({ // reverse traverse
        for (auto nodePtr = head.prev(); nodePtr != &head; nodePtr = nodePtr->prev()) {
            MyData *dataPtr = nodePtr->data();

            DONT_CHANGE(
                auto myData = dataStack.top();
                d2ds_assert_eq(dataPtr->id, myData.id);
                d2ds_assert_eq(dataPtr->data, myData.data);
                dataStack.pop();
            )
        }
    })

    d2ds_assert(dataStack.empty());

    SHOW_YOUR_CODE({ // use DefaultAllocator::free(addr) to release
        ENode *target = head.next();
        while (target != &head) {
            d2ds::DoublyLink::del(&head, target);
            DefaultAllocator::free(target);
            target = head.next();
        }
    })

    d2ds_assert(head.next() == &head);

    XLINGS_WAIT

    return 0;
}
```

## 总结

本章节是基于**嵌入式单链表**章节继续来介绍链表中最常用的双链表对应的嵌入式双链表的实现和使用示例。显示简单介绍了双链表的引入原因(相对与单链表)。然后, 又以同一个示例展示了嵌入式双链表的不同的使用方式