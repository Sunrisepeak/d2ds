// array.1.cpp - readonly
//
// 描述:
//  数据结构Array的数据初始化
//
// 目标/要求:
//  - 实现列表初始化器的数据初始化
//  - 在exercises/array/Array.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Array.hpp>

int main() {
    d2ds::Array<int, 5> intArr { 5, 4, 3, 2 /*, 1*/ };

    D2DS_WAIT

    return 0;
}