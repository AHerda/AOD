#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

enum Directionality {
    DIRECTED,
    UNDIRECTED
};

// Struktura reprezentująca wierzchołek grafu
struct Node {
    int id;                     // Identyfikator wierzchołka
    vector<Node*> neighbors;    // Lista sąsiadów wierzchołka
    bool visited;               // Flaga, czy wierzchołek był już odwiedzony
    int parent;                 // Identyfikator rodzica wierzchołka w drzewie przeszukiwania
};

class Graph {
    Directionality directionality;
    int V;
    int E;
    vector<vector<int>> neighbors;
    vector<vector<int>> reverse_neighbors;

    void add_edge(int u, int v) {
        neighbors[u].push_back(v);
        if (directionality == UNDIRECTED) {
            neighbors[v].push_back(u);
        }
    }

    vector<vector<int>> reverse() {
        vector<vector<int>> reversed_neighbors;

        for(int u = 1; u <= V; u++) {
            for(int v : neighbors[u]) {
                reversed_neighbors[v].push_back(u);
            }
        }

        return reversed_neighbors;
    }

    public:

    Graph(string filename) {
        ifstream myfile(filename);

        char flag;
        myfile >> flag;
        directionality = (flag == 'D') ? DIRECTED : UNDIRECTED;
        neighbors.resize(V + 1);
        myfile >> V;
        myfile >> E;

        for(int i = 0; i < E; i++) {
            int u, v;
            myfile >> u >> v;
            add_edge(u, v);
        }

        reverse_neighbors = reverse();

        myfile.close();
    }

    void bfs(int start, bool tree) {
        vector<bool> visited(V + 1, false);
        queue<int> que;
        que.push(start);
        visited[start] = true;

        while(!que.empty()) {
            int u = que.front();
            que.pop();

            if(tree) {
                cout << u << " ";
            }

            for(int v : neighbors[u]) {
                if(!visited[v]) {
                    visited[v] = true;
                    que.push(v);
                }
            }
        }

        cout << endl;
    }

    void dfs(int start, bool tree, vector<int>& component, vector<bool>& visited_global, bool reverse = false) {
        vector<bool> visited(V + 1, false);
        stack<int> stos;
        
        stos.push(start);
        
        visited[start] = true;
        if(!visited_global.empty()) {
            visited_global[start] = true;
        }
        component.push_back(start);

        while(!stos.empty()) {
            int u = stos.top();
            stos.pop();

            if(tree) {
                cout << u << " ";
            }

            if(!reverse) {
                for(int v : neighbors[u]) {
                    if(!visited[v]) {
                        visited[v] = true;
                        if(!visited_global.empty()) {
                            visited_global[v] = true;
                        }
                    
                        stos.push(v);

                        if(!component.empty()) {
                            component.push_back(v);
                        }
                    }
                }
            }
            else {
                for(int v : reverse_neighbors[u]) {
                    if(!visited[v]) {
                        visited[v] = true;
                        if(!visited_global.empty()) {
                            visited_global[v] = true;
                        }
                    
                        stos.push(v);

                        if(!component.empty()) {
                            component.push_back(v);
                        }
                    }
                }
            }
        }

        cout << endl;
    }

    bool topological_sort() {
        vector<int> results;
        vector<int> E_in(V + 1, 0);

        for(int u = 1; u <= V; u++) {
            for(int v : neighbors[u]) {
                E_in[v]++;
            }
        }

        queue<int> que;

        for(int u = 1; u <= V; u++) {
            if(E_in[u] == 0) {
                que.push(u);
            }
        }

        while(!que.empty()) {
            int u = que.front();
            que.pop();
            results.push_back(u);

            for(int v : neighbors[u]) {
                E_in[v]--;
                if(E_in[v] == 0) {
                    que.push(v);
                }
            }
        }

        if(V <= 200) {
            for(int i = 0; i < results.size(); i++) {
                cout << results[i];

                if(i + 1 != results.size()) {
                    cout << " ";
                }

                cout << endl;
            }
        }

        return (results.size() != V);
    }

    void strong_connect() {
        vector<bool> visited(V + 1, false);
        vector<vector<int>> components;
        stack<int> s;

        for(int u = 1; u <= V; u++) {
            if(!visited[u]) {
                vector<int> component;
                dfs(u, false, component, visited);
                for(int v : component) {
                    s.push(v);
                }
            }
        }

        visited.assign(V + 1, false);

        while(!s.empty()) {
            int u = s.top();
            s.pop();

            if(!visited[u]) {
                vector<int> component;
                dfs(u, false, component, visited, true);
                components.push_back(component);
            }
        }

        cout << "Liczba silnie spójnych składowych: " << components.size() << endl;
        for (vector<int>& component : components) {
            cout << "Liczba wierzchołków w składowej: " << component.size() << endl;
            if (V <= 200) {
                cout << "Wierzchołki składowej: ";
                for (int u : component) {
                    cout << u << " ";
                }
                cout << endl;
            }
        }
    }

    void print_graph() {
        cout << "Liczba wierzchołków: " << V << endl;
        cout << "Liczba krawędzi: " << E << endl;
        cout << "Skierowanie: " << (directionality == DIRECTED ? "TAK" : "NIE") << endl;
        cout << "Lista sąsiedztwa:" << endl;

        for (int u = 1; u <= V; u++) {
            cout << u << ": ";
            for (int v : neighbors[u]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

int main(int argc, char** argv) {
    Graph graf("./resources/aod_testy1/4/u4a-2.txt");
    vector<int> maciek;
    vector<bool> maciek2;
    graf.dfs(3, true, maciek, maciek2);
}