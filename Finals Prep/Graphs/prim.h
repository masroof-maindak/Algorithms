#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
    Prim's algorithm is a greedy algorithm that finds a minimum spanning tree for a 
    weighted undirected graph. It starts with an arbitrary node and adds the cheapest
    edge to the tree. It then adds the cheapest edge from the tree to a new node
    It continues until all nodes are in the tree
*/

typedef pair<int, int> Edge; // {weight, to}
// Don't need a 'from' field because each edge is stored against the node it is from

int primAdjList (vector<vector<Edge>> &graph) {
    int v = graph.size();
    vector<bool> visited (v, false);
    int MSTweight = 0;
    visited[0] = true; // select 0 as the starting node

    // priority queue to store the edges
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push({0, 0});

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

        // iterate through the edges, adding the unexplored edges to the priority queue
        for (Edge e : graph[u])
            if (!visited[e.second])
                pq.push({e.first, e.second}); // {weight, to}
    }

    return MSTweight;
}