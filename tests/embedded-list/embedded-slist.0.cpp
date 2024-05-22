// embedded-slist.0.cpp - readonly
//
// 描述:
//   定义嵌入式单链表节点
//
// 目标/要求:
//  - 不修改该代码检测文件
//  - 在exercises/linked-list/EmbeddedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/EmbeddedList.hpp"

int main() {

    d2ds_assert_eq(sizeof(d2ds::SinglyLink), 8);

    D2DS_WAIT

    return 0;
}