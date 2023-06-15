#pragma once

#include "utils.h"

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
#include <chrono>
#include <memory>

class Graph {
public:
    std::list<pii> *adj; //adjacency list
    int V;
    int maxWeight;
    int minWeight;
    int E;
    
    Graph(int T);
    void addEdge(int u, int v, int w);
    ~Graph();
    void print_graph();

    // DIJKSTRA
    std::vector<long long> dijkstra(int source);
    std::vector<long long> dial(int source);
    std::vector<long long> radix(int source);
};

std::shared_ptr<Graph> generateGraph(const std::string& path);
std::list<int> parseSources(const std::string& path, short mode);