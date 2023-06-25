#include "Hypercube.hpp"
#include <queue>
#include <algorithm>
#include <list>
#include <limits.h>

int Hypercube::EdmondsKarp(int s, int t) {
    std::vector<Edge*> pred(v, nullptr);
    int flow = 0;
    do {
        std::queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (Edge* e : adj[cur]) {
                if (pred[e->t] == nullptr && e->t != s && e->capacity > e->flow) {
                    pred[e->t] = e;
                    q.push(e->t);
                }
            }
        }
        if (pred[t] != nullptr) {
            int df = INT_MAX;
            for (auto e = pred[t]; e != nullptr; e = pred[e->s]) {
                df = std::min(df, e->capacity - e->flow);
            }
            for (auto e = pred[t]; e != nullptr; e = pred[e->s]) {
                e->flow += df;
                e->rev->flow -= df;
            }
            flow += df;
        }
        else break;
    } while (pred[t] == nullptr);
    return flow;
}

int Hypercube::maxFlow(int s, int t, int& paths) {
    int ans = 0;
    int a;
    do {
        a = EdmondsKarp(s, t);
        ans += a;
        paths++;
    } while (a != 0);
    return ans;
}

void Hypercube::printFlow() {
    for (auto i : adj) {
        for (auto edge : i) {
            if (edge->flow != 0)
                std::cout << edge->s << " -> " << edge->t << ": " << edge->flow << "\n";
        }
    }
}

int Hypercube::DinicMaxflow(int s, int t, int& p) {
    if (s == t)
        return -1;
    int maxFlow = 0;
    p = 0;

    while (BFS(s, t)) {
        int* start = new int[v + 1]{ 0 };
        while (int flow = sendFlow(s, INT_MAX, t, start)) {
            maxFlow += flow;
            p++;
        }
        delete[] start;
    }
    return maxFlow;
}

bool Hypercube::BFS(int s, int t) {
    for (int i = 0; i < v; i++)
        level[i] = -1;

    level[s] = 0;
    std::list<int> q;
    q.push_back(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (auto i = adj[u].begin(); i != adj[u].end(); i++) {
            Edge* e = *i;
            if (level[e->t] < 0 && e->flow < e->capacity) {
                level[e->t] = level[u] + 1;
                q.push_back(e->t);
            }
        }
    }
    return level[t] >= 0;
}

int Hypercube::sendFlow(int u, int flow, int t, int start[]) {
    if (u == t)
        return flow;

    for (; start[u] < adj[u].size(); start[u]++) {
        Edge* e = adj[u][start[u]];

        if (level[e->t] == level[u] + 1 && e->flow < e->capacity) {
            // find minimum flow from u to t
            int curr_flow = std::min(flow, e->capacity - e->flow);
            int temp_flow = sendFlow(e->t, curr_flow, t, start);

            if (temp_flow > 0) {
                e->flow += temp_flow;
                e->rev->flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}