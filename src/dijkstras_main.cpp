#include "dijkstras.h"
int main() {
    Graph graph;
    file_to_graph("src/small.txt", graph);
    
    vector<int> previous(graph.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(graph, 0, previous);
    
    for (int i = 0; i < graph.numVertices; ++i) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }
    return 0;
}
