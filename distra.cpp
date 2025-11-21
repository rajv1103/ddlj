#include <iostream>
#include <vector>
using namespace std;

#define INF 9999

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<vector<int>> w(n, vector<int>(n));

    // Input weight matrix
    cout << "Enter weight between each pair (enter -1 for no link):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> w[i][j];
            if (w[i][j] < 0) w[i][j] = INF;
        }
    }

    int src, dest;
    cout << "Enter source and destination nodes: ";
    cin >> src >> dest;

    // Dijkstra Tables
    vector<int> dist(n, INF), visited(n, 0), prev(n, -1);

    dist[src] = 0;

    for (int c = 0; c < n - 1; c++) {
        int u = -1, min = INF;

        // Pick minimum distance unvisited node
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        // Relax neighbors
        for (int v = 0; v < n; v++) {
            if (!visited[v] && w[u][v] != INF &&
                dist[u] + w[u][v] < dist[v]) {

                dist[v] = dist[u] + w[u][v];
                prev[v] = u;
            }
        }
    }

    // Print cost
    cout << "\nMinimum Cost = " << dist[dest] << endl;

    // Print path (reverse)
    cout << "Shortest Path = ";
    vector<int> path;
    for (int v = dest; v != -1; v = prev[v])
        path.push_back(v);

    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << (i ? " -> " : "");

    cout << endl;

    return 0;
}
