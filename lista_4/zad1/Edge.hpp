#ifndef MAX_FLOW_EDGE_H
#define MAX_FLOW_EDGE_H
#include "utils2.hpp"

class Edge {
public:
    int k;
    int s; //source
    int t; //sink
    int flow;
    int capacity;
    Edge* rev;
    Edge(int source, int sink, int k) {
        this->s = source;
        this->t = sink;
        this->k = k;
        setCapacity();
        this->flow = 0;
    }
    ~Edge() {
    }
    void setCapacity();
};

#endif //MAX_FLOW_EDGE_H