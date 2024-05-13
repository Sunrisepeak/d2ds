// vector.3.cpp - readonly
//
// 描述:
//  数据结构Vector的扩容和缓存机制
//    扩容/缩容机制: 二倍缩放 
//        扩容条件: mSize_e + 1 > mCapacity_e
//        缩容条件: mSize_e <= mCapacity_e / 3
//
// 目标/要求:
//  - 实现Vector的 capacity/push_back/pop_back/resize
//  - 在exercises/array/Vector.hpp中完成你的代码设计
//  - 通过编译器检测
//

#include "common/common.hpp"

#include <exercises/array/Vector.hpp>

int main() {

    d2ds::DefaultAllocator::debug() = false;

    { // push_back
        d2ds::Vector<int> intArr;
        intArr.push_back(1); d2ds_assert_eq(intArr[0], 1);
        d2ds_assert_eq(intArr.capacity(), 2);
        intArr.push_back(2); d2ds_assert_eq(intArr[1], 2);
        intArr.push_back(3); d2ds_assert_eq(intArr[2], 3);
        d2ds_assert_eq(intArr.size(), 3);
        d2ds_assert_eq(intArr.capacity(), 4);
        d2ds_assert_eq(intArr[1], 2);
    }

    D2DS_RETURN

    { // pop_back
        d2ds::Vector<int> intArr = { 1, 2, 3, 4 };
        intArr.push_back(5); d2ds_assert_eq(intArr[0], 1);
        intArr.pop_back();
        intArr.pop_back();
        d2ds_assert_eq(intArr.capacity(), 8);
        intArr.pop_back(); d2ds_assert_eq(intArr[intArr.size() - 1], 2);
        d2ds_assert_eq(intArr.size(), 2);
        d2ds_assert_eq(intArr.capacity(), 4);
    }

    D2DS_WAIT

    return 0;
}