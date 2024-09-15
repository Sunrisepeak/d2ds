// embedded-dlist.0.cpp - readonly
//
// 描述:
//   定义嵌入式双链表和初始化操作
//
// 目标/要求:
//  - 定义对应的DoublyLink和对应的init操作
//  - 在exercises/linked-list/EmbeddedList.hpp中完成你的代码设计
//  - 通过所有编译器检测 和 断言
//

#include "common/common.hpp"

#include "exercises/linked-list/EmbeddedList.hpp"

int main() {

    d2ds::DoublyLink dLink;
    d2ds::DoublyLink::init(&dLink);
    d2ds_assert(dLink.next == dLink.prev);

    XLINGS_WAIT

    return 0;
}