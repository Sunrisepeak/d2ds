// embedded-slist.4.cpp - write
//
// 描述:
//   嵌入式表链-remove操作练习
//
// 目标/要求:
//  - 删除list中数值为偶数的节点
//  - 在本文件中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/EmbeddedList.hpp"

using namespace d2ds;

struct IntNode : SinglyLink {
    int data;
};

int main() {

    SinglyLink list;

    // insert int node
    for (int i = 1; i <= 10; i++) {
        auto nodePtr = new IntNode();
        nodePtr->data = i;
        SinglyLink::insert(&list, nodePtr);
    }

    for (auto it = &list; it->next != &list; it = it->next) {
        // show your code

    }

    // release all
    int sum = 0;
    SinglyLink *p = list.next;
    while (p != &list) {

        sum += reinterpret_cast<IntNode *>(p)->data;

        auto q = p->next;
        delete p;
        p = q;
    }

    d2ds_assert_eq(sum, 1 + 3 + 5 + 7 + 9);

    D2DS_WAIT

    return 0;
}