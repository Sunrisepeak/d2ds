// array.0.cpp - readonly
//
// 描述:
//  数据结构Array范型支持 
//
// 目标/要求:
//  - 实现类模板定义
//  - 在exercises/array/Array.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Array.hpp>

int main() {
    d2ds::Array<int, 5> intArr;
    d2ds::Array<double, 10> doubleArr;

    D2DS_WAIT

    return 0;
}