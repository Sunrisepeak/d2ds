#ifndef SLINKED_LIST_HPP_D2DS
#define SLINKED_LIST_HPP_D2DS

#include <common/common.hpp>

namespace d2ds {
// show your code

template <typename T>
struct SLinkedListNode {
    SLinkedListNode *next;
    T data;
};

template <typename T>
struct SLinkedListIterator {
    using Node = SLinkedListNode<T>;
    SLinkedListIterator() : mNodePtr { nullptr } {}
    SLinkedListIterator(Node *nodePtr) : mNodePtr { nodePtr } { }

    T * operator->() {
        return &(mNodePtr->data);
    }

    T & operator*() {
        return mNodePtr->data;
    }

    bool operator==(const SLinkedListIterator &it) const {
        return mNodePtr == it.mNodePtr;
    }

    bool operator!=(const SLinkedListIterator &it) const {
        return mNodePtr != it.mNodePtr;
    }

    SLinkedListIterator & operator++() {
        mNodePtr = mNodePtr->next;
        return *this;
    }

    SLinkedListIterator operator++(int) {
        auto old = *this;
        mNodePtr = mNodePtr->next;
        return old;
    }

    Node *mNodePtr;
};

template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {

    using Node = SLinkedListNode<T>;

public:
    using Iterator = SLinkedListIterator<T>;

public:
    SLinkedList() : mSize_e { 0 }, mHead_e { &mHead_e, T()}, mTailPtr_e { &mHead_e } { 

    }

    SLinkedList(std::initializer_list<T> list) : SLinkedList() {
        for (auto it = list.begin(); it != list.end(); it++) {
            push_back(*it);
        }
    }

    SLinkedList(const SLinkedList &dsObj) : SLinkedList() {
        for (Node *nodePtr = dsObj.mHead_e.next; nodePtr != &(dsObj.mHead_e);) {
            push_back(nodePtr->data);
            nodePtr = nodePtr->next;
        }
    }

    SLinkedList & operator=(const SLinkedList &dsObj) {
        if (this != &dsObj) {
            this->~SLinkedList();
            for (Node *nodePtr = dsObj.mHead_e.next; nodePtr != &(dsObj.mHead_e);) {
                push_back(nodePtr->data);
                nodePtr = nodePtr->next;
            }
        }
        return *this;
    }

    SLinkedList(SLinkedList &&dsObj) : SLinkedList() {
        mHead_e.next = dsObj.mHead_e.next;
        mTailPtr_e = dsObj.mTailPtr_e;
        mSize_e = dsObj.mSize_e;
        mTailPtr_e->next = &mHead_e; // Note: update tail node

        // reset
        dsObj.mHead_e.next = &(dsObj.mHead_e);
        dsObj.mTailPtr_e = &(dsObj.mHead_e);
        dsObj.mSize_e = 0;
    }

    SLinkedList & operator=(SLinkedList &&dsObj) {
        if (this != &dsObj) {
            this->~SLinkedList();
            mHead_e.next = dsObj.mHead_e.next;
            mTailPtr_e = dsObj.mTailPtr_e;
            mSize_e = dsObj.mSize_e;
            mTailPtr_e->next = &mHead_e;

            // reset
            dsObj.mHead_e.next = &(dsObj.mHead_e);
            dsObj.mTailPtr_e = &(dsObj.mHead_e);
            dsObj.mSize_e = 0;
        }
        return *this;
    }

    ~SLinkedList() {
        while (mHead_e.next != &mHead_e) {
            Node *nodePtr = mHead_e.next;
            mHead_e.next = nodePtr->next;
            nodePtr->data.~T();
            Alloc::deallocate(nodePtr, sizeof(Node));
        }
        mSize_e = 0;
        mTailPtr_e = &mHead_e;
    }

public:

    int size() const {
        return mSize_e;
    }

    bool empty() const {
        return mHead_e.next == &mHead_e;
    }

    T & front() {
        return mHead_e.next->data;
    }

    T & back() {
        return mTailPtr_e->data;
    }

    T & operator[](int index) {
        // d2ds_assert(index < mSize_e && mSize != 0);
        Node *nodePtr = mHead_e.next;
        for (int i = 0; i < index; i++) {
            nodePtr = nodePtr->next;
        }
        return nodePtr->data;
    }

public:
    void push_back(const T &data) {

        auto nodePtr = static_cast<Node *>(Alloc::allocate(sizeof(Node)));

        new (&(nodePtr->data)) T(data);
        nodePtr->next = &mHead_e;

        mTailPtr_e->next = nodePtr;
        mTailPtr_e = nodePtr;

        mSize_e++;
    }

    void _pop_back() {
        // assert(size() > 0);
        Node *nodePtr = &mHead_e;
        while (nodePtr->next != mTailPtr_e) {
            nodePtr = nodePtr->next;
        }
        // delete from list
        nodePtr->next = &mHead_e;
        // release
        mTailPtr_e->data.~T();
        Alloc::deallocate(mTailPtr_e, sizeof(Node));
        mSize_e--;

        mTailPtr_e = nodePtr; // update
    }

    void push_front(const T &data) {

        auto nodePtr = static_cast<Node *>(Alloc::allocate(sizeof(Node)));
        new (&(nodePtr->data)) T(data);

        nodePtr->next = mHead_e.next;
        mHead_e.next = nodePtr;
        mSize_e++;

        if (mSize_e == 1) {
            mTailPtr_e = nodePtr;
        }
    }

    void pop_front() {
        Node *nodePtr = mHead_e.next;
        // delete from list
        mHead_e.next = nodePtr->next;
        // release
        nodePtr->data.~T();
        Alloc::deallocate(nodePtr, sizeof(Node));
        mSize_e--;

        if (mSize_e == 0)
            mTailPtr_e = &mHead_e; // update
    }

public:

    void erase_after(Iterator pos) {
        // assert(pos.mNodePtr->next != &mHead_e);
        Node *nodePtr = pos.mNodePtr->next;
        pos.mNodePtr->next = nodePtr->next;

        nodePtr->data.~T();
        Alloc::deallocate(nodePtr, sizeof(Node));
        mSize_e--;

        if (pos.mNodePtr->next == &mHead_e) {
            mTailPtr_e = pos.mNodePtr->next;
        }
    }

    void insert_after(Iterator pos, const T &data) {
        auto nodePtr = static_cast<Node *>(Alloc::allocate(sizeof(Node)));
        new (&(nodePtr->data)) T(data);

        nodePtr->next = pos.mNodePtr->next;
        pos.mNodePtr->next = nodePtr;
        mSize_e++;

        if (nodePtr->next == &mHead_e) {
            mTailPtr_e = nodePtr;
        }
    }

public:
    Iterator begin() {
        return mHead_e.next;
    }

    Iterator end() {
        return &mHead_e;
    }

private:
    int mSize_e;
    Node *mTailPtr_e;
    Node mHead_e;
};

}

#endif