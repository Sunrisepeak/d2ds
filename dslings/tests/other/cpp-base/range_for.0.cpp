// range_for.0.cpp - readonly
//
// 描述:
//  实现PyRange的类型定义
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/other/cpp-base/RangeFor.hpp中完成你的代码设计
//

#include <dstruct.hpp>

#include "common/common.hpp"

#include "exercises/other/cpp-base/RangeFor.hpp"

int main() {
    d2ds::PyRange(0, 10);
    d2ds::PyRange(0, 5, 200);

    D2DS_WAIT

    return 0;
}