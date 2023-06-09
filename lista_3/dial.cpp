#include "graph.h"

std::vector<long long> Graph::dial(int source) {
    std::vector<long long> dist(V + 1, LLONG_MAX);
    std::vector<char> visited(V + 1, false);

    dist[source] = 0;

    bucket_queue bq;
    bq.insert(source, 0);

    while(bq.get_size() > 0) {
        int u = bq.pop();

        if(visited[u] == true) continue;

        visited[u] = true;
        long long cost = dist[u];

        for(auto neighbor : this->adj[u]) {
            int v = neighbor.first;
            int w = neighbor.second;

            long long new_cost = cost + w;

            if(new_cost < dist[v]) {
                dist[v] = new_cost;
                bq.insert(v, new_cost);
            }
        }
    }

    
    return std::move(dist);
}