// vector.2.cpp - readonly
//
// 描述:
//  数据结构Vector的常用函数和数据访问
//
// 目标/要求:
//  - 实现Vector的empty/size/operator[]
//  - 在exercises/array/Vector.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Vector.hpp>

int main() {

    d2ds::DefaultAllocator::debug() = false;

    d2ds::Vector<int> intArr1;
    d2ds_assert(intArr1.empty());

    d2ds::Vector<int> intArr2(10);
    d2ds_assert_eq(intArr2.size(), 10);

    d2ds::Vector<int> intArr3 = { -1, -2, -3 };
    const d2ds::Vector<int> constIntArr3 = { 1, 2, 3 };

    d2ds_assert_eq(intArr3[1], -2);

    intArr3[0] = constIntArr3[1] * intArr3[2];
    d2ds_assert_eq(intArr3[0], 2 * -3);

    D2DS_WAIT

    return 0;
}