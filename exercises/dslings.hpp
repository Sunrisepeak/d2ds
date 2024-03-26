#ifndef __DSLINGS_HPP__D2DS
#define __DSLINGS_HPP__D2DS

namespace d2ds {
// show your code






class MaxValue {
public:
    MaxValue(int val) {
        __mVal = val;
    }

    int get() {
        return __mVal;
    }

    void set(int val) {
        if (val > __mVal)
            __mVal = val;
    }

private:
    int __mVal;
};



}

#endif