// range_for.2.cpp - readonly
//
// 描述:
//  实现PyRange对象begin和end返回值支持*解引用和++操作
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/other/cpp-base/RangeFor.hpp中完成你的代码设计
//  - 通过所有断言检测
//

#include <dstruct.hpp>

#include "common/common.hpp"

#include "exercises/other/cpp-base/RangeFor.hpp"

int main() {
    d2ds::PyRange range(0, 10);

    auto begin = range.begin();
    auto end = range.end();

    d2ds_assert(begin != end);

    d2ds_assert_eq(*begin, 0);
    ++begin;
    d2ds_assert_eq(*begin, 1);

    D2DS_WAIT

    return 0;
}