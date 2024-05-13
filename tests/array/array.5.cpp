// array.5.cpp - readonly
//
// 描述:
//  数据结构Array的迭代器支持 - 范围for支持
//
// 目标/要求:
//  - 实现迭代器支持 & 范围for支持
//  - 在exercises/array/Array.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Array.hpp>

int main() {
    d2ds::Array<int, 5> intArr { 0, 1, 2, 3, 4 };

    d2ds_assert(intArr.begin() != intArr.end());

    int val = 0;
    for (int data : intArr) {
        d2ds_assert_eq(data, val);
        val++;
    }

    D2DS_WAIT

    return 0;
}