#include <iostream>
using namespace std;

struct Router {
    int dist[20];   // distance to every node
    int from[20];   // next hop
} rt[10];

int main() {
    int cost[20][20];
    int n;

    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "Enter the cost (delay) matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
            if (i == j) cost[i][j] = 0;   // self cost = 0

            rt[i].dist[j] = cost[i][j];  // initial distances
            rt[i].from[j] = j;           // initial next hop
        }
    }

    // Distance Vector Algorithm
    int count;
    do {
        count = 0;

        for (int i = 0; i < n; i++) {         // for each router
            for (int j = 0; j < n; j++) {     // for each destination
                for (int k = 0; k < n; k++) { // check via every neighbor
                    if (rt[i].dist[j] > cost[i][k] + rt[k].dist[j]) {

                        rt[i].dist[j] = cost[i][k] + rt[k].dist[j];
                        rt[i].from[j] = k;   // update next hop
                        count++;
                    }
                }
            }
        }
    } while (count != 0);   // repeat until no change

    // Print routing tables
    for (int i = 0; i < n; i++) {
        cout << "\nRouting table for Router " << i + 1 << ":\n";
        cout << "Destination\tNext Hop\tDistance\n";
        for (int j = 0; j < n; j++) {
            cout << j + 1 << "\t\t" 
                 << rt[i].from[j] + 1 << "\t\t"
                 << rt[i].dist[j] << endl;
        }
    }

    return 0;
}
