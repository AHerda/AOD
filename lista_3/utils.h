#pragma once

#include <array>
#include <deque>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <vector>

struct Node {
  int u;
  int label;

  Node(int u, int label) : u(u), label(label) {}
};

struct radix_heap {
private:
    static const int bucket_count = sizeof(int) * 8 + 1;
    std::array<std::vector<Node>, bucket_count> buckets = {};
    std::array<int, bucket_count> bucket_minimum;
    int least = 0;
    int size = 0;

public:
    radix_heap() {
        bucket_minimum.fill(INT_MAX);
    }

    void insert(int u, int const label) {
        size += 1;
        int const bucket = find_bucket(label);
        buckets[bucket].push_back(Node(u, label));
        bucket_minimum[bucket] = std::min(bucket_minimum[bucket], label);
    }

    int extract() {
        size -= 1;
        pull();
        Node value = buckets[0].back();
        buckets[0].pop_back();
        return value.u;
    }

    int getsize() {
        return size;
    }

    private:
    void pull() {
        if(buckets[0].size() > 0) {
        return;
        }

        // Find non-empty bucket.
        int i = 1;
        while(buckets[i].size() == 0) {
        i += 1;
        }

        least = bucket_minimum[i];

        for(Node& v: buckets[i]) {
        int const bucket = find_bucket(v.label);
        buckets[bucket].push_back(v);
        bucket_minimum[bucket] = std::min(bucket_minimum[bucket], v.label);
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

/*struct Bucket_Queue {
private:
    std::vector<std::list<int>> buckets;
    int least_bucket = INT_MAX;
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

    int extract() {
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

    int size() const {
        return size;
    }
};
*/