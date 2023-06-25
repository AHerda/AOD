#ifndef MAX_FLOW_EDGE_H
#define MAX_FLOW_EDGE_H
#include "utils.hpp"

class Edge {
public:
    int k;
    int source;
    int sink;
    int flow;
    int capacity;
    Edge* rev;
    Edge(int source, int sink, int k) {
        this->source = source;
        this->sink = sink;
        this->k = k;
        setCapacity();
        this->flow = 0;
    }
    ~Edge() {
    }
    auto setCapacity() -> void;
};

#endif