#ifndef MAX_FLOW_UTILS_H
#define MAX_FLOW_UTILS_H

static bool isPowerOfTwo(int x) {
    return x && (!(x & (x - 1)));
}

static int hammingWeight(int n) {
    int count = 0;
    while(n != 0){
        count += (n%2);
        n >>= 1;
    }
    return count;
}

#endif //MAX_FLOW_UTILS_H