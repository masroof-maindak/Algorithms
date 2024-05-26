#include <iostream>
#include <vector>
#include <queue>

#define min(a, b) (a < b ? a : b)
#define INT_MAX 2147483647

bool isCyclic(std::vector<std::vector<int>> &g) {
    if (g.size() == 0)
        return false;

    std::vector<bool> visited(g.size(), false);
    std::queue<int> q;

    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < g[0].size(); v++) {
            if (g[u][v] and visited[v])
                return true;
                
            if (g[u][v] and !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return false;
}

std::vector<int> dijkstra(std::vector<std::vector<int>> &g, int origin) {
    int n = g[0].size();
    std::vector<int> dist (n, INT_MAX);
    std::vector<bool> visited (n, false);
    dist[origin] = 0;

    //priority queue to store vertices by distance (pair<distance, vertex>)
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, origin));

    while (!pq.empty()) {
        // get the vertex with the minimum distance
        int u = pq.top().second;
        pq.pop();

        // skip if already visited
        if (visited[u])
            continue;

        // mark as visited
        visited[u] = true;

        // pick unvisited adjacent vertices and update distance if shorter path found
        for (int v = 0; v < n; v++) {
            if (g[u][v] != INT_MAX and !visited[v] and dist[u] + g[u][v] < dist[v]) {
                dist[v] = dist[u] + g[u][v];
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int optimalMiddleGround(std::vector<std::vector<int>> &g, int vertQ, int vertP) {
    int vertT = INT_MAX, sumCost = INT_MAX;
    std::vector<int> costsFromQ = dijkstra(g, vertQ);
    std::vector<int> costsFromP = dijkstra(g, vertP);

    for (int i = 0; i < g[0].size(); i++) {
        int sumCostAtVertI = costsFromQ[i] + costsFromP[i];
        if (sumCostAtVertI < sumCost) {
            sumCost = sumCostAtVertI;
            vertT = i;
        }
    }

    return vertT;
}

int main() {
    return 0;
}