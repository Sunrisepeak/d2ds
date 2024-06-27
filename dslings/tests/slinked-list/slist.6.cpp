// slinked-list.6.cpp - readonly
//
// 描述:
//   链表的"随机访问/下标索引访问用法模拟"
//
// 目标/要求:
//  - 实现重载operator[], 模拟实现下标索引访问 (一般不直接提供)
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::SLinkedList<int> intList = { 0, 1, 2, 3, 4, 5 };

    for (int i = 0; i < intList.size(); i++) {
        d2ds_assert_eq(intList[i], i);
    }

    D2DS_WAIT

    return 0;
}