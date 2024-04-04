#ifndef __COMMON_HPP__D2DS
#define __COMMON_HPP__D2DS

#include <iostream>
#include <string>
#include <random>
#include <cassert>
#include <thread>

#define HONLY_LOGGER_TAG "D2DS"
#include "common/honly_logger.hpp"
#include "common/dslings_config.hpp"


#define d2ds_assert(expr) \
    if (!(expr)) { \
        HONLY_LOGW("❌ | %s", #expr); \
    } else { \
        HONLY_LOGI_P("✅ | %s", #expr); \
    }

#define d2ds_assert_eq(a, b) \
    if (a != b) {\
        HONLY_LOGW("❌ | %s == %s (%s == %s)", \
            #a, #b, std::to_string(a).c_str(), std::to_string(b).c_str()); \
    } else {\
        HONLY_LOGI_P("✅ | %s == %s (%s == %s)", \
            #a, #b, std::to_string(a).c_str(), std::to_string(b).c_str()); \
    }

#define D2DS_WAIT HONLY_LOGW("Delete the D2DS_WAIT to continue...");


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