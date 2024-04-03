// array.0.cpp - readonly
//
// 描述:
//  实现Array数据结构可以存储开发者指定类型的功能
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/array/Array.hpp中完成你的代码设计
//  - 通过Array类型定义的编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Array.hpp>

int main() {
    d2ds::Array<int, 5> intArr;
    d2ds::Array<double, 10> doubleArr;
    return 0;
}