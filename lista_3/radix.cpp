#include "graph.h"

std::vector<long long> Graph::radix(int source){
    std::vector<long long> dist(V + 1, LLONG_MAX);
    std::vector<char> visited(V + 1, false);
    dist[source] = 0;

    int max_weight = this->maxWeight;

    radix_heap rh;
    rh.insert(source, 0);

    while(rh.getsize() > 0) {
        int u = rh.extract();
        if(visited[u] == true) continue;

        visited[u] = true;
        long long cost = dist[u];

        for(auto neighbor : this->adj[u]) {
            int v = neighbor.first;
            int w = neighbor.second;

            int new_cost = cost + w;
            if(new_cost < dist[v]) {
                dist[v] = new_cost;
                rh.insert(v, new_cost);
            }
        }
    }
    return std::move(dist);
}