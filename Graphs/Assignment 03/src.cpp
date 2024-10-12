#include <climits>
#include <queue>
#include <vector>

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
			/* If vertex is adj. and already visited, cycle detected */
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
	std::vector<int> dist(n, INT_MAX);
	std::vector<bool> visited(n, false);
	dist[origin] = 0;

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
						std::greater<std::pair<int, int>>>
		pq;
	pq.push(std::make_pair(0, origin));

	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();

		if (visited[u])
			continue;

		visited[u] = true;

		/* Pick unvisited adjacent vertices and update distance if shorter path
		 * found */
		for (int v = 0; v < n; v++) {
			if (g[u][v] != INT_MAX and !visited[v] and
				dist[u] + g[u][v] < dist[v]) {
				dist[v] = dist[u] + g[u][v];
				pq.push(std::make_pair(dist[v], v));
			}
		}
	}

	return dist;
}

int optimalMiddleGround(std::vector<std::vector<int>> &g, int vertQ,
						int vertP) {
	int vertT = INT_MAX, sumCost = INT_MAX;
	std::vector<int> costsFromQ = dijkstra(g, vertQ);
	std::vector<int> costsFromP = dijkstra(g, vertP);

	for (int i = 0; i < g[0].size(); i++) {
		int sumCostAtVertI = costsFromQ[i] + costsFromP[i];
		if (sumCostAtVertI < sumCost) {
			sumCost = sumCostAtVertI;
			vertT	= i;
		}
	}

	return vertT;
}

int main() { return 0; }
