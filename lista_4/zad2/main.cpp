#include "graph.hpp"

#include <iostream>
#include <chrono>
#include <fstream>

auto stats() -> void
{
    std::ofstream file("wyniki/wyniki.csv", std::ios_base::out);
    file << "k;i;size;time\n";
    for(int k = 3; k <= 10; k++) {
        for(int i = 1; i <= k; i++) {
            for(int j = 0; j < 1000; j++) {
                std::cout << "powtórzenie " << k << " " << i << " " << j << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
    
                std::vector<Edge> graph = generateGraph(k, i);
                std::vector<Edge> matching = findMaximumMatching(graph);
            
                auto end = std::chrono::high_resolution_clock::now();
                auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

                file << k << ";" << i << ";" << matching.size() << ";" << time.count() << "\n";
            }
        }
    }
    file.close();
}
 
int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        std::cerr << "Usage: program --size k --degree i [--printMatching]" << std::endl;
        return 1;
    }
 
    int k = std::atoi(argv[2]);
    int i = std::stoi(argv[4]);
    bool printMatching = false;
 
    if (k < 1 || k > 16 || i > k)
    {
        std::cerr << "Error: Invalid value for --size or --degree. Value k must be between 1 and 16. Value i must be smaller or equal to k" << std::endl;
        return 1;
    }
 
    if (argc >= 6 && std::string(argv[5]) == "--printMatching")
    {
        printMatching = true;
    }
 
    auto start = std::chrono::high_resolution_clock::now();
 
    std::vector<Edge> graph = generateGraph(k, i);
    std::vector<Edge> matching = findMaximumMatching(graph);
 
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
 
    std::cout << "Maximum Matching Size: " << matching.size() << std::endl;
    std::cerr << "Execution Time: " << duration.count() << " microseconds" << std::endl;
 
    if (printMatching)
    {
        std::cout << "Matching Edges:" << std::endl;
        for (const auto &edge : matching)
        {
            std::cout << edge.vertexOne << " - " << edge.vertexTwo << std::endl;
        }
    }

    stats();
 
    return 0;
}