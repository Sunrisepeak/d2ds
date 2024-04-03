#ifndef __RANGE_BASE_FOR_HPP__D2DS
#define __RANGE_BASE_FOR_HPP__D2DS

#include <common/common.hpp>

namespace d2ds {
// show your code

class py_range {
public:
    py_range(int start, int end) : py_range(start, 1, end) { }

    py_range(int start, int step, int end) {

        __mLen =  (end - start) / step;

        d2ds_assert(start < end);
        d2ds_assert(step > 0);
        d2ds_assert(__mLen <= 100);

        for (int i = 0; i < __mLen; i++) {
            __mArr[i] = start;
            start = start + step;
        }
    }

public:
    const int * begin() const {
        return __mArr;
    }

    const int * end() const {
        return __mArr + __mLen;
    }

private:
    int __mLen;
    int __mArr[100];
};

}

#endif