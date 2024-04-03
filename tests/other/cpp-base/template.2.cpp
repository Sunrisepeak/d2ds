// template.2.cpp - readonly
//
// 描述:
//  实现Box类模板, 来存储指定类型的值
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

    {
        d2ds::Box<int> box;
        box.set_value(2);
        d2ds_assert_eq(box.get_value(), 2);
    }

    {
        d2ds::Box<dstruct::String> box;
        box.set_value("Hello, d2ds!");
        d2ds_assert(box.get_value() == dstruct::String("Hello, d2ds!"));
    }

    D2DS_WAIT

    return 0;
}