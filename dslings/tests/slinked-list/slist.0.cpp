// slist.0.cpp - readonly
//
// 描述:
//   定义SLinkedList及其数据成员
//
// 目标/要求:
//  - 定义SLinkedList及链表节点Node和对应的数据成员
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::SLinkedListNode<int> node;
    d2ds::SLinkedList<int> intList;
    d2ds::SLinkedList<double, d2ds::DefaultAllocator> doubleList;

    d2ds_assert(sizeof(intList) > 24);

    XLINGS_WAIT

    return 0;
}