#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
    BF is used when Dijkstra's is not applicable (negative weights)
    It is important to note however that both will fail if there is a negative cycle
    BF, unlike Dijkstra, is not a greedy algorithm
    It relaxes all edges v-1 times
*/

vector<int> bellmanFordAdjMatrix(vector<vector<int>> &g, int origin) {
    // Time complexity: O(v^3)
    int v = g[0].size();
    vector<int> dist (v, INT_MAX);
    dist[origin] = 0;

    for (int i = 0; i < v-1; i++) //v-1 iterations
        for (int j = 0; j < v; j++) //loop through all vertices
            for (int k = 0; k < v; k++) //check all outgoing edges
                if (g[j][k] != INT_MAX and dist[j] + g[j][k] < dist[k]) // if the edge exists and the new path is shorter
                    dist[k] = dist[j] + g[j][k]; // update the distance

    //check if a negative cycle *exists*
    for (int j = 0; j < v; j++)
        for (int k = 0; k < v; k++)
            if (g[j][k] != INT_MAX and dist[j] + g[j][k] < dist[k]) // if a new, shorter path is found
                return {}; // negative cycle detected

    /*
        Not that if we want to detect WHAT nodes are in the negative cycle, we can run the
        entire algorithm again and if any distance is updated, mark it as negative infinity
    */

    return dist;
}

struct Edge {
    int src, dest, weight;
};

vector<int> bellmanFordAdjList(vector<vector<Edge>> &graph, int origin) {
    // Time complexity: O(v*e)
    int V = graph.size();
    vector<int> dist (V, INT_MAX);
    dist[origin] = 0;

    // relax all edges v-1 times
    for (int i = 0; i < V-1; i++) //v-1 iterations
        for (vector<Edge> &u : graph) // for each vertex' adjacencey list in the graph
            for (Edge &e : u) // for each outgoing edge 'e' in that adjacency list of vertex 'u'
                if (dist[e.src] != INT_MAX and dist[e.src] + e.weight < dist[e.dest]) // if the vertex has been reached by now and the new path is shorter
                    dist[e.dest] = dist[e.src] + e.weight; // update the distance
                    
    //check if a negative cycle *exists*
    for (vector<Edge> &u : graph)
        for (Edge &e : u)
            if (dist[e.src] != INT_MAX and dist[e.src] + e.weight < dist[e.dest])
                return {}; // negative cycle detected
    
    /*
        Not that if we want to detect WHAT nodes are in the negative cycle, rather than simply
        confirming its existence, we can run the entire algorithm again and if any distance is 
        updated, mark it as negative infinity rather than (dist[e.src] + e.weight)
    */

    return dist;
}