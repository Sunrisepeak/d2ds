// array.3.cpp - readonly
//
// 描述:
//  数据结构Array类模板的数据访问
//
// 目标/要求:
//  - 实现下标访问功能
//  - 在exercises/array/Array.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Array.hpp>

int main() {
    d2ds::Array<int, 5> intArr { 5, 4, 3, 2, 1 };

    intArr[1] = 6;

    d2ds_assert_eq(intArr[0], 5);
    d2ds_assert_eq(intArr[4], 1);

    intArr[4] = intArr[0];
    d2ds_assert_eq(intArr[0], intArr[4]);

    D2DS_WAIT

    return 0;
}