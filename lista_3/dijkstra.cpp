#include "graph.h"

bool priority_compare(pii l, pii r) {
  return l.second > r.second;
}

std::vector<long long> Graph::dijkstra(int source) {
    std::vector<long long> dist(V + 1, LLONG_MAX);
    std::vector<char> visited(V + 1, false);

    std::priority_queue<pii, std::vector<pii>, bool (*)(pii l, pii r)> pq(priority_compare);
    pq.push(pii(source, 0));
    dist[source] = 0;

    while(!pq.empty()) {
        int u = pq.top().first;
        int cost = pq.top().second;
        pq.pop();

        if(visited[u] == true) continue;

        visited[u] == true;

        for(auto neighbor : this->adj[u]) {
            int v = neighbor.first;
            int w = neighbor.second;
            int new_cost = cost + w;

            if(new_cost < dist[v]) {
                dist[v] = new_cost;
                pq.push(pii(v, new_cost));
            }
        }
    }

    return std::move(dist);
}