#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& graph, int source, vector<int>& previous) {
    int numVertices = graph.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    
    distances[source] = 0;
    previous[source] = -1;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});
    
    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        
        for (const Edge& edge : graph[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.insert(path.begin(), v);
    }
    return path;
}

void print_path(const vector<int>& path, int total) {
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}
