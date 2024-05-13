// vector.1.cpp - readonly
//
// 描述:
//  Vector自定义分配器支持
//
//      struct AllocatorInterface {
//          static void * allocate(int bytes);
//          static void deallocate(void *addr, int bytes);
//      };
//
// 目标/要求:
//  - 开发者能使用默认分配器, 也可以通过模板的第二个参数配置自定义的分配器
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

    char stackMemory[1024];
    StackMemAllocator::config_and_init(stackMemory, 1024);

    {
        int *intPtr = (int *) StackMemAllocator::allocate(sizeof(4));
        *intPtr = 1010;
        std::cout << intPtr << ": " << *intPtr << std::endl;
        StackMemAllocator::deallocate(intPtr, sizeof(intPtr));
    }

    d2ds::Vector<int, d2ds::DefaultAllocator> intVec;
    d2ds::Vector<char, StackMemAllocator> charVecByStack;
    d2ds::Vector<double> doubleVec;

    D2DS_WAIT

    return 0;
}