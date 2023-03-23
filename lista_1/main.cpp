#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

enum Directionality {
    DIRECTED,
    UNDIRECTED
};

#include <iostream>
using namespace std;
 
template <class T>
class DynamicArray {
private:
    
    int size;
 
    int capacity;
 
public:
    T* array = nullptr;
    DynamicArray()
    {
        capacity = 1;
        size = 0;
        array = new T[capacity];
    }
 
    DynamicArray(int capacity)
    {
        this->capacity = capacity;
        array = new T[capacity];
        size = 0;
    }

    T get(int index) {
        if(index < size)
            return array[index];
        return array[0];
    }

    void set(int index, T value) {
        if(index < size) {
            array[index] = value;
        }
    }
 
    int getSize() { return size; }
 
    int getCapacity() { return capacity; }
 
    void push_back(T value)
    {
        if (size == capacity) {
            growArray();
        }
 
        array[size] = value;
        
        size++;
    }
 
    void pop_back()
    {
        array[size - 1] = (int) NULL;
 
        size--;
 
        if (size == (capacity / 2)) {
            shrinkArray();
        }
    }

    void pop_front() {
        deleteAt(0);
    }
 
    void growArray()
    {
        T* temp = new T[capacity * 2];
 
        capacity = capacity * 2;
        for (int i = 0; i < size; i++) {
            temp[i] = array[i];
        }
 
        delete[] array;
 
        array = temp;
    }
 
    void shrinkArray()
    {
 
        capacity = size;
        T* temp = new T[capacity];
 
        for (int i = 0; i < size; i++) {
            temp[i] = array[i];
        }
 
        delete[] array;
 
        array = temp;
    }
 
    int search(T key)
    {
        for (int i = 0; i < size; i++) {
            if (array[i] == key) {
                return i;
            }
        }
 
        return -1;
    }
 
    void insertAt(int index, T value)
    {
        if (size == capacity) {
            growArray();
        }
 
        for (int i = size - 1; i >= index; i--) {
            array[i + 1] = array[i];
        }
 
        array[index] = value;
        size++;
    }
 
    void deleteAt(int index)
    {
        for (int i = index; i < size; i++) {
            array[i] = array[i + 1];
        }
 
        array[size - 1] = (int) NULL;
 
        size--;
 
        if (size == (capacity / 2)) {
            shrinkArray();
        }
    }
 
    bool isEmpty()
    {
        if (size == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    void fill(int n, T value) {
        for(int i = 0; i < n; i++) {
            push_back(value);
        }
    }
};

class Graph {
    Directionality directionality;
    int V;
    int E;
    DynamicArray<DynamicArray<int>> neighbors;
    DynamicArray<DynamicArray<int>> reverse_neighbors;

    void add_edge(int u, int v) {
        neighbors.array[u].push_back(v);
        reverse_neighbors.array[v].push_back(u);
        if (directionality == UNDIRECTED) {
            neighbors.array[v].push_back(u);
            reverse_neighbors.array[u].push_back(v);
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

        for(int i = 0; i < V; i++) {
            DynamicArray<int> temp1;
            neighbors.push_back(temp1);
            DynamicArray<int> temp2;
            reverse_neighbors.push_back(temp2);
        }

        int u, v;
        for(int i = 0; i < E; i++) {
            myfile >> u >> v;
            add_edge(u, v);
        }

        myfile.close();
    }

    void bfs(int start, bool tree) {
        DynamicArray<int> visited;
        visited.fill(V + 1, 0);
        DynamicArray<int> que;
        que.push_back(start);
        visited.set(start, 1);

        while(!que.isEmpty()) {
            int u = que.array[0];
            que.pop_front();

            if(tree) {
                cout << u << " ";
            }

            for(int i = 0; i < neighbors.array[u].getSize(); i++) {
                if(visited.get(neighbors.array[u].array[i]) == 0) {
                    visited.set(neighbors.array[u].array[i], 1);
                    que.push_back(neighbors.array[u].array[i]);
                }
            }
        }

        cout << endl;
    }

    void dfs(int start, bool tree, DynamicArray<int> component, DynamicArray<int> visited_global, bool reverse = false) {
        DynamicArray<int> visited;
        visited.fill(V + 1, 0);
        DynamicArray<int> stos;
        
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
                    if(visited.get(neighbors.array[u].array[i]) == 0) {
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
                    if(visited.get(reverse_neighbors.array[u].array[i]) == 0) {
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
    }

    bool topological_sort() {
        DynamicArray<int> results;
        DynamicArray<int> E_in;
        E_in.fill(V + 1, 0);

        for(int u = 1; u <= V; u++) {
            for(int i = 0; i < neighbors.array[u].getSize(); i++) {
                E_in.set(neighbors.array[u].array[i], E_in.get(neighbors.array[u].array[i]) + 1);
            }
        }

        DynamicArray<int> que;

        for(int u = 1; u <= V; u++) {
            if(E_in.array[u] == 0) {
                que.push_back(u);
            }
        }

        while(!que.isEmpty()) {
            int u = que.array[0];
            que.pop_front();
            results.push_back(u);

            for(int i = 0; i < neighbors.array[u].getSize(); i++) {
                E_in.set(neighbors.array[u].array[i], E_in.get(neighbors.array[u].array[i]) - 1);
                if(E_in.get(neighbors.array[u].array[i]) == 0) {
                    que.push_back(neighbors.array[u].array[i]);
                }
            }
        }

        if(V <= 200) {
            for(int i = 0; i < results.getSize(); i++) {
                cout << results.array[i];

                if(i + 1 != results.getSize()) {
                    cout << " ";
                }

                cout << endl;
            }
        }

        return (results.getSize() != V);
    }

    void strong_connect() {
        DynamicArray<int> visited;
        visited.fill(V + 1, 0);
        DynamicArray<DynamicArray<int>> components;
        DynamicArray<int> stos;

        for(int u = 1; u <= V; u++) {
            if(visited.array[u] == 0) {
                DynamicArray<int> component;
                dfs(u, false, component, visited);
                for(int i = 0; i < component.getSize(); i++) {
                    stos.push_back(component.array[i]);
                }
            }
        }

        DynamicArray<int> visited2;
        visited2.fill(V + 1, 0);

        while(!stos.isEmpty()) {
            int u = stos.array[stos.getSize() - 1];
            stos.pop_back();

            if(visited2.array[u] == 0) {
                DynamicArray<int> component;
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
    }

    void print_graph() {
        cout << "Liczba wierzchołków: " << V << endl;
        cout << "Liczba krawędzi: " << E << endl;
        cout << "Skierowanie: " << (directionality == DIRECTED ? "TAK" : "NIE") << endl;
        cout << "Lista sąsiedztwa:" << endl;

        for (int u = 1; u <= V; u++) {
            cout << u << ": ";
            for (int i = 0; i < neighbors.array[u].getSize(); i++) {
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
    //vector<int> maciek;
    //vector<bool> maciek2;
    graf.topological_sort();
    graf.bfs(2, true);

    return 0;
}