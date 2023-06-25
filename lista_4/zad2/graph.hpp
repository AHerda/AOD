#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <string>

struct Edge
{
    int vertexOne, vertexTwo;
 
    Edge(int u, int v) : vertexOne(u), vertexTwo(v) {}
};
 
auto generateGraph(int k, int i) -> std::vector<Edge>
{
    std::vector<int> v1(pow(2, k));
    std::vector<int> v2(pow(2, k));
    std::iota(v1.begin(), v1.end(), 1);
    std::iota(v2.begin(), v2.end(), 2 * k + 1);
 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(v2.begin(), v2.end(), gen);
 
    std::vector<Edge> edges;
    for (int j = 0; j < pow(2, k); j++)
    {
        for (int l = 0; l < i; l++)
        {
            edges.emplace_back(v1[j], v2[(j + l) % int(pow(2, k))]);
        }
    }
    return edges;
}
 
auto findMaximumMatching(const std::vector<Edge> &graph) -> std::vector<Edge>
{
    std::vector<Edge> matching;
    std::vector<bool> used(graph.size(), false);
 
    for (const auto &edge : graph)
    {
        if (!used[edge.vertexOne] && !used[edge.vertexTwo])
        {
            used[edge.vertexOne] = true;
            used[edge.vertexTwo] = true;
            matching.push_back(edge);
        }
    }
 
    return matching;
}