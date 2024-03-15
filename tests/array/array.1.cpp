#include <exercises/array/Array.hpp>

int main() {
    d2ds::Array<int, 5> intArr;

    intArr[2] = 1;
    assert(intArr[2] == 1);

    return 0;
}