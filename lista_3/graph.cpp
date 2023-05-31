#include "graph.h"

Graph::Graph(int V) {
    this->V = V;
    this->adj = new std::list< std::pair<int,int> >[V + 1];
    this->maxWeight = 0; 
    this->minWeight = INT_MAX;
}

void Graph::addEdge(int u, int v, int w) {
    this->adj[u].emplace_back(v, w);
    if (w > maxWeight) 
        maxWeight = w;
    else if (w < minWeight)
        minWeight = w;
}

Graph::~Graph() {
    delete adj;
}

void Graph::print_graph() {
    std::cout << "Liczba wierzcholkow: " << V << std::endl;
    std::cout << "Liczba krawedzi: " << E << std::endl;
    std::cout << "Lista sasiedztwa:" << std::endl;

    for (int u = 0; u <= V; u++) {
        std::cout << u << ": ";
        for (pii v : this->adj[u]) {
            std::cout << v.first << "(" << v.second << ") ";
        }
        std::cout << std::endl;
    }

    std::cout << "Największy koszt: " << maxWeight << std::endl;
    std::cout << "Najmniejszy koszt: " << minWeight << std::endl;
}

Graph* generateGraph(const std::string& path) {
    std::ifstream ifs = std::ifstream(path, std::ios_base::in);
    std::string data;
    Graph *g;

    while (getline(ifs, data)) {
        char* p;
        char* line = new char[data.length() + 1];
        strcpy(line, data.c_str());
        p = strtok(line, " ");

        if (strcmp(p, "p") == 0) {
            p = strtok(NULL, " ");
            p = strtok(NULL, " ");
            g = new Graph(atoi(p));
            p = strtok(NULL, " ");
            g->E = atoi(p);
        }

        else if (strcmp(p, "a") == 0) {
            p = strtok(NULL, " ");
            int a = atoi(p);
            p = strtok(NULL, " ");
            int b = atoi(p);
            p = strtok(NULL, " ");
            int weight = atoi(p);
            g->addEdge(a, b, weight);
        }
        delete[] line;
    }
    ifs.close();
    return g;
}

std::list<int> parseSources(const std::string& path, short mode) {
    std::ifstream ifs = std::ifstream(path, std::ios_base::in);
    std::string data;
    std::list<int> src;
    
    while (getline(ifs, data)) {
        char* p;
        char* line = new char[data.length() + 1];
        strcpy(line, data.c_str());
        p = strtok(line, " ");

        if (mode == 1) { //sp
            if (std::string(p) == "s") {
                p = strtok(NULL, " ");
                src.push_back(atoi(p) - 1);
            }
        }
        else if (mode == 2) { //p2p
            if (std::string(p) == "q") {
                p = strtok(NULL, " ");
                src.push_back(atoi(p) - 1);
                p = strtok(NULL, " ");
                src.push_back(atoi(p) - 1);
            }
        }
        delete[] line;
    }
    ifs.close();
    return src;
}





// GŁÓWNE ALGORYTMY

int Graph::dijkstra_1(int source) {
    std::vector<int> dist(V + 1, INT_MAX);
    int time = 0;
    int time_counter;

    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({source, 0});

    auto start = std::chrono::high_resolution_clock::now();
    while(!pq.empty()) {
        int u = pq.top().first;
        int cost = pq.top().second;
        pq.pop();

        for(auto neighbor : this->adj[u]) {
            int v = neighbor.first;
            int w = neighbor.second;
            int new_cost = cost + w;

            if(new_cost < dist[v]) {
                dist[v] = new_cost;
                pq.push({v, new_cost});

                auto end = std::chrono::high_resolution_clock::now();
                time += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                time_counter++;
            }
        }
    }

    return time / time_counter;
}