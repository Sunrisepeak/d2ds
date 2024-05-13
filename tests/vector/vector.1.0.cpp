// vector.1.cpp - readonly
//
// 描述:
//  显示定义数据结构Vector的bigfive - 析构
//
// 目标/要求:
//  - 实现Vector的析构函数
//  - 在exercises/array/Vector.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Vector.hpp>

using d2ds::BigFiveTest;

int main() {

    d2ds::DefaultAllocator::debug() = true;

    {
        d2ds::Vector<BigFiveTest::Obj> objArr(1);
    }

    d2ds_assert(BigFiveTest::destructor());
    d2ds_assert_eq(1,d2ds::DefaultAllocator::deallocate_counter());

    D2DS_WAIT

    return 0;
}