// embedded-slist.0.cpp - readonly
//
// 描述:
//   定义嵌入式单链表节点
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    dstruct::Vector<int> vec(5, 1);

    d2ds::SLinkedList<int> intList1;
    d2ds::SLinkedList<int> intList2(10);
    d2ds::SLinkedList<int> intList3 = { 1, 2, 3 };
    d2ds::SLinkedList<int> intList4(vec.begin(), vec.end());

    D2DS_WAIT

    return 0;
}