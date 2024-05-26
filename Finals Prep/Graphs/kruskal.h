#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int from, to, weight;
    bool operator > (const Edge &e) const {
        return weight > e.weight;
    }
};

int kruskal (int V, vector<Edge> &edges) {
    // Sort edges by weight
    int E = edges.size();
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    for (Edge e : edges)
        pq.push(e);
    
}