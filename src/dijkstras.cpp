#include "dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    // Set distance from source to source to 0
    distances[source] = 0;
    // Set all vertices to unexplored
    previous.assign(numVertices, -1); 

    priority_queue<pair<int,int>> minHeap; // pair<vertex, weight>
    minHeap.push({source, 0});

    while (!minHeap.empty()) {
        int u = minHeap.top().first;
        int dest_u =  minHeap.top().second;
        minHeap.pop();

        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (Edge edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}


vector<int> extract_shortest_path(const vector<int>& previous, int destination) {
    vector<int> result;

    if (previous[destination] == -1) {
        return result;
    }

    result.push_back(destination);
    int before_dest = previous[destination];
    while(before_dest != -1) {
        result.insert(result.begin(), before_dest);
        before_dest = previous[before_dest];
    }

    return result;
}


void print_path(const vector<int>& v, int total) {

}
