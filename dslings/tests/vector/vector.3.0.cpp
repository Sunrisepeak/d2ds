// vector.3.cpp - readonly
//
// 描述:
//  数据结构Vector的最大内存容量capacity标记
//
// 目标/要求:
//  - Vector中 添加capacity成员和函数, 并更新所有构造函数和bigfive
//  - 在exercises/array/Vector.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Vector.hpp>

int main() {

    d2ds::DefaultAllocator::debug() = false;

    { // default cntor()
        d2ds::Vector<int> intArr1, intArr2;
        d2ds_assert_eq(intArr1.capacity(), intArr2.capacity());
        d2ds_assert_eq(intArr1.size(), intArr2.capacity());
    }

    { // cntor(int)
        d2ds::Vector<int> intArr(10);
        d2ds_assert_eq(intArr.capacity(), 10);
    }

    { // cntor(initializer_list)
        d2ds::Vector<int> intArr = {0, 1, 2, 3};
        d2ds_assert_eq(intArr.capacity(), 4);
    }

    { // copy-sem
        d2ds::Vector<int> intArr1 = {0, 1, 2, 3};
        d2ds::Vector<int> intArr2(intArr1), intArr3;
        d2ds_assert_eq(intArr1.capacity(), intArr2.capacity());

        intArr3 = intArr2;
        d2ds_assert_eq(intArr3.capacity(), intArr2.capacity());
    }

    { // move-sem
        d2ds::Vector<int> intArr1(10);
        d2ds::Vector<int> intArr2(std::move(intArr1)), intArr3;

        d2ds_assert_eq(intArr1.capacity(), 0);
        d2ds_assert_eq(intArr2.capacity(), 10);

        intArr3 = std::move(intArr2);

        d2ds_assert_eq(intArr3.capacity(), 10);
        d2ds_assert_eq(intArr2.capacity(), 0);
    }

    D2DS_WAIT

    return 0;
}