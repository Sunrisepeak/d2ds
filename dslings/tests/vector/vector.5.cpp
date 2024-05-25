// vector.2.cpp - readonly
//
// 描述:
//  数据结构Vector的向量加减法扩展和判断等
//
// 目标/要求:
//  - 实现Vector的operator+/operator-/operator==的重载
//  - 在exercises/array/Vector.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Vector.hpp>

int main() {

    d2ds::DefaultAllocator::debug() = false;

    d2ds::Vector<int> OQ = { 4, 1, 1 };
    d2ds::Vector<int> OP = { 2, 4, 4 };
    d2ds::Vector<int> QP = { -2, 3, 3 };  

    d2ds_assert(OQ + QP == OP);
    d2ds_assert(OP - OQ == QP);

    D2DS_WAIT

    return 0;
}