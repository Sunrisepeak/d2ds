#ifndef __ARRAY_HPP__D2DS
#define __ARRAY_HPP__D2DS

#include <DStruct/dstruct.hpp>

namespace d2ds {

template<typename T, size_t N>
using Array = dstruct::Array<T, N>;

}

#endif