// array.4.cpp - readonly
//
// 描述:
//  数据结构Array常用函数实现
//
// 目标/要求:
//  - 实现 size, back 成员函数
//  - 在exercises/array/Array.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Array.hpp>

int main() {
    d2ds::Array<int, 5> intArr { 0, 1, 2, 3, 4 };

    for (int i = 0; i < intArr.size(); i++) {
        d2ds_assert_eq(i, intArr[i]);
    }

    d2ds_assert_eq(4, intArr.back());

    D2DS_WAIT

    return 0;
}