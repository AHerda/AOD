#include <iostream>
#include <fstream>
#include <chrono>
#include "Hypercube.hpp"

auto stats() -> void
{
    std::ofstream file("wyniki/wyniki.csv", std::ios_base::out);
    file << "k;flow;time;aug_paths\n";

    for(int k = 1; k <= 16; k++) {
        int d = 10;
        long long time;
        long long flow;
        long long paths;
        for (int i = 0; i < d; i++) {
            std::cout << "powtórzenie " << k << " " << i << std::endl;
            time = 0;
            flow = 0;
            paths = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            Hypercube tmp = Hypercube(k);
            int p = -1;
            flow = tmp.maxFlow(0, pow(2, k) - 1, p);
            paths = p;
            auto t = std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::high_resolution_clock::now() - begin);
            time = t.count();

            file << k << ";" << flow << ";" << time << ";" << paths << "\n";
        }
    }
    file.close();
}

int main(int argc, char** argv) {
    int k;
    int meta;
    if (argc < 3) {
        std::cerr << "wrong number of arguments";
        return 1;
    }
    if (std::string(argv[1]) == "--size") {
        k = atoi(argv[2]);
        meta = int(pow(2,k) - 1);
    } else return 1;

    int numOfPaths = -1;
    auto begin = std::chrono::high_resolution_clock::now();

    Hypercube hypercube = Hypercube(k);
    std::cout << "Max Flow: " << hypercube.maxFlow(0, meta, numOfPaths) << '\n';
    auto t = std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::high_resolution_clock::now() - begin);

    std::cerr << "Execution Time: " << t.count() << " microseconds\n";
    std::cerr << "# Paths: " << numOfPaths << "\n";

    if (argc >= 4 && std::string(argv[3]) == "--printFlow")
        hypercube.printFlow();
    
    //stats();

    return 0;
}