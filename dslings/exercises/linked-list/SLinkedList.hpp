#ifndef SLINKED_LIST_HPP_D2DS
#define SLINKED_LIST_HPP_D2DS

#include <common/common.hpp>

namespace d2ds {
// show your code

template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {

    struct Node {
        Node *next;
        T data;
    };

private:
    int mSize_e;
    Node mHead_e;
};

}

#endif