#ifndef MAX_FLOW_HYPERCUBE_H
#define MAX_FLOW_HYPERCUBE_H
#include <vector>
#include <iostream>
#include <cmath>
#include "Edge.hpp"
#include "utils.hpp"

class Hypercube {
private:
    int* level;
public:
    int k;
    int v; //num of nodes
    std::vector<std::vector<Edge*> > adj;

    Hypercube(int k) {
        this->k = k;
        this->v = pow(2,k);
        this->adj = std::vector<std::vector<Edge*> >(v);
        this->level = new int[v];
        for (int i = 0; i < v; i++) {
            for (int cur = i + 1; cur < v; cur++) {
                if (isPowerOfTwo(i ^ cur) == 1) {
                    Edge* tmp = new Edge(i, cur, k);
                    tmp->rev = new Edge(cur, i, k);
                    adj[i].push_back(tmp);
                }
            }
        }
    }
    auto EdmondsKarp(int source, int sink) -> int;
    auto maxFlow(int source, int sink, int&paths) -> int;
    auto printFlow() -> void;
    auto DinicMaxflow(int source, int sink, int& p) -> int;
    auto BFS(int source, int sink) -> bool;
    auto sendFlow(int u, int flow, int sink, int start[]) -> int;
};

#endif