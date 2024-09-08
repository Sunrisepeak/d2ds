#ifndef DSLINGS_HPP_D2DS
#define DSLINGS_HPP_D2DS

namespace d2ds {
// show your code



class MaxValue {
public:
    MaxValue(int val) {
        mMaxVal_e = val;
    }

    int get() {
        return mMaxVal_e;
    }

    void set(int val) {
        if (val > mMaxVal_e) {
            mMaxVal_e = val;
        }
    }

private:
    int mMaxVal_e;
};

}

#endif