// slinked-list.5.cpp - readonly
//
// 描述:
//   实现链表的常用函数 - front/back
//
// 目标/要求:
//  - 实现 front/back 访问第一个元素和最后一个元素
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::SLinkedList<int> intList = { 1, 2, 3 };

    d2ds_assert_eq(intList.front(), 1);
    d2ds_assert_eq(intList.back(), 3);

    D2DS_WAIT

    return 0;
}