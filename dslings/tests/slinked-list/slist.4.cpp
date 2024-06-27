// slist.4.cpp - readonly
//
// 描述:
//   实现链表的常用函数 - size/empty
//
// 目标/要求:
//  - 实现 size/empty
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::SLinkedList<int> intList;

    d2ds_assert_eq(intList.size(), 0);
    d2ds_assert(intList.empty());

    d2ds::SLinkedList<int> intList1 = { 1, 2, 3 };

    d2ds_assert_eq(intList1.size(), 3);
    d2ds_assert(!intList1.empty());

    D2DS_WAIT

    return 0;
}