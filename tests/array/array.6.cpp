// array.6.cpp - readonly
//
// 描述:
//  数据结构Array负下标访问数据支持
//
// 目标/要求:
//  - 实现负下标访问数据支持, 其中 -1 表示最后一个元素
//  - 在exercises/array/Array.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Array.hpp>

int main() {

    d2ds::Array<char, 4> intArr { 'd', '2', 'd', 's'};

    d2ds_assert_eq(intArr[0], intArr[-4]);
    d2ds_assert_eq(intArr[1], intArr[-3]);
    d2ds_assert_eq(intArr[2], intArr[-2]);
    d2ds_assert_eq(intArr[3], intArr[-1]);

    D2DS_WAIT

    return 0;
}