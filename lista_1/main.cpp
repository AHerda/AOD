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
    //vector<Node> V;
    //vector<vector<Node>> E;

    void add_edge(int u, int v) {
        neighbors[u].push_back(v);
        if (directionality == UNDIRECTED) {
            neighbors[v].push_back(u);
        }
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

    void dfs(int start, bool tree) {
        vector<bool> visited(V + 1, false);
        stack<int> stos;
        stos.push(start);
        visited[start] = true;

        while(!stos.empty()) {
            int u = stos.top();
            stos.pop();

            if(tree) {
                cout << u << " ";
            }

            for(int v : neighbors[u]) {
                if(!visited[v]) {
                    visited[v] = true;
                    stos.push(v);
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

    vector<vector<int>> reverse() {
        vector<vector<int>> reversed_neighbors;

        for(int u = 1; u <= V; u++) {
            for(int v : neighbors[u]) {
                reversed_neighbors[v].push_back(u);
            }
        }

        return reversed_neighbors;
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
    graf.dfs(3, true);
}