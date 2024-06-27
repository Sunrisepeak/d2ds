// slist.8.cpp - readonly
//
// 描述:
//   实现链表的前置增删 - push_front / pop_front
//
// 目标/要求:
//  - 实现单链表的push_front / pop_front 函数
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::SLinkedList<int> intList;

    for (int i = 0; i < 5; i++) {
        intList.push_front(i);
    }

    for (int i = 0; i < intList.size(); i++) {
        d2ds_assert_eq(intList[i], 5 - i - 1);
    }

    for (int i = 0; i < 5; i++) {
        d2ds_assert_eq(intList.front(), 5 - i - 1);
        intList.pop_front();
    }

    d2ds_assert(intList.empty());

    D2DS_WAIT

    return 0;
}