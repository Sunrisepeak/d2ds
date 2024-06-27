// slist.it.0.cpp - readonly
//
// 描述:
//   定义SLinkedList的迭代器类型, 用来管理当前节点的数据访问
//
// 目标/要求:
//  - 定义SLinkedListIterator类模板, 并在SLinkedList定义对应的类型别名
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::SLinkedListNode<int> node;

    node.next = nullptr;
    node.data = 0;

    d2ds::SLinkedListIterator<int> iterator1(&node);
    d2ds::SLinkedList<int>::Iterator iterator2(&node);

    d2ds_assert_eq(sizeof(iterator1), 8);
    d2ds_assert_eq(sizeof(iterator2), 8);

    D2DS_WAIT

    return 0;
}