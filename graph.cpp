#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

#define V 10 // Total number of locations

// Distance matrix (in kilometers)
int graph[V][V] = {
    // Yamunotri, Gangotri, Kedarnath, Badrinath, Uttarkashi, Guptkashi, Haridwar, Rishikesh, Dehradun, Rudraprayag
    {0, 150, INT_MAX, INT_MAX, 90, INT_MAX, 220, INT_MAX, INT_MAX, INT_MAX},     // Yamunotri
    {150, 0, INT_MAX, 240, 100, INT_MAX, 250, INT_MAX, INT_MAX, INT_MAX},        // Gangotri
    {INT_MAX, INT_MAX, 0, 200, INT_MAX, 80, INT_MAX, INT_MAX, INT_MAX, 30},      // Kedarnath
    {INT_MAX, 240, 200, 0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 100},    // Badrinath
    {90, 100, INT_MAX, INT_MAX, 0, INT_MAX, 180, 160, 170, INT_MAX},             // Uttarkashi
    {INT_MAX, INT_MAX, 80, INT_MAX, INT_MAX, 0, INT_MAX, INT_MAX, INT_MAX, 50},  // Guptkashi
    {220, 250, INT_MAX, INT_MAX, 180, INT_MAX, 0, 30, 60, INT_MAX},              // Haridwar
    {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 160, INT_MAX, 30, 0, 50, INT_MAX},      // Rishikesh
    {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 170, INT_MAX, 60, 50, 0, INT_MAX},      // Dehradun
    {INT_MAX, INT_MAX, 30, 100, INT_MAX, 50, INT_MAX, INT_MAX, INT_MAX, 0}       // Rudraprayag
};

// Location names
string places[V] = {
    "Yamunotri", "Gangotri", "Kedarnath", "Badrinath", "Uttarkashi",
    "Guptkashi", "Haridwar", "Rishikesh", "Dehradun", "Rudraprayag"
};

// Display available locations
void showPlaces() {
    cout << "\nAvailable Locations:\n";
    for (int i = 0; i < V; i++)
        cout << "  " << i << ". " << places[i] << endl;
}

// Dijkstra's Algorithm (with path display)
void dijkstra(int src) {
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        for (int i = 0; i < V; i++)
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        if (dist[u] == INT_MAX)
            break;

        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "\nShortest routes from " << places[src] << ":\n";
    for (int i = 0; i < V; i++) {
        if (i == src) continue;
        cout << "To " << places[i] << ": ";
        if (dist[i] == INT_MAX) {
            cout << "No route available.\n";
        } else {
            cout << dist[i] << " km via ";
            // Print path
            vector<int> path;
            for (int v = i; v != -1; v = parent[v])
                path.insert(path.begin(), v);
            for (size_t j = 0; j < path.size(); j++) {
                cout << places[path[j]];
                if (j != path.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
}

// Floyd-Warshall Algorithm
void floydWarshall() {
    int dist[V][V];

    // Initialize distances
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Main algorithm
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

int main() {
    int choice;

    cout << "==============================\n";
    cout << "  DevBhoomi Navigator – Char Dham Route Planner \n";
    cout << "==============================\n";

    do {
        cout << "\nMenu Options:\n";
        cout << "  1. Find shortest route from one place (Dijkstra)\n";
        cout << "  2. Show all shortest routes between all places (Floyd-Warshall)\n";
        cout << "  3. Show all available locations\n";
        cout << "  4. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                showPlaces();
                int src;
                cout << "Enter the number of your starting location: ";
                cin >> src;
                if (src >= 0 && src < V) {
                    dijkstra(src);
                } else {
                    cout << "Invalid location selected. Please try again.\n";
                }
                break;
            }
            case 2:
                floydWarshall();
                break;
            case 3:
                showPlaces();
                break;
            case 4:
                cout << "Thank you for using DevBhoomi Navigator. Safe travels!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 4);

    return 0;
}
