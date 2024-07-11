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
        for (auto linkPtr = ?; linkPtr != &head; ) {
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
        d2ds::DoublyLink *target = head.next;
        while (target != &head) {
            DefaultAllocator::free(target);
        }
    })

    d2ds_assert(head.next == &head);

    D2DS_WAIT

    return 0;
}