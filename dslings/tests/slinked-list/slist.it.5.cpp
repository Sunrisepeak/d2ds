// slist.it.5.cpp - readonly
//
// 描述:
//   实现SLinkedList的插入/删除操作
//
// 目标/要求:
//  - 实现erase_after/insert_after成员函数
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::SLinkedList<int> intList = { 5, 4, 3, 2, 1 };

    auto it = intList.begin();
    intList.erase_after(it);
    ++it; d2ds_assert_eq(*it, 3);

    for (int val : intList) {
        std::cout << " " << val;
    }

    std::cout << std::endl;

    it = intList.begin();
    intList.insert_after(it, 6);
    ++it; d2ds_assert_eq(*it, 6);

    for (int val : intList) {
        std::cout << " " << val;
    }

    std::cout << std::endl;

    D2DS_WAIT

    return 0;
}