// embedded-dlist.2.cpp - readonly
//
// 描述:
//   嵌入式双链表的插入和删除操作
//
// 目标/要求:
//  - 定义对应的DoublyLink和对应的init操作
//  - 在exercises/linked-list/EmbeddedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/EmbeddedList.hpp"

int main() {

    d2ds::DoublyLink head;

    d2ds::DoublyLink::init(&head);

    for (int i = 0; i < 10; i++) {
        auto linkPtr = new d2ds::DoublyLink();
        d2ds::DoublyLink::insert(&head, linkPtr);
    }

    int cnt = 0;
    while (head.next != &head) {
        cnt++;
        auto target = head.next;
        d2ds::DoublyLink::del(&head, target);
        delete target;
    }

    d2ds_assert_eq(cnt, 10);

    D2DS_WAIT

    return 0;
}