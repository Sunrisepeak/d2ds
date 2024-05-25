// embedded-slist.3.cpp - write
//
// 描述:
//   嵌入式表链-插入操作练习
//
// 目标/要求:
//  - 创建5个IntNode节点并初始化为0 ~ 4插入到list中
//  - 在本文件中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/EmbeddedList.hpp"

using namespace d2ds;

struct IntNode {
    SinglyLink link;
    int data;

    IntNode() : link(), data { 0 } {}
};

int main() {

    SinglyLink list;

    // create & insert
    for (int i = 0; i < 5; i++) {
        // show your code (use `new` to create node)

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

    d2ds_assert_eq(sum, 0 + 1 + 2 + 3 + 4);

    D2DS_WAIT

    return 0;
}