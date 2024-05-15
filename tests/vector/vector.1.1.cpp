// vector.1.cpp - readonly
//
// 描述:
//  显示定义数据结构Vector的bigfive - 拷贝语义
//
// 目标/要求:
//  - 实现Vector的拷贝构造和拷贝赋值
//  - 在exercises/array/Vector.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Vector.hpp>

using d2ds::BigFiveTest;

int main() {

    d2ds::DefaultAllocator::debug() = true;

    {
        d2ds::Vector<BigFiveTest::Obj> objArr1(5);

        d2ds::Vector<BigFiveTest::Obj> objArr2(objArr1);
        d2ds::Vector<BigFiveTest::Obj> objArr3 = objArr1;
        d2ds_assert(BigFiveTest::copy_constructor());

        D2DS_RETURN

        objArr3 = objArr2;
        //d2ds_assert(BigFiveTest::copy_assignment());

        objArr1 = objArr1;
    }

    d2ds_assert(BigFiveTest::destructor(true));

    D2DS_WAIT

    return 0;
}