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

    void dfs2(int start, vector<int>& visited, vector<int>& component, bool reversed = false) {
        visited[start] = 1;
        stack<int> st;

        st.push(start);

        while(!st.empty()) {
            int u = st.top();
            st.pop();

            component.push_back(u);

            if(!reversed) {
                for(int v : neighbors[u]) {
                    if(visited[v] == 0) {
                        visited[v] = 1;
                        st.push(v);
                    }
                }
            }
            else {
                for(int v : reverse_neighbors[u]) {
                    if(visited[v] == 0) {
                        visited[v] = 1;
                        st.push(v);
                    }
                }
            }
        }
    }

    void fillOrder(int start, vector<int>& visited, queue<int>& que) {
        visited[start] = true;
        queue<int> q;
    
        q.push(start);

        while(!q.empty()) {
            int u = q.front();
            q.pop();
            que.push(u);

            for(int v : neighbors[u]) {
                if(visited[v] == 0) {
                    visited[v] = 1;
                    q.push(v);
                }
            }
        }
    }

    void strong_connect() {
        vector<vector<int>> components;
        queue<int> que;
        vector<int> visited;
        visited.assign(V + 1, 0);

        for(int u = 1; u <= V; u++) {
            if(visited[u] == 0) {
                fillOrder(u, visited, que);
            }
        }

        for(int u = 1; u <= V; u++) {
            visited[u] = 0;
        }

        while (!que.empty()) {
            int u = que.front();
            que.pop();
    
            if (visited[u] == 0) {
                vector<int> component;
                dfs2(u, visited, component, true);
                components.push_back(component);
            }
        }

        int i = 0;
        cout << "Graf posiada " << components.size() << " silnie spojnych skladowych\n";
        for(vector<int> component : components) {
            cout << "\tSkladowa " << ++i << " zawiera " << component.size() << " elementow\n";
            if(V <= 200) {
                cout << "\t\t";
                for(int u : component) {
                    cout << u << ", ";
                }
                cout << endl;
            }
        }
    }

    void bipartite() {
        queue<int> que;
        vector<int> colors;
        colors.assign(V + 1, 0);
        int x, y, z;

        for(int i = 1; i <= V; i++) {
            if(colors[i] == 0) {
                colors[i] = 1;
                que.push(i);

                while(!que.empty()) {
                    int u = que.front();
                    que.pop();

                    for(int v : neighbors[u]) {
                        if(colors[v] == colors[u]){
                            cout << "Graf nie jest dwudzielny!\n";
                            return;
                        }
                        if(colors[v] == 0) {
                            colors[v] = 3 - colors[u];
                            que.push(v);
                        }
                    }
                }
            }
        }

        cout << "Graf jest dwudzielny!\n";
        if(V <= 200) {
            cout << "Podzial numer 1:\n";
            for(int i = 1; i <= V; i++) {
                if(colors[i] == 1) {
                    cout << i;
                    if(i != V) cout << ", ";
                }
            }
            cout << "\nPodzial numer 2:\n";
            for(int i = 1; i <= V; i++) {
                if(colors[i] == 2) {
                    cout << i;
                    if(i != V) cout << ", ";
                }
            }
        }
    }

    void print_graph(bool neighbors_show = true) {
        cout << "Liczba wierzcholkow: " << V << endl;
        cout << "Liczba krawedzi: " << E << endl;
        cout << "Skierowanie: " << (directionality == DIRECTED ? "TAK" : "NIE") << endl;

        if(neighbors_show) {
            cout << "Lista sasiedztwa:" << endl;

            for (int u = 1; u <= V; u++) {
                cout << u << ": ";
                for (int v : neighbors[u]) {
                    cout << v << " ";
                }
                cout << endl;
            }
        }
    }
};

int main(int argc, char** argv) {
    Graph graf("resources/aod_testy1/3/g3-6.txt");
    graf.print_graph(false);
    //cout << graf.topological_sort() << endl;
    //graf.bfs(2, true);
    //graf.dfs(2, true);
    graf.strong_connect();
    //graf.bipartite();

    return 0;
}