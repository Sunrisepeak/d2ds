// vector.0.cpp - readonly
//
// 描述:
//  Vector的不同初始化方式
//
// 目标/要求:
//  - 实现 默认初始化、指定长度初始化、列表初始化 对应的构造函数
//  - 在exercises/array/Vector.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Vector.hpp>

struct StackMemAllocator {

    static void * allocate(int bytes) {
        HONLY_LOGI("StackMemAllocator: try to allocate %d bytes", bytes);
        mTop = mTop - bytes;
        assert(mTop >= mMemory);
        return mTop;
    }

    static void deallocate(void *addr, int bytes) {
        HONLY_LOGI("StackMemAllocator: free addr %p, bytes %d", addr, bytes);
        // nothing
    }

    static void config_and_init(char *memory, int size) {
        mMemory = memory;
        mTop = memory + size;
    }

    static char *mTop;
    static char *mMemory;
};

char * StackMemAllocator::mTop = nullptr;
char * StackMemAllocator::mMemory = nullptr;


int main() {

    d2ds::DefaultAllocator::debug() = true;

    char stackMemory[1024];
    StackMemAllocator::config_and_init(stackMemory, 1024);

    d2ds::Vector<int, d2ds::DefaultAllocator> intVec;
    d2ds::Vector<char, StackMemAllocator> charVecByStack(10);
    d2ds::Vector<double> doubleVec = { 1.1, 2.2, 3.3 };

    d2ds_assert_eq(d2ds::DefaultAllocator::allocate_counter(), 1);

    D2DS_WAIT

    return 0;
}