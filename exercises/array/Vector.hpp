#ifndef VECTOR_HPP_D2DS
#define VECTOR_HPP_D2DS

#include <initializer_list>

#include "common/common.hpp"

namespace d2ds {
// show your code

template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    Vector() : mSize_e { 0 }, mDataPtr_e { nullptr } { }

    Vector(const Vector &dsObj) : mSize_e { dsObj.mSize_e } {
        mDataPtr_e = (T *) Alloc::allocate(sizeof(T) * mSize_e);
        for (int i = 0; i < mSize_e; i++) {
            new (mDataPtr_e + i) T(dsObj.mDataPtr_e[i]);
        }
    }

    Vector & operator=(const Vector &dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        this->~Vector();
        mSize_e = dsObj.mSize_e;
        mDataPtr_e = static_cast<T *>(Alloc::allocate(sizeof(T) * mSize_e));
        for (int i = 0; i < mSize_e; i++) {
            mDataPtr_e[i] = dsObj.mDataPtr_e[i];
        }
        return *this;
    }

    Vector(Vector &&dsObj) : mSize_e { dsObj.mSize_e } {
        mDataPtr_e = dsObj.mDataPtr_e;
        // reset
        dsObj.mSize_e = 0;
        dsObj.mDataPtr_e = nullptr;
    }

    Vector & operator=(Vector &&dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        this->~Vector();
        mSize_e = dsObj.mSize_e;
        mDataPtr_e = dsObj.mDataPtr_e;
        // reset
        dsObj.mSize_e = 0;
        dsObj.mDataPtr_e = nullptr;
        return *this;
    }

    Vector(int size) : mSize_e { size } {
        mDataPtr_e = static_cast<T *>(Alloc::allocate(sizeof(T) * mSize_e));
        for (int i = 0; i < mSize_e; i++) {
            new (mDataPtr_e + i) T();
        }
    }

    Vector(std::initializer_list<T> list) {
        mSize_e = list.end() - list.begin();
        mDataPtr_e = static_cast<T *>(Alloc::allocate(sizeof(T) * mSize_e));
        auto it = list.begin();
        T *data = mDataPtr_e;
        while (it != list.end()) {
            new (data) T(*it);
            it++; data++;
        }
    }

    ~Vector() {
        if (mSize_e) {
            for (int i = 0; i < mSize_e; i++) {
                (mDataPtr_e + i)->~T();
            }
            Alloc::deallocate(mDataPtr_e, mSize_e * sizeof(T));
        }
    }

public:
    int size() const {
        return mSize_e;
    }

    bool empty() const {
        return mSize_e == 0;
    }

    T & operator[](int index) {
        return mDataPtr_e[index];
    }

    const T & operator[](int index) const {
        return mDataPtr_e[index];
    }

private:
    int mSize_e, mCapacity_e;
    T * mDataPtr_e;
};

}

#endif