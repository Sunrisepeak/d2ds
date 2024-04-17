#ifndef ARRAY_HPP_D2DS
#define ARRAY_HPP_D2DS

#include <initializer_list>

#include <array>

namespace d2ds {
//using dstruct::Array;

// show your code

template <typename T, unsigned int N>
class Array {

public:
    Array(std::initializer_list<T> list) {
        int i = 0;
        for (auto it = list.end(); it != list.end(); it++) {
            mData_e[i] = *it;
            i++;
        }
    }

private:
    T mData_e[N == 0 ? 1 : N];
};

}
#endif