// vector.2.cpp - readonly
//
// 描述:
//  数据结构Vector的迭代器支持
//
// 目标/要求:
//  - 实现Vector的begin/end
//  - 在exercises/array/Vector.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Vector.hpp>

int main() {

    d2ds::DefaultAllocator::debug() = false;

    d2ds::Vector<int> intArr = { 4, 3, 2, 1 };

    for (auto &val : intArr) {
        val *= 2;
    }

    const d2ds::Vector<int> constIntArr = intArr;

    int sum = 0;
    for (auto &val : constIntArr) {
        sum += val;
    }

    d2ds_assert_eq(sum, (4 + 3 + 2 + 1) * 2);

    //D2DS_WAIT

    return 0;
}