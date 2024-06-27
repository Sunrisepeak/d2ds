// slist.it.1.cpp - readonly
//
// 描述:
//   实现迭代器的类指针行为
//
// 目标/要求:
//  - 重载SLinkedListIterator的 -> 和 * 运算符
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    struct MyObj {
        char a;
        int b;
        float c;
    };
    MyObj obj {'a', 1, 1.1};

    d2ds::SLinkedListNode<MyObj> node;
    node.data = obj;

    d2ds::SLinkedList<MyObj>::Iterator iterator(&node);
    d2ds_assert_eq(iterator->a, obj.a);
    d2ds_assert_eq(iterator->b, obj.b);
    d2ds_assert_eq(iterator->c, obj.c);

    (*iterator).c = 2.2;

    //d2ds_assert_eq(2.2, node.data.c); // defaul 2.2 is double
    d2ds_assert_eq(2.2f, node.data.c);

    D2DS_WAIT

    return 0;
}