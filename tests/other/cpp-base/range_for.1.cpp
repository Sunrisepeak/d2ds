// range_for.1.cpp - readonly
//
// 描述:
//  实现py_range的begin和end
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/other/cpp-base/Template.hpp中完成你的代码设计
//  - 通过所有断言检测
//

#include <dstruct.hpp>

#include "common/common.hpp"

#include "exercises/other/cpp-base/RangeFor.hpp"

int main() {
    d2ds::py_range range(2, 10);

    auto __begin = range.begin();
    auto __end = range.end();

    d2ds_assert_eq(*__begin, 2);
    d2ds_assert(__begin != __end);

    D2DS_WAIT

    return 0;
}