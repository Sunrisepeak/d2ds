// template.0.cpp - readonly
//
// 描述:
//  实现max函数模板
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/other/cpp-base/Template.hpp中完成你的代码设计
//  - 通过所有断言检测
//

#include <dstruct.hpp>

#include "common/common.hpp"

#include "exercises/other/cpp-base/Template.hpp"

int main() {

    { // int
        int a = -1, b = 1;
        d2ds_assert_eq(d2ds::max(a, b), dstruct::max(a, b));
    }

    { // unsigned int
        unsigned int a = 4294967295, b = 1;
        d2ds_assert_eq(d2ds::max(a, b), dstruct::max(a, b));
    }

    { // double
        double a = 1.3, b = 3.1;
        d2ds_assert_eq(d2ds::max(a, b), dstruct::max(a, b));
    }

    XLINGS_WAIT

    return 0;
}