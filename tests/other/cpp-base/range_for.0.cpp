// range_for.0.cpp - readonly
//
// 描述:
//  实现py_range的类型定义
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/other/cpp-base/RangeFor.hpp中完成你的代码设计
//

#include <dstruct.hpp>

#include "common/common.hpp"

#include "exercises/other/cpp-base/RangeFor.hpp"

int main() {
    d2ds::py_range(0, 10);
    d2ds::py_range(0, 5, 200);
    return 0;
}