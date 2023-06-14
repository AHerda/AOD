#include <iostream>
#include "graph.h"

int main(int argc, char *argv[]) {
    if (argc != 7) {
        std::cerr << "wrong number of arguments!";
        return -1;
    }

    std::string graphFile;
    std::string srcFile;
    std::string resFile;
    short mode;

    for (int i = 1; i < 7; i++) {
        std::cout << i << " " << std::string(argv[i]) << std::endl;
        if (std::string(argv[i]) == "-d") {
            graphFile = std::string(argv[i+1]);
        }
        else if (std::string(argv[i]) == "-ss") {
            srcFile = std::string(argv[i+1]);
            mode = 1;
        }
        else if (std::string(argv[i]) == "-p2p") {
            srcFile = std::string(argv[i+1]);
            mode = 2;
        }
        else if (std::string(argv[i]) == "-oss" || std::string(argv[i]) == "-op2p") {
            resFile = std::string(argv[i+1]);
        }
    }

    std::cout << "Wczytano dane\n";
    std::shared_ptr<Graph> g = generateGraph(graphFile);
    std::cout << "Wpisano graf\n";
    std::list<int> src = parseSources(srcFile, mode);
    std::cout << "Wpisano starty\n";
    std::ofstream file(resFile, std::ios::out);
    std::cout << "Wypissywanie danych\n";
    file << "f " << graphFile << ' ' << srcFile << "\ng " << g->V << ' ' << g->E << ' ' << g->minWeight << ' ' << g->maxWeight << "\n";
    std::cout << "Wypisano dane\n";
    int len = src.size();

    if (mode == 1) { //ss 
        long long time = 0;
        while (!src.empty()) {
            int s = src.front();
            std::cout << "s " << s << "\n";
            src.pop_front();
            auto start = std::chrono::high_resolution_clock::now();

            std::vector<long long> dist = g->radix(s);

            auto end = std::chrono::high_resolution_clock::now();
            auto time_temp =std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            time += time_temp.count();
        }
        time /= len;
        file << "t " << time / 1000 << "." << time % 1000;
    }
    else { //p2p
        std::vector<long long> dist;
        while (!src.empty()) {
            int a = src.front();
            src.pop_front();
            int b = src.front();
            dist = g->radix(a);
            file << "d " << a + 1 << ' ' << b + 1 << ' ' << dist[b] << '\n';
        }
    }
    file.close();
    return 0;
}