#ifndef COMMON_HPP_D2DS
#define COMMON_HPP_D2DS

#include <iostream>
#include <string>
#include <random>
#include <cassert>
#include <thread>

#define HONLY_LOGGER_TAG "D2DS"
#include "common/honly_logger.hpp"
#include "common/dslings_config.hpp"


#define d2ds_assert(expr) \
{ \
    if (!(expr)) { \
        HONLY_LOGW("❌ | %s", #expr); \
    } else { \
        HONLY_LOGI_P("✅ | %s", #expr); \
    } \
}

#define d2ds_assert_eq(a, b) \
{ \
    if (a != b) {\
        HONLY_LOGW("❌ | %s == %s (%s == %s)", \
            #a, #b, std::to_string(a).c_str(), std::to_string(b).c_str()); \
    } else {\
        HONLY_LOGI_P("✅ | %s == %s (%s == %s)", \
            #a, #b, std::to_string(a).c_str(), std::to_string(b).c_str()); \
    } \
}

#define D2DS_WAIT HONLY_LOGW("Delete the D2DS_WAIT to continue...");
#define D2DS_RETURN HONLY_LOGW("Delete the D2DS_RETURN to continue..."); return 0;

#define D2DS_SELF_ASSIGNMENT_CHECKER if (this == &dsObj) return *this;

namespace d2ds {

struct DefaultAllocator {

    static void * allocate(int bytes) {
        allocate_counter()++;
        if (debug())
            HONLY_LOGI("DefaultAllocator: try to allocate %d bytes", bytes);
        return malloc(bytes);
    }

    static void deallocate(void *addr, int bytes) {
        deallocate_counter()++;
        if (debug())
            HONLY_LOGI("DefaultAllocator: free addr %p, bytes %d", addr, bytes);
        assert(addr != nullptr);
        free(addr);
    }

public: // config & status
    static bool & debug() {
        static bool debugFlag = false;
        return debugFlag;
    }

    static int & allocate_counter() {
        static int cnt = 0;
        return cnt;
    }

    static int & deallocate_counter() {
        static int cnt = 0;
        return cnt;
    }

    static void clear_status() {
        allocate_counter() = 0;
        deallocate_counter() = 0;
    }

};

class BigFiveTest {
public:

    struct Obj {
        Obj(int data_ = 0) : data { data_ } { get_test_data_e().mDestructor++; }

        Obj(const Obj &obj) {
            get_test_data_e().mDestructor++;
            get_test_data_e().mCopyConstructor = true;
        }
        Obj & operator=(const Obj &obj) {
            get_test_data_e().mDestructor++;
            get_test_data_e().mCopyAssignment = true;
            if (this == &obj) get_test_data_e().mSelfAssignment = true;
            return *this;
        }

        Obj(Obj &&obj) { get_test_data_e().mMoveConstructor = true; }
        Obj & operator=(Obj &&obj) {
            get_test_data_e().mMoveAssignment = true;
            if (this == &obj) get_test_data_e().mSelfAssignment = true;
            return *this;
        }

        ~Obj() { get_test_data_e().mDestructor--; }

        int data;
    };

public: // checker
    static bool destructor(bool enableInfo = false) {
        if (enableInfo)
            HONLY_LOGD("checker -> %d == 0", get_test_data_e().mDestructor);
        return get_test_data_e().mDestructor == 0;
    }

    static bool copy_constructor(bool enableInfo = false) {
        if (enableInfo)
            HONLY_LOGD("checker -> %d", get_test_data_e().mCopyConstructor);
        return get_test_data_e().mCopyConstructor;
    }

    static bool copy_assignment(bool enableInfo = false) {
        if (enableInfo)
            HONLY_LOGD("checker -> %d", get_test_data_e().mCopyAssignment);
        return get_test_data_e().mCopyAssignment;
    }

    static bool move_constructor(bool enableInfo = false) {
        if (enableInfo)
            HONLY_LOGD("checker -> %d", get_test_data_e().mMoveConstructor);
        return get_test_data_e().mMoveConstructor;
    }

    static bool move_assignment(bool enableInfo = false) {
        if (enableInfo)
            HONLY_LOGD("checker -> %d", get_test_data_e().mMoveAssignment);
        return get_test_data_e().mMoveAssignment;
    }

    static bool self_assignment(bool enableInfo = false) {
        if (enableInfo)
            HONLY_LOGD("checker -> %d", get_test_data_e().mMoveAssignment);
        return get_test_data_e().mSelfAssignment == false;
    }

public:
    static bool copy_constructor_pass() {
        get_test_data_e().mCopyConstructor = true;
    }

    static bool copy_assignment_pass() {
        get_test_data_e().mCopyAssignment = true;
    }

    static bool move_constructor_pass() {
        get_test_data_e().mMoveConstructor = true;
    }

    static bool move_assignment_pass() {
        get_test_data_e().mMoveAssignment = true;
    }

    static bool self_assignment_pass() {
        get_test_data_e().mSelfAssignment = true;
    }

public:

    static void clear_status() {
        get_test_data_e().mDestructor = 0;
        get_test_data_e().mCopyConstructor = false;
        get_test_data_e().mCopyAssignment = false;
        get_test_data_e().mMoveConstructor = false;
        get_test_data_e().mMoveAssignment = false;
    }

    static void print_status() {
        HONLY_LOGW("BigFiveTest status:");
        HONLY_LOGI("mDestructor %s", get_test_data_e().mDestructor == 0 ? "pass" : "failed");
        HONLY_LOGI("mCopyConstructor %s", get_test_data_e().mCopyConstructor ? "pass" : "failed");
        HONLY_LOGI("mCopyAssignment %s", get_test_data_e().mCopyAssignment ? "pass" : "failed");
        HONLY_LOGI("mMoveConstructor %s", get_test_data_e().mMoveConstructor ? "pass" : "failed");
        HONLY_LOGI("mMoveAssignment %s", get_test_data_e().mMoveAssignment ? "pass" : "failed");
        HONLY_LOGI("mSelfAssignment %s", get_test_data_e().mSelfAssignment == false ? "pass" : "failed");
    }

private:
    struct TestData {
        int mDestructor = 0;
        bool mCopyConstructor = false;
        bool mCopyAssignment = false;
        bool mMoveConstructor = false;
        bool mMoveAssignment = false;
        bool mSelfAssignment = false;
    };

    static TestData & get_test_data_e() {
        static TestData data;
        return data;
    }
};

template <typename DSVType>
static void random_data_generator(DSVType &dsv, int rangeL, int rangeR) {
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