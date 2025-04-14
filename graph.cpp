#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Graph represented as an adjacency list
// Each pair = (destination, weight)
vector<vector<pair<int, int>>> graph;

// Distance matrix for Floyd-Warshall
vector<vector<int>> distFW;

// Location names for display
vector<string> locations = {
    "Yamunotri", "Gangotri", "Kedarnath", "Badrinath"
};

// Function to add an edge between two places
void addEdge(int u, int v, int weight) {
    graph[u].push_back({v, weight});
    graph[v].push_back({u, weight}); // Assuming undirected roads
}

// Function to initialize graph with sample Char Dham data
void buildGraph() {
    int n = locations.size();
    graph.resize(n);

    // Sample edges (can be modified or extended)
    addEdge(0, 1, 110); // Yamunotri <-> Gangotri
    addEdge(1, 2, 180); // Gangotri <-> Kedarnath
    addEdge(2, 3, 120); // Kedarnath <-> Badrinath
    addEdge(0, 2, 250); // Yamunotri <-> Kedarnath
    addEdge(1, 3, 300); // Gangotri <-> Badrinath
}

// Dijkstra's Algorithm - single-source shortest path
void dijkstra(int src) {
    int n = graph.size();
    vector<int> dist(n, INF);
    dist[src] = 0;

    // Min-heap priority queue: (distance, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();

        for (auto it : graph[u]) {
            int v = it.first;
            int weight = it.second;
            if (dist[v] > currentDist + weight) {
                dist[v] = currentDist + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print results
    cout << "Shortest distances from " << locations[src] << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "→ " << locations[i] << ": ";
        if (dist[i] == INF)
            cout << "Unreachable\n";
        else
            cout << dist[i] << " km\n";
    }
}

// Floyd-Warshall Algorithm - all-pairs shortest path
void floydWarshall() {
    int n = graph.size();
    distFW.assign(n, vector<int>(n, INF));

    // Initialize with direct distances
    for (int u = 0; u < n; ++u) {
        distFW[u][u] = 0;
        for (auto it : graph[u]) {
            int v = it.first;
            int weight = it.second;
            distFW[u][v] = weight;
        }
    }

    // Dynamic programming step
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (distFW[i][k] != INF && distFW[k][j] != INF)
                    distFW[i][j] = min(distFW[i][j], distFW[i][k] + distFW[k][j]);

    // Print result
    cout << "\nAll-Pairs Shortest Paths (Floyd-Warshall):\n";
    for (int i = 0; i < n; ++i) {
        cout << locations[i] << " →\n";
        for (int j = 0; j < n; ++j) {
            cout << "  to " << locations[j] << ": ";
            if (distFW[i][j] == INF)
                cout << "Unreachable\n";
            else
                cout << distFW[i][j] << " km\n";
        }
    }
}
