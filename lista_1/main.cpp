#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

enum Directionality {
    DIRECTED,
    UNDIRECTED
};

class Graph {
    Directionality directionality;
    int V;
    int E;
    vector<vector<int>> neighbors;
    vector<vector<int>> reverse_neighbors;

    void add_edge(int u, int v) {
        neighbors[u].push_back(v);
        reverse_neighbors[v].push_back(u);
        if (directionality == UNDIRECTED) {
            neighbors[v].push_back(u);
            reverse_neighbors[u].push_back(v);
        }
    }

    public:
    
    Graph(string filename) {
        ifstream myfile(filename);

        char flag;
        myfile >> flag;
        directionality = (flag == 'D') ? DIRECTED : UNDIRECTED;
        myfile >> V;
        myfile >> E;

        neighbors.assign(V + 1, vector<int>());
        reverse_neighbors.assign(V + 1, vector<int>());

        int u, v;
        for(int i = 0; i < E; i++) {
            myfile >> u >> v;
            add_edge(u, v);
        }

        myfile.close();
    }

    void bfs(int start, bool tree) {
        vector<int> visited;
        visited.assign(V + 1, 0);
        queue<int> que;
        que.push(start);
        visited[start] = 1;

        while(!que.empty()) {
            int u = que.front();
            que.pop();

            if(tree) {
                cout << u << " ";
            }

            for(int v : neighbors[u]) {
                if(visited[v] == 0) {
                    visited[v] = 1;
                    que.push(v);
                }
            }
        }

        cout << endl;
    }

    void dfs(int start, bool tree) {
        vector<int> visited;
        visited.assign(V + 1, 0);
        stack<int> st;
        st.push(start);
        visited[start] = 1;

        while(!st.empty()) {
            int u = st.top();
            st.pop();

            if(tree) {
                cout << u << " ";
            }

            for(int v : neighbors[u]) {
                if(visited[v] == 0) {
                    visited[v] = 1;
                    st.push(v);
                }
            }
        }

        cout << endl;
    }

    /*void dfs(int start, bool tree, vector<int> component, vector<int> visited_global, bool reverse = false) {
        vector<int> visited;
        visited.fill(V + 1, 0);
        vector<int> stos;
        
        stos.push_back(start);
        
        visited.set(start, 1);
        if(!visited_global.isEmpty()) {
            visited_global.set(start, 1);
        }
        component.push_back(start);

        while(!stos.isEmpty()) {
            int u = stos.array[stos.getSize() - 1];
            stos.pop_back();

            if(tree) {
                cout << u << " ";
            }

            if(!reverse) {
                for(int i = 0; i < neighbors.array[u].getSize(); i++) {
                    if(visited.array[neighbors.array[u].array[i]] == 0) {
                        visited.set(neighbors.array[u].array[i], 1);
                        if(!visited_global.isEmpty()) {
                            visited_global.set(neighbors.array[u].array[i], 1);
                        }
                    
                        stos.push_back(neighbors.array[u].array[i]);

                        if(!component.isEmpty()) {
                            component.push_back(neighbors.array[u].array[i]);
                        }
                    }
                }
            }
            else {
                for(int i = 0; i < reverse_neighbors.array[u].getSize(); i++) {
                    if(visited.array[reverse_neighbors.array[u].array[i]] == 0) {
                        visited.set(neighbors.array[u].array[i], 1);
                        if(!visited_global.isEmpty()) {
                            visited_global.set(neighbors.array[u].array[i], 1);
                        }
                    
                        stos.push_back(neighbors.array[u].array[i]);

                        if(!component.isEmpty()) {
                            component.push_back(neighbors.array[u].array[i]);
                        }
                    }
                }
            }
        }

        cout << endl;
    }*/

    bool topological_sort() {
        vector<int> results;
        vector<int> E_in;
        E_in.assign(V + 1, 0);

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
            for(int u : results) {
                cout << u << " ";
            }
            cout << endl;
        }

        return (results.size() != V);
    }

    /*void strong_connect() {
        vector<int> visited;
        visited.fill(V + 1, 0);
        vector<vector<int>> components;
        vector<int> stos;

        for(int u = 1; u <= V; u++) {
            if(visited.array[u] == 0) {
                vector<int> component;
                dfs(u, false, component, visited);
                for(int i = 0; i < component.getSize(); i++) {
                    stos.push_back(component.array[i]);
                }
            }
        }

        vector<int> visited2;
        visited2.fill(V + 1, 0);

        while(!stos.isEmpty()) {
            int u = stos.array[stos.getSize() - 1];
            stos.pop_back();

            if(visited2.array[u] == 0) {
                vector<int> component;
                dfs(u, false, component, visited, true);
                components.push_back(component);
            }
        }

        cout << "Liczba silnie spójnych składowych: " << components.getSize() << endl;
        for (int i = 0; i < components.getSize(); i++) {
            cout << "Liczba wierzchołków w składowej: " << components.array[i].getSize() << endl;
            if (V <= 200) {
                cout << "Wierzchołki składowej: ";
                for (int j = 0; j < components.array[i].getSize(); j++) {
                    cout << components.array[i].array[j] << " ";
                }
                cout << endl;
            }
        }
    }*/

    void print_graph() {
        cout << "Liczba wierzchołków: " << V << endl;
        cout << "Liczba krawędzi: " << E << endl;
        cout << "Skierowanie: " << (directionality == DIRECTED ? "TAK" : "NIE") << endl;
        cout << "Lista sąsiedztwa:" << endl;

        for (int u = 1; u <= V; u++) {
            cout << u << ": ";
            for (int v : neighbors[u]) {
                cout << neighbors.array[u].array[i] << " ";
            }
            cout << endl;
        }
    }
};

int main(int argc, char** argv) {
    Graph graf("resources/aod_testy1/2/g2a-1.txt");
    graf.print_graph();
    //cout << graf.V;
    //graf.topological_sort();
    //graf.bfs(2, true);


    return 0;
}