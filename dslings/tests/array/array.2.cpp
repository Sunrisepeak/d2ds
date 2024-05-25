// array.2.cpp - readonly
//
// 描述:
//  数据结构Array类模板行为控制(显式定义bigfive)
//  (构造|析构 / 赋值构造 / 赋值分配 / 移动构造 / 移动赋值)
//  https://en.cppreference.com/w/cpp/language/rule_of_three
//
// 目标/要求:
//  - 实现下标访问功能
//  - 在exercises/array/Array.hpp中完成你的代码设计
//  - 通过编译器检测 & 断言检查
//

#include "common/common.hpp"

#include <exercises/array/Array.hpp>

using d2ds::BigFiveTest;

int main() {
    {
        d2ds::Array<BigFiveTest::Obj, 5> intArr;
    }
    d2ds_assert(BigFiveTest::destructor());

    {
        d2ds::Array<BigFiveTest::Obj, 5> intArr1;

        d2ds::Array<BigFiveTest::Obj, 5> intArr2(intArr1);
        d2ds::Array<BigFiveTest::Obj, 5> intArr3 = intArr1;
//        d2ds_assert(BigFiveTest::copy_constructor());

        intArr3 = intArr2;
        d2ds_assert(BigFiveTest::copy_assignment());

        intArr1 = intArr1;
    }

    {
        d2ds::Array<BigFiveTest::Obj, 5> intArr1;
        d2ds::Array<BigFiveTest::Obj, 5> intArr2 { std::move(intArr1) };
//        d2ds_assert(BigFiveTest::move_constructor());

        intArr1 = std::move(intArr2);
        d2ds_assert(BigFiveTest::move_assignment());

        intArr1 = std::move(intArr1);
    }

    d2ds_assert(BigFiveTest::self_assignment());
    d2ds_assert(BigFiveTest::destructor());
    //BigFiveTest::print_status();

    D2DS_WAIT

    return 0;
}