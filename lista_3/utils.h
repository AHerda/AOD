#pragma once

#include <array>
#include <list>
#include <deque>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <vector>

typedef std::pair<int, int> pii;
typedef std::pair<int, long long> pill;

struct radix_heap {
private:
    static const int bucket_count = sizeof(int) * 8 + 1;
    std::array<std::vector<pill>, bucket_count> buckets = {};
    std::array<long long, bucket_count> bucket_minimum;
    int least = 0;
    int size = 0;

public:
    radix_heap() {
        bucket_minimum.fill(INT_MAX);
    }

    void insert(int u, long long const cost) {
        size += 1;
        int const bucket = find_bucket(cost);
        buckets[bucket].push_back(pill(u, cost));
        bucket_minimum[bucket] = std::min(bucket_minimum[bucket], cost);
    }

    int pop() {
        size -= 1;
        pull();
        pii value = buckets[0].back();
        buckets[0].pop_back();
        return value.first;
    }

    int get_size() {
        return size;
    }

    private:
    void pull() {
        if(buckets[0].size() > 0) return;

        int i = 1;
        while(buckets[i].size() == 0) i += 1;

        least = bucket_minimum[i];

        for(pill& v: buckets[i]) {
            int const bucket = find_bucket(v.second);
            buckets[bucket].push_back(v);
            bucket_minimum[bucket] = std::min(bucket_minimum[bucket], v.second);
        }
        buckets[i].clear();
        bucket_minimum[i] = INT_MAX;
    }

    int find_bucket(int const value) {
        const int bits = sizeof(int) * 8;
        int const zeros = __builtin_clz(value ^ least);
        return value == least ? 0 : bits - zeros;
    }
};

struct bucket_queue {
private:
    std::vector<std::list<long long>> buckets;
    long long least_bucket = LLONG_MAX;
    int size = 0;

public:
    void insert(int const v, int const distance) {
        if(buckets.size() <= distance) {
        buckets.resize(distance + 1);
        }

        buckets[distance].push_back(v);
        if(distance < least_bucket) {
        least_bucket = distance;
        }
        size += 1;
    }

    int pop() {
        if(buckets[least_bucket].size() == 0) {
            while(buckets[least_bucket].size() == 0) {
                least_bucket += 1;
            }
        }

        int v = buckets[least_bucket].front();
        buckets[least_bucket].pop_front();
        size -= 1;
        return v;
    }

    int get_size() const {
        return size;
    }
};