// intrusive-list.0.cpp - readonly
//
// 描述:
//  通过实现一个MaxVal类型(保存最大值), 来介绍dslings的"编译器驱动开发"
//  即根据编译器的错误提示来完成这个训练流程的演示Demo, 并且通常为了降低难度会把一个'数据结构'的实现分成多个检测模块.
//  如: dslings.0.cpp dslings.1.cpp dslings.2.cpp
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/dslings.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/IntrusiveList.hpp"

using namespace d2ds;

struct IntNode {
    SinglyLink link;
    int data;

    IntNode() : link(), data { 0 } {}
};

int main() {

    SinglyLink head;

    // insert
    for (int i = 0; i < 10; i++) {
        auto nodePtr = new IntNode();
        nodePtr->data = i;
        SinglyLink::insert(&head, reinterpret_cast<SinglyLink *>(nodePtr));
    }

    // remove
    for (int i = 9; i > 4; i--) {
        auto p = head.next;
        int data = reinterpret_cast<IntNode *>(p)->data;
        d2ds_assert_eq(data, i);
        SinglyLink::remove(&head, p);
        delete p;
    }

    // release all
    int sum = 0;
    SinglyLink *p = head.next;
    while (p != &head) {
        sum += reinterpret_cast<IntNode *>(p)->data;
        auto q = p->next;
        delete p;
        p = q;
    }

    d2ds_assert_eq(sum, 0 + 1 + 2 + 3 + 4);

    //D2DS_WAIT

    return 0;
}