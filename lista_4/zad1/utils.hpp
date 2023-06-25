#ifndef utils_hpp
#define utils_hpp

#include <memory>
#include <limits.h>
#include <algorithm>
#include <random>

std::random_device rd;
std::mt19937 mt(rd());

auto H1(int x) -> int
{
    return __builtin_popcount(x);
}

auto Z1(int x) -> int
{
    return __builtin_popcount(~x);
}

auto gen_u_ij(int i, int j) -> int
{
    int l = std::max(std::max(H1(i), H1(j)), std::max(Z1(i), Z1(j)));
    std::uniform_int_distribution<> gen(1, pow(2, l));

    return gen(mt);
}

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

#endif