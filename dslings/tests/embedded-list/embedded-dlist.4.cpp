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
        auto dataPtr = (MyData *) d2ds::DefaultAllocator::malloc(sizeof(MyData));
        d2ds::DoublyLink::init(dataPtr);
        dataPtr->id = i;
        dataPtr->data = 'a' + i;
        d2ds::DoublyLink::insert(&head, dataPtr);
    }

    dstruct::Stack<MyData> dataStack;
    for (auto nodePtr = head.next(); nodePtr != &head; nodePtr = nodePtr->next()) {
        auto dataPtr = nodePtr->data();
        dataStack.push(*dataPtr);
    }

    SHOW_YOUR_CODE({ // reverse traverse
        for () {
            MyData *dataPtr = ?;

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
        
    })

    d2ds_assert(head.next() == &head);

    XLINGS_WAIT

    return 0;
}