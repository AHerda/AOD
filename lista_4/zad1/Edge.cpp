#include <algorithm>
#include <random>
#include <time.h>
#include "Edge.hpp"

auto Edge::setCapacity() -> void
{
    int source_w = H(source);
    int sink_w = H(sink);
    const int l = std::max(std::max(source_w, k - source_w), std::max(sink_w, k - sink_w));
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, pow(2, l));
    this->capacity = floor(dist(mt));
}