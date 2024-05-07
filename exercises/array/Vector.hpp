#ifndef VECTOR_HPP_D2DS
#define VECTOR_HPP_D2DS

#include <initializer_list>

#include "common/common.hpp"

namespace d2ds {
// show your code

template <typename T, typename Alloc = DefaultAllocator>
class Vector {
public:
    Vector() : mSize_e { 0 }, mCapacity_e { 0 }, mDataPtr_e { nullptr } { }

    Vector(const Vector &dsObj) : mSize_e { dsObj.mSize_e } {
        mDataPtr_e = (T *) Alloc::allocate(sizeof(T) * mSize_e);
        mCapacity_e = dsObj.mCapacity_e;
        for (int i = 0; i < mSize_e; i++) {
            new (mDataPtr_e + i) T(dsObj.mDataPtr_e[i]);
        }
    }

    Vector & operator=(const Vector &dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        this->~Vector();
        mSize_e = dsObj.mSize_e;
        mCapacity_e = dsObj.mCapacity_e;
        mDataPtr_e = static_cast<T *>(Alloc::allocate(sizeof(T) * mSize_e));
        for (int i = 0; i < mSize_e; i++) {
            mDataPtr_e[i] = dsObj.mDataPtr_e[i];
        }
        return *this;
    }

    Vector(Vector &&dsObj) : mSize_e { dsObj.mSize_e } {
        mDataPtr_e = dsObj.mDataPtr_e;
        mCapacity_e = dsObj.mCapacity_e;
        // reset
        dsObj.mSize_e = 0;
        dsObj.mDataPtr_e = nullptr;
        dsObj.mCapacity_e = 0;
    }

    Vector & operator=(Vector &&dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        this->~Vector();
        mSize_e = dsObj.mSize_e;
        mCapacity_e = dsObj.mCapacity_e;
        mDataPtr_e = dsObj.mDataPtr_e;
        // reset
        dsObj.mSize_e = 0;
        dsObj.mDataPtr_e = nullptr;
        dsObj.mCapacity_e = 0;
        return *this;
    }

    Vector(int size) : mSize_e { size } {
        mDataPtr_e = static_cast<T *>(Alloc::allocate(sizeof(T) * mSize_e));
        for (int i = 0; i < mSize_e; i++) {
            new (mDataPtr_e + i) T();
        }
        mCapacity_e = mSize_e;
    }

    Vector(std::initializer_list<T> list) {
        mCapacity_e = mSize_e = list.end() - list.begin();
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
        mSize_e = mCapacity_e = 0;
        mDataPtr_e = nullptr;
    }

public:
    void push_back(const T &element) {
        if (mSize_e + 1 > mCapacity_e) {
            resize(mCapacity_e == 0 ? 2 : 2 * mCapacity_e);
        }
        new (mDataPtr_e + mSize_e) T(element);
        mSize_e++;
    }

    void pop_back() {
        mSize_e--;
        (mDataPtr_e + mSize_e)->~T();
        if (mSize_e <= mCapacity_e / 3) {
            resize(mCapacity_e / 2);
        }
    }


    void resize(int n) { // only mSize_e < n
        auto newDataPtr = n == 0 ? nullptr : static_cast<T *>(Alloc::allocate(n * sizeof(T)));

        for (int i = 0; i < mSize_e; i++) {
            new (newDataPtr + i) T(mDataPtr_e[i]);
            (mDataPtr_e + i)->~T();
        }

        if (mDataPtr_e) {
            // Note:
            //  memory-size is mCapacity_e * sizeof(T) rather than mSize_e * sizeof(T)
            Alloc::deallocate(mDataPtr_e, mCapacity_e * sizeof(T));
        }

        mCapacity_e = n;
        mDataPtr_e = newDataPtr;
    }

public:
    int size() const {
        return mSize_e;
    }

    int capacity() const {
        return mCapacity_e;
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

public:
    T * begin() {
        return mDataPtr_e;
    }

    T * end() {
        return mDataPtr_e + mSize_e;
    }

    const T * begin() const {
        return mDataPtr_e;
    }

    const T * end() const {
        return mDataPtr_e + mSize_e;
    }

private:
    int mSize_e, mCapacity_e;
    T * mDataPtr_e;
};

template <typename T>
bool operator==(const Vector<T> &v1, const Vector<T> &v2) {
    return v1[0] == v2[0] && v1[1] == v2[1];
}

template <typename T>
Vector<T> operator+(const Vector<T> &v1, const Vector<T> &v2) {
    Vector<T> v(2);
    v[0] = v1[0] + v2[0];
    v[1] = v1[1] + v2[1];
    return std::move(v);
}

template <typename T>
Vector<T> operator-(const Vector<T> &v1, const Vector<T> &v2) {
    Vector<T> v(2);
    v[0] = v1[0] - v2[0];
    v[1] = v1[1] - v2[1];
    return std::move(v);
}

}

#endif