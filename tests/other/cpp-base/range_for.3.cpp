// range_for.3.cpp - readonly
//
// 描述:
//  实现py_range在范围for循环的支持, 并保证数据生成的正确性
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
    {
        int index = 0;
        for (int val : d2ds::py_range(0, 10)) {
            d2ds_assert_eq(val, index);
            index++;
        }
    }

    {
        int index = 0, step = 5;
        for (auto val : d2ds::py_range(0, 50, step)) {
            d2ds_assert_eq(val, index);
            index += step;
        }
    }

    D2DS_WAIT

    return 0;
}