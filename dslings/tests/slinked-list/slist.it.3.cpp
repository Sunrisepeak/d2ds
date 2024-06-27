// slist.it.3.cpp - readonly
//
// 描述:
//   实现单链表迭代器的前进迭代操作
//
// 目标/要求:
//  - 重载operator++运算符
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::SLinkedListNode<int> node;
    node.next = nullptr;

    d2ds::SLinkedList<int>::Iterator iterator1(&node);
    d2ds::SLinkedList<int>::Iterator iterator2(&node);
    d2ds::SLinkedList<int>::Iterator iterator3(nullptr);

    d2ds_assert(++iterator1 == iterator3);
    d2ds_assert(iterator2++ != iterator3);
    d2ds_assert(iterator2 == iterator3);

    D2DS_WAIT

    return 0;
}