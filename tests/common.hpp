#ifndef __COMMON_HPP__D2DS
#define __COMMON_HPP__D2DS

#include <iostream>
#include <random>
#include <cassert>
#include <thread>

#include <dstruct.hpp>

#define d2ds_assert_eq(a, b) \
if (a != b) \
    std::cerr << #a << " == " << #b << " (" << a << " == " << b << ")" << std::endl; \
assert((a) == (b))

namespace d2ds {

template <typename DSVType>
static void randomDataGenerator(DSVType &dsv, int rangeL, int rangeR) {
    // test: random data
    // Choose a random mean between 1 and 2 * ARR_SIZE
    // https://en.cppreference.com/w/cpp/numeric/random
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(rangeL, rangeR);

    for (auto it = dsv.begin(); it != dsv.end(); it++) {
        *it = uniform_dist(e1);
    }
}

template <typename DSVType>
static void ds_print(DSVType &dsv) {
    std::cerr << "[ ";
    for (auto it = dsv.begin(); it != dsv.end(); it++) {
        std::cerr << *it << " ";
    }
    std::cerr << "]" << std::endl;
}

}

#endif