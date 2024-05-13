// vector.1.cpp - readonly
//
// 描述:
//  显示定义数据结构Vector的bigfive - 移动语义
//
// 目标/要求:
//  - 实现Vector的移动构造和移动赋值
//  - 在exercises/array/Vector.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Vector.hpp>

using d2ds::BigFiveTest;

int main() {

    d2ds::DefaultAllocator::debug() = true;

    {
        d2ds::Vector<BigFiveTest::Obj> objArr1(5), objArr2(10);
        d2ds::Vector<BigFiveTest::Obj> objArr3 { std::move(objArr1) };
        //d2ds_assert(BigFiveTest::move_constructor());

        objArr3 = std::move(objArr2);
        //d2ds_assert(BigFiveTest::move_assignment());

        objArr3 = std::move(objArr3);

        d2ds_assert_eq(d2ds::DefaultAllocator::allocate_counter(), 2);
    }

    d2ds_assert_eq(d2ds::DefaultAllocator::deallocate_counter(), 2);

    d2ds_assert(BigFiveTest::self_assignment());
    d2ds_assert(BigFiveTest::destructor(true));

    D2DS_WAIT

    return 0;
}