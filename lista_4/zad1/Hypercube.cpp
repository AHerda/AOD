#include "Hypercube.hpp"
#include <queue>
#include <algorithm>
#include <list>
#include <limits.h>

auto Hypercube::EdmondsKarp(int source, int sink) -> int
{
    std::vector<Edge*> pred(v, nullptr);
    int flow = 0;
    do {
        std::queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (Edge* e : adj[cur]) {
                if (pred[e->sink] == nullptr && e->sink != source && e->capacity > e->flow) {
                    pred[e->sink] = e;
                    q.push(e->sink);
                }
            }
        }
        if (pred[sink] != nullptr) {
            int df = INT_MAX;
            for (auto e = pred[sink]; e != nullptr; e = pred[e->source]) {
                df = std::min(df, e->capacity - e->flow);
            }
            for (auto e = pred[sink]; e != nullptr; e = pred[e->source]) {
                e->flow += df;
                e->rev->flow -= df;
            }
            flow += df;
        }
        else break;
    } while (pred[sink] == nullptr);
    return flow;
}

auto Hypercube::maxFlow(int source, int sink, int& paths) -> int
{
    int result = 0;
    int temp;
    do {
        temp = EdmondsKarp(source, sink);
        result += temp;
        paths++;
    } while (temp != 0);
    return result;
}

auto Hypercube::printFlow() -> void{
    for (auto i : adj) {
        for (auto edge : i) {
            if (edge->flow != 0)
                std::cout << edge->source << " -> " << edge->sink << ": " << edge->flow << "\n";
        }
    }
}

auto Hypercube::DinicMaxflow(int source, int sink, int& p) -> int
{
    if (source == sink)
        return -1;
    int maxFlow = 0;
    p = 0;

    while (BFS(source, sink)) {
        int* start = new int[v + 1]{ 0 };
        while (int flow = sendFlow(source, INT_MAX, sink, start)) {
            maxFlow += flow;
            p++;
        }
        delete[] start;
    }
    return maxFlow;
}

auto Hypercube::BFS(int source, int sink) -> bool
{
    for (int i = 0; i < v; i++)
        level[i] = -1;

    level[source] = 0;
    std::list<int> q;
    q.push_back(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (auto i = adj[u].begin(); i != adj[u].end(); i++) {
            Edge* e = *i;
            if (level[e->sink] < 0 && e->flow < e->capacity) {
                level[e->sink] = level[u] + 1;
                q.push_back(e->sink);
            }
        }
    }
    return level[sink] >= 0;
}

auto Hypercube::sendFlow(int u, int flow, int sink, int start[]) -> int
{
    if (u == sink)
        return flow;

    for (; start[u] < adj[u].size(); start[u]++) {
        Edge* e = adj[u][start[u]];

        if (level[e->sink] == level[u] + 1 && e->flow < e->capacity) {
            // find minimum flow from u to t
            int curr_flow = std::min(flow, e->capacity - e->flow);
            int temp_flow = sendFlow(e->sink, curr_flow, sink, start);

            if (temp_flow > 0) {
                e->flow += temp_flow;
                e->rev->flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}