#include <algorithm>
#include <random>
#include "Edge.hpp"

void Edge::setCapacity() {
    int sWeight = hammingWeight(s);
    int tWeight = hammingWeight(t);
    const int l = std::max(std::max(sWeight, k - sWeight), std::max(tWeight, k - tWeight));
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, pow(2, l));
    this->capacity = floor(dist(mt));
}