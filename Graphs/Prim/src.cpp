#include <queue>
#include <vector>

using namespace std;

/*
 * Prim's algorithm is a greedy algorithm that finds a minimum spanning tree for
 * a weighted undirected graph. It starts with an arbitrary node 's' and adds
 * the node with the smallest edge weight.
 *
 * At every step, it adds the smallest edge (u, v) such that u is in the tree
 * and v is not.
 */

typedef pair<int, int> Edge; // {weight, to}

int primAdjList(vector<vector<Edge>> &g) {
	int v = g.size();
	vector<bool> visited(v, false);
	int MSTweight = 0;
	visited[0]	  = true;

	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	pq.push({0, 0});

	while (!pq.empty()) {
		int u = pq.top().second;
		int w = pq.top().first;
		pq.pop();

		if (visited[u])
			continue;

		visited[u] = true;
		MSTweight += w;

		for (Edge e : g[u])
			if (!visited[e.second])
				pq.push({e.first, e.second}); /* {weight, to} */
	}

	return MSTweight;
}
