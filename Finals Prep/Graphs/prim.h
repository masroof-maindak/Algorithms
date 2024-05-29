#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
    Prim's algorithm is a greedy algorithm that finds a minimum spanning tree for a 
    weighted undirected graph. It starts with an arbitrary node 's' and adds the node
    with the smallest edge weight.

    At every step, it adds the smallest edge (u, v) such that u is in the tree and v is not.
*/

typedef pair<int, int> Edge; // {weight, to}
// Don't need a 'from' field because each edge is stored against the node it is from

// returns: weight of MST
// param: graph in adjacency list format
int primAdjList (vector<vector<Edge>> &graph) {
    int v = graph.size();
    vector<bool> visited (v, false);
    int MSTweight = 0;
    visited[0] = true; // select 0 as the starting node

    // priority queue to store the edges
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push({0, 0});  // starting node has no weight

    while (!pq.empty()) {
        // get the node on the other end of the shortest edge
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();

        // continue if already visited
        if (visited[u]) 
            continue;

        // mark as visited
        visited[u] = true;
        MSTweight += w;

        // iterate through its outgoing edges, adding the ones who lead to 
        // paths we HAVEN'T explored to the priority queue
        for (Edge e : graph[u])
            if (!visited[e.second])
                pq.push({e.first, e.second}); // {weight, to}
    }

    return MSTweight;
}