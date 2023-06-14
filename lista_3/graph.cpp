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

std::shared_ptr<Graph> generateGraph(const std::string& path) {
    std::ifstream ifs = std::ifstream(path, std::ios_base::in);
    std::string data;
    std::shared_ptr<Graph> g;

    while (getline(ifs, data)) {
        char* p;
        char* line = new char[data.length() + 1];
        strcpy(line, data.c_str());
        p = strtok(line, " ");

        if (strcmp(p, "p") == 0) {
            p = strtok(NULL, " ");
            p = strtok(NULL, " ");
            g = std::make_shared<Graph>(atoi(p));
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
                src.push_back(atoi(p));
            }
        }
        else if (mode == 2) { //p2p
            if (std::string(p) == "q") {
                p = strtok(NULL, " ");
                src.push_back(atoi(p));
                p = strtok(NULL, " ");
                src.push_back(atoi(p));
            }
        }
        delete[] line;
    }
    ifs.close();
    return src;
}