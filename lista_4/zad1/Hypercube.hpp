#ifndef MAX_FLOW_HYPERCUBE_H
#define MAX_FLOW_HYPERCUBE_H
#include <vector>
#include <iostream>
#include <cmath>
#include "Edge.hpp"
#include "utils2.hpp"

class Hypercube {
private:
    int* level;
public:
    int k;
    int v; //num of nodes
    std::vector<std::vector<Edge*> > adj;

    explicit Hypercube(int k) {
        this->k = k;
        this->v = pow(2,k);
        this->adj = std::vector<std::vector<Edge*> >(v);
        this->level = new int[v]; //!
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
    int EdmondsKarp(int s, int t);
    int maxFlow(int s, int t, int&paths);
    void printFlow();
    int DinicMaxflow(int s, int t, int& p);
    bool BFS(int s, int t);
    int sendFlow(int u, int flow, int t, int start[]);
};

#endif //MAX_FLOW_HYPERCUBE_H