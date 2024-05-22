// embedded-slist.1.cpp - readonly
//
// 描述:
//   定义嵌入式单链表的插入操作(默认为循环链表)
//
// 目标/要求:
//  - 使用SinglyLink的insert操作
//  - 在exercises/linked-list/EmbeddedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/EmbeddedList.hpp"

using namespace d2ds;

int main() {

    SinglyLink head;

    for (int i = 0; i < 10; i++) {
        auto linkPtr = new SinglyLink();
        SinglyLink::insert(&head, linkPtr);
    }

    int cnt = 0;
    SinglyLink *p = head.next;
    while (p != &head) {
        cnt++;
        auto q = p->next;
        delete p;
        p = q;
    }

    d2ds_assert_eq(cnt, 10);

    D2DS_WAIT

    return 0;
}