#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define V 6 // Number of locations

// Distance matrix (in kilometers)
int graph[V][V] = {
    {0, 150, INT_MAX, INT_MAX, 90, INT_MAX},        // Yamunotri
    {150, 0, INT_MAX, 240, 100, INT_MAX},           // Gangotri
    {INT_MAX, INT_MAX, 0, 200, INT_MAX, 80},        // Kedarnath
    {INT_MAX, 240, 200, 0, INT_MAX, INT_MAX},       // Badrinath
    {90, 100, INT_MAX, INT_MAX, 0, INT_MAX},        // Uttarkashi
    {INT_MAX, INT_MAX, 80, INT_MAX, INT_MAX, 0}     // Guptkashi
};

// Human-readable names
string places[V] = {
    "Yamunotri", "Gangotri", "Kedarnath",
    "Badrinath", "Uttarkashi", "Guptkashi"
};

void dijkstra(int src) {
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);
    dist[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        int u = -1;
        for (int j = 0; j < V; j++)
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;

        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    cout << "\nShortest routes from " << places[src] << ":\n";
    for (int i = 0; i < V; i++) {
        if (i == src) continue;
        cout << "To " << places[i] << ": ";
        if (dist[i] == INT_MAX)
            cout << "No direct route available.\n";
        else
            cout << dist[i] << " km\n";
    }
}

void floydWarshall() {
    int dist[V][V];

    // Copy original distances
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Apply Floyd-Warshall algorithm
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    // Display result
    cout << "\nAll-Pairs Shortest Path Matrix:\n\n";
    cout << "         ";
    for (int i = 0; i < V; i++)
        cout << places[i].substr(0, 6) << "\t";
    cout << endl;

    for (int i = 0; i < V; i++) {
        cout << places[i].substr(0, 6) << "  ";
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INT_MAX)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

void showPlaces() {
    cout << "\nAvailable Locations:\n";
    for (int i = 0; i < V; i++)
        cout << "  " << i << ". " << places[i] << endl;
}

int main() {
    int choice;
    cout << "Welcome to DevBhoomi Navigator – Char Dham Route Planner (Phase 1)\n";

    do {
        cout << "\n=============================\n";
        cout << "Choose an option:\n";
        cout << "  1. Find shortest route from one place (Dijkstra)\n";
        cout << "  2. Show all shortest routes between all places (Floyd-Warshall)\n";
        cout << "  3. Exit\n";
        cout << "=============================\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice == 1) {
            showPlaces();
            int src;
            cout << "Enter the number of your starting location: ";
            cin >> src;

            if (src >= 0 && src < V) {
                dijkstra(src);
            } else {
                cout << "Invalid place number. Try again.\n";
            }

        } else if (choice == 2) {
            floydWarshall();

        } else if (choice != 3) {
            cout << "Invalid option! Please choose from the menu.\n";
        }

    } while (choice != 3);

    cout << "\nThank you for using DevBhoomi Navigator. Safe travels!\n";
    return 0;
}
