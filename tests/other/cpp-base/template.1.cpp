// template.1.cpp - readonly
//
// 描述:
//  实现Box类模板 - 范型支持
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/other/cpp-base/Template.hpp中完成你的代码设计
//  - 通过所有编译器检查
//

#include <dstruct.hpp>

#include "common/common.hpp"

#include "exercises/other/cpp-base/Template.hpp"


int main() {
    d2ds::Box<int> intBox;
    d2ds::Box<dstruct::String> stringBox;

    D2DS_WAIT

    return 0;
}