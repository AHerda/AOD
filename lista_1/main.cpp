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

        int size = results.size();

        return (size != V);
    }

    void dfs2(int start, vector<int>* component, vector<int> visited_global, bool reverse = false) {
        vector<int> visited;
        visited.assign(V + 1, 0);
        stack<int> st;
        
        st.push(start);
        
        visited[start] = 1;
        visited_global[start] = 1;

        component->push_back(start);

        while(!st.empty()) {
            int u = st.top();
            st.pop();

            vector<int> temp = (reverse) ? reverse_neighbors[u] : neighbors[u];

            for(int v : temp) {
                if(visited[v] == 0) {
                    visited[v] = 1;
                    visited_global[v] = 1;
                    
                    st.push(v);

                    component->push_back(v);
                }
            }
        }
    }

    void strong_connect() {
        vector<int> visited;
        visited.assign(V + 1, 0);
        vector<vector<int>> components;
        stack<int> st;

        for(int u = 1; u <= V; u++) {
            if(visited[u] == 0) {
                vector<int> component;
                dfs2(u, &component, visited);
                for(int v : component) {
                    st.push(v);
                }
            }
        }

        for(int i = 0; i < visited.size(); i++) {
            visited[i] = 0;
        }

        while(!st.empty()) {
            int u = st.top();
            st.pop();

            if(visited[u] == 0) {
                vector<int> component;
                dfs2(u, &component, visited, true);
                components.push_back(component);
            }
        }

        cout << "Liczba silnie spójnych składowych: " << components.size() << endl;
        for (vector<int> component : components) {
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
    Graph graf("resources/aod_testy1/3/g3-5.txt");
    //graf.print_graph();
    //cout << graf.topological_sort() << endl;
    //graf.bfs(2, true);
    //graf.dfs(2, true);
    graf.strong_connect();


    return 0;
}