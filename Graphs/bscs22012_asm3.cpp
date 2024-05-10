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

std::vector<int> dijkstra(std::vector<std::vector<int>> &g, int originVert) {
    int n = g[0].size();
    std::vector<int> dist (n, INT_MAX);
    std::vector<bool> visited (n, false);
    dist[originVert] = 0;

    for (int i = 0; i < n; i++) {
        //select unvisited node/node with minimum cost
        int u = -1; 
        for (int j = 0; j < n; j++)
            if (!visited[j] and (u == -1 or dist[j] < dist[u]))
                u = j;

        // mark as visited
        visited[u] = true;

        // update adjacent nodes' cost
        for (int v = 0; v < n; v++)
            dist[v] = min(dist[v], dist[u] + g[u][v]);
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