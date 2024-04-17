// array.2.cpp - readonly
//
// 描述:
//  数据结构Array的模板类bigfive显示定义
//  (赋值构造 / 赋值分配 / 移动构造 / 移动赋值 / 析构)
//  https://en.cppreference.com/w/cpp/language/rule_of_three
//
// 目标/要求:
//  - 实现下标访问功能
//  - 在exercises/array/Array.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Array.hpp>

using TestObj = d2ds::BigFiveTest::Obj;

int main() {
    {
        std::array<TestObj, 5> intArr;
    }
    d2ds::BigFiveTest::destructor();

    return 0;
}