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
    T* array = nullptr;
    int size;
 
    int capacity;
 
public:
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
        cout << size;
        size++;
    }
 
    void pop_back()
    {
        array[size - 1] = nullptr;
 
        size--;
 
        if (size == (capacity / 2)) {
            shrinkArray();
        }
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
 
        array[size - 1] = nullptr;
 
        size--;
 
        if (size == (capacity / 2)) {
            shrinkArray();
        }
    }
 
    void printArrayDetails()
    {
        cout << "Elements of array : ";
        for (int i = 0; i < size; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
        cout << "No of elements in array : " << size
             << ", Capacity of array :" << capacity << endl;
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
        neighbors.get(u).push_back(v);
        cout << neighbors.get(u).getSize() << endl;
        reverse_neighbors.get(v).push_back(u);
        if (directionality == UNDIRECTED) {
            neighbors.get(v).push_back(u);
            reverse_neighbors.get(u).push_back(v);
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
        queue<int> que;
        que.push(start);
        visited.set(start, 1);

        while(!que.empty()) {
            int u = que.front();
            que.pop();

            if(tree) {
                cout << u << " ";
            }

            for(int i = 0; i < neighbors.get(u).getSize(); i++) {
                if(visited.get(neighbors.get(u).get(i)) == 0) {
                    visited.set(neighbors.get(u).get(i), 1);
                    que.push(neighbors.get(u).get(i));
                }
            }
        }

        cout << endl;
    }

    void dfs(int start, bool tree, DynamicArray<int> component, DynamicArray<int> visited_global, bool reverse = false) {
        DynamicArray<int> visited;
        visited.fill(V + 1, 0);
        stack<int> stos;
        
        stos.push(start);
        
        visited.set(start, 1);
        if(!visited_global.isEmpty()) {
            visited_global.set(start, 1);
        }
        component.push_back(start);

        while(!stos.empty()) {
            int u = stos.top();
            stos.pop();

            if(tree) {
                cout << u << " ";
            }

            if(!reverse) {
                for(int i = 0; i < neighbors.get(u).getSize(); i++) {
                    if(visited.get(neighbors.get(u).get(i)) == 0) {
                        visited.set(neighbors.get(u).get(i), 1);
                        if(!visited_global.isEmpty()) {
                            visited_global.set(neighbors.get(u).get(i), 1);
                        }
                    
                        stos.push(neighbors.get(u).get(i));

                        if(!component.isEmpty()) {
                            component.push_back(neighbors.get(u).get(i));
                        }
                    }
                }
            }
            else {
                for(int i = 0; i < reverse_neighbors.get(u).getSize(); i++) {
                    if(visited.get(reverse_neighbors.get(u).get(i)) == 0) {
                        visited.set(neighbors.get(u).get(i), 1);
                        if(!visited_global.isEmpty()) {
                            visited_global.set(neighbors.get(u).get(i), 1);
                        }
                    
                        stos.push(neighbors.get(u).get(i));

                        if(!component.isEmpty()) {
                            component.push_back(neighbors.get(u).get(i));
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
            for(int i = 0; i < neighbors.get(u).getSize(); i++) {
                E_in.set(neighbors.get(u).get(i), E_in.get(neighbors.get(u).get(i)) + 1);
            }
        }

        queue<int> que;

        for(int u = 1; u <= V; u++) {
            if(E_in.get(u) == 0) {
                que.push(u);
            }
        }

        while(!que.empty()) {
            int u = que.front();
            que.pop();
            results.push_back(u);

            for(int i = 0; i < neighbors.get(u).getSize(); i++) {
                E_in.set(neighbors.get(u).get(i), E_in.get(neighbors.get(u).get(i)) - 1);
                if(E_in.get(neighbors.get(u).get(i)) == 0) {
                    que.push(neighbors.get(u).get(i));
                }
            }
        }

        if(V <= 200) {
            for(int i = 0; i < results.getSize(); i++) {
                cout << results.get(i);

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
        stack<int> s;

        for(int u = 1; u <= V; u++) {
            if(visited.get(u) == 0) {
                DynamicArray<int> component;
                dfs(u, false, component, visited);
                for(int i = 0; i < component.getSize(); i++) {
                    s.push(component.get(i));
                }
            }
        }

        DynamicArray<int> visited2;
        visited2.fill(V + 1, 0);

        while(!s.empty()) {
            int u = s.top();
            s.pop();

            if(visited2.get(u) == 0) {
                DynamicArray<int> component;
                dfs(u, false, component, visited, true);
                components.push_back(component);
            }
        }

        cout << "Liczba silnie spójnych składowych: " << components.getSize() << endl;
        for (int i = 0; i < components.getSize(); i++) {
            cout << "Liczba wierzchołków w składowej: " << components.get(i).getSize() << endl;
            if (V <= 200) {
                cout << "Wierzchołki składowej: ";
                for (int j = 0; j < components.get(i).getSize(); j++) {
                    cout << components.get(i).get(j) << " ";
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
            for (int i = 0; i < neighbors.get(u).getSize(); i++) {
                cout << neighbors.get(u).get(i) << " ";
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