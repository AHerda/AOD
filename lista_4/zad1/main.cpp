#include <iostream>
#include <fstream>
#include <chrono>
#include "Hypercube.hpp"

void stats(const int k, const int meta) {
    int d = 20;
    long long time = 0;
    long long flow = 0;
    long long paths = 0;
    for (int i = 0; i < d; i++) {
        auto begin = std::chrono::high_resolution_clock::now();
        Hypercube tmp = Hypercube(k);
        int p = -1;
        flow += tmp.maxFlow(0, meta, p);
        //flow += tmp.DinicMaxflow(0, meta, p);
        paths += p;
        auto t = std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::high_resolution_clock::now() - begin);
        time += t.count();
    }
    std::cout << "flow, time, paths:\n";
    std::cout << flow/d << ' ' << time/d << ' ' << paths/d;
}

int main(int argc, char** argv) {
    int k;
    int meta;
    if (argc < 3) {
        std::cerr << "wrong number of arguments";
        return 1;
    }
    if (std::string(argv[1]) == "-size") {
        k = atoi(argv[2]);
        meta = int(pow(2,k) - 1);
    } else return 1;

    int numOfPaths = -1;
    auto begin = std::chrono::high_resolution_clock::now();

    Hypercube hypercube = Hypercube(k);
    std::cout << "max flow: " << hypercube.maxFlow(0, meta, numOfPaths) << '\n';
    auto t = std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::high_resolution_clock::now() - begin);

    std::cerr << "t = " << t.count() << " µs\n";
    std::cerr << "number of paths found: " << numOfPaths << "\n";

    if (argc >= 4 && std::string(argv[3]) == "-printFlow")
        hypercube.printFlow();

    return 0;
}