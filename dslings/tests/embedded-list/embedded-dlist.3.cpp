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

    D2DS_WAIT

    return 0;
}