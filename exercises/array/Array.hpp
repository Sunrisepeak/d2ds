#ifndef ARRAY_HPP_D2DS
#define ARRAY_HPP_D2DS

#include <initializer_list>

namespace d2ds {
//using dstruct::Array;

// show your code

template <typename T, unsigned int N>
class Array {

public: // bigFive

    Array() = default;

    Array(const Array &dsObj) {
        for (int i = 0; i < N; i++) {
            new (mData_e + i) T(dsObj.mData_e[i]);
        }
    }

    Array & operator=(const Array &dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        for (int i = 0; i < N; i++) {
            mData_e[i] = dsObj.mData_e[i];
        }
        return *this;
    }

    Array(Array &&dsObj) {
        for (int i = 0; i < N; i++) {
            new (mData_e + i) T(std::move(dsObj.mData_e[i]));
        }
    }

    Array & operator=(Array &&dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        for (int i = 0; i < N; i++) {
            mData_e[i] = std::move(dsObj.mData_e[i]);
        }
        return *this;
    }

    Array(std::initializer_list<T> list) {
        int i = 0;
        for (auto it = list.begin(); it != list.end() && i < N; it++) {
            mData_e[i] = *it;
            i++;
        }
    }

    ~Array() = default;

private:
    T mData_e[N == 0 ? 1 : N];
};

}
#endif