#ifndef graph_h
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <limits.h>
#include <queue>
#include <chrono>


typedef std::pair<int, int> pii;

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
    int dijkstra_1(int source);
};

Graph* generateGraph(const std::string& path);
std::list<int> parseSources(const std::string& path, short mode);

#endif