#include <iostream>
using namespace std;
#define V 7

int getPopular(int key[], bool mstSet[]) {
    int min = INT_MIN, min_index;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && key[v] > min) {
            min = key[v], min_index = v;
        }
    }

    return min_index;
}


void print(int parent[], int graph[V][V]) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << " \n";
}

void removeRoads(int graph[V][V]) {
    int parents[V];
    int values[V];
    bool save[V];

    for (int i = 0; i < V; i++) values[i] = INT_MIN, save[i] = false;

    values[0] = 0;
    parents[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = getPopular(values, save);
        save[u] = true;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && save[v] == false && graph[u][v] > values[v])
                parents[v] = u, values[v] = graph[u][v];
    }


    print(parents, graph);
}

int main()
{
    int graph[V][V] = {
        { 0, 5, 8, 0, 0, 0, 0 },
        { 5, 0, 0,12, 0, 9, 0 },
        { 8, 0, 0, 0, 8, 4, 2 },
        { 0,12, 0, 0, 3, 6, 0 },
        { 0, 0, 8, 3, 0, 0, 7 },
        { 0, 9, 4, 6, 0, 0, 0 },
        { 0, 0, 2, 0, 7, 0, 0 }
    };

    removeRoads(graph);
    return 0;
}