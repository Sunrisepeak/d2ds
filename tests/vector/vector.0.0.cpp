// vector.0.cpp - readonly
//
// 描述:
//  定义Vector
//
// 目标/要求:
//  - 实现类模板和数据初成员定义
//  - 在exercises/array/Vector.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Vector.hpp>

struct DataMember {
    int size;
    void *ptr;
};

int main() {

    d2ds::Vector<int> intVec;
    d2ds_assert(sizeof(intVec) >= sizeof(DataMember));

    D2DS_WAIT

    return 0;
}