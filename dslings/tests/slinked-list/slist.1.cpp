// slist.1.cpp - readonly
//
// 描述:
//   实现链表的数据成员的初始化, 以及资源的释放
//
// 目标/要求:
//  - 实现 默认初始化/列表初始化对应的构造函数, 以及析构函数
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::DefaultAllocator::debug() = true;

    {
        d2ds::SLinkedList<int> intList1;
        d2ds::SLinkedList<int> intList3 = { 1, 2, 3 };
    }

    d2ds_assert_eq(
        d2ds::DefaultAllocator::allocate_counter(),
        d2ds::DefaultAllocator::deallocate_counter()
    );

    D2DS_WAIT

    return 0;
}