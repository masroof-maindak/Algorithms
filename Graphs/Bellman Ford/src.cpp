#include <climits>
#include <vector>

using namespace std;

/*
 * BF is used when Dijkstra's is not applicable (negative weights)
 * It is important to note however that both will fail if there is a negative
 * cycle (BF can still be used to detect negative cycles, but not to find the
 * shortest path in one's presence) BF, unlike Dijkstra, is not a greedy
 * algorithm. It relaxes all edges v-1 times.
 */

/*
 * Note that if we want to detect WHAT nodes are [in/affected by] the
 * negative cycle, rather than simply confirming its existence, we can run
 * the entire algorithm again and if any distance is updated, mark it as
 * negative infinity rather than (dist[e.src] + e.weight)
 */

/* Time complexity: O(v^3) */
vector<int> BfMat(vector<vector<int>> &g, int origin) {
	int v = g[0].size();
	vector<int> dist(v, INT_MAX);
	dist[origin] = 0;

	/*
	 * 1. Loop through all vertices v-1 times
	 * 2. For each vertex, loop through all outgoing edges
	 * 3. If the edge exists and the new path is shorter, update the distance
	 */

	for (int i = 0; i < v - 1; i++)
		for (int j = 0; j < v; j++)
			for (int k = 0; k < v; k++)
				if (g[j][k] != INT_MAX and dist[j] + g[j][k] < dist[k])
					dist[k] = dist[j] + g[j][k];

	/* Check if a negative cycle *exists* */
	for (int j = 0; j < v; j++)
		for (int k = 0; k < v; k++)
			if (g[j][k] != INT_MAX and dist[j] + g[j][k] < dist[k])
				return {};

	return dist;
}

struct Edge {
	int src, dest, weight;
};

vector<int> BfList(vector<vector<Edge>> &graph, int origin) {
	int V = graph.size();
	vector<int> dist(V, INT_MAX);
	dist[origin] = 0;

	/* v-1 iterations */
	for (int i = 0; i < V - 1; i++)
		/* For each vertex' adjacencey list in the graph */
		for (vector<Edge> &u : graph)
			/* For each outgoing edge 'e' in the adj. list of vertex 'u' */
			for (Edge &e : u)
				if (dist[e.src] != INT_MAX and
					dist[e.src] + e.weight < dist[e.dest])
					dist[e.dest] = dist[e.src] + e.weight;

	for (vector<Edge> &u : graph)
		for (Edge &e : u)
			if (dist[e.src] != INT_MAX and
				dist[e.src] + e.weight < dist[e.dest])
				return {};

	return dist;
}
