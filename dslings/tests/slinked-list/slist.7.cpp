// slist.7.cpp - readonly
//
// 描述:
//   实现链表的尾部增删 - push_back / _pop_back
//
// 目标/要求:
//  - 实现单链表的_pop_back(通常不直接提供这个操作)
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::SLinkedList<int> intList;

    for (int i = 0; i < 5; i++) {
        intList.push_back(i);
    }

    for (int i = 0; i < intList.size(); i++) {
        d2ds_assert_eq(intList[i], i);
    }

    for (int i = 0; i < 5; i++) {
        d2ds_assert_eq(intList.size(), 5 - i);
        intList._pop_back();
    }

    d2ds_assert(intList.empty());

    D2DS_WAIT

    return 0;
}