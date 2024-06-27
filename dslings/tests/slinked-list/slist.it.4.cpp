// slist.it.4.cpp - readonly
//
// 描述:
//   实现SLinkedList的begin/end来获取迭代器
//
// 目标/要求:
//  - 实现begin/end成员函数 并通过for循环检查
//  - 在exercises/linked-list/SLinkedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/SLinkedList.hpp"

int main() {

    d2ds::SLinkedList<int> intList = { 5, 4, 3, 2, 1 };

    auto it = intList.begin();

    d2ds_assert_eq(*it, 5);
    it++; d2ds_assert_eq(*it, 4);
    it++; d2ds_assert_eq(*it, 3);
    it++; d2ds_assert_eq(*it, 2);
    it++; d2ds_assert_eq(*it, 1);

    d2ds_assert(++it == intList.end());

    int tmp = 5; 
    for (auto val : intList) {
        d2ds_assert_eq(val, tmp);
        tmp--;
    }

    D2DS_WAIT

    return 0;
}