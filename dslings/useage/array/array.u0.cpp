// dslings.useage.cpp - write
//
// 描述:
//  d2ds-dslngs的"编译器驱动开发模式"使用示例
//
// 目标/要求:
//  - 修复该代码中的编译错误
//
// 参考资料:
//  - 接口文档: https://en.cppreference.com/w/cpp/container/array
//  - 设计原理: https://sunrisepeak.github.io/d2ds/chapter_01_array.html
//

#include <iostream>
#include <array>

#include "common/common.hpp"

int main() {

    std::array<int, 5> arr = {1, 2, 3, 4, 5}

    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    XLINGS_WAIT

    return 0;
}