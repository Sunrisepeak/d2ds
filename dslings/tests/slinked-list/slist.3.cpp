// slist.3.cpp - readonly
//
// 描述:
//   实现链表的移动语义
//
// 目标/要求:
//  - 实现 移动构造 和 移动赋值, 并通过资源分配与释放的检查
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::DefaultAllocator::debug() = true;

    {
        d2ds::SLinkedList<int> intList1 = { 1, 2, 3 };
        d2ds::SLinkedList<int> intList2(std::move(intList1));

        d2ds_assert_eq(d2ds::DefaultAllocator::allocate_counter(), 3);

        d2ds::SLinkedList<int> intList3;
        intList3 = std::move(intList2);

        d2ds_assert_eq(d2ds::DefaultAllocator::allocate_counter(), 3);

        intList3 = std::move(intList3); // self-assign checker

        d2ds_assert_eq(d2ds::DefaultAllocator::allocate_counter(), 3);
    }

    d2ds_assert_eq(d2ds::DefaultAllocator::deallocate_counter(), 3);

    D2DS_WAIT

    return 0;
}