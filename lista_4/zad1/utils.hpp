#ifndef MAX_FLOW_UTILS_H
#define MAX_FLOW_UTILS_H

static bool isPowerOfTwo(int x) {
    return x && (!(x & (x - 1)));
}

static int H(int n) {
    return __builtin_popcount(n);
}

#endif //MAX_FLOW_UTILS_H