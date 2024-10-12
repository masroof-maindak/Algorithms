#include <climits>
#include <iostream>
#include <vector>
using namespace std;

#define INF INT_MAX

vector<vector<int>> FloydWarshall(vector<vector<int>> g) {
	/* IDEA: dist(a->b) = min(dist(a->b), dist(a->c) + dist(c->b)) */

	int v = g.size();
	vector<vector<int>> dist(v, vector<int>(v, INF));
	for (int i = 0; i < v; i++)
		dist[i][i] = 0;

	for (int i = 0; i < v; i++)
		for (int j = 0; j < v; j++)
			if (g[i][j] != 0)
				dist[i][j] = g[i][j];

	for (int k = 0; k < v; k++)
		for (int i = 0; i < v; i++)
			for (int j = 0; j < v; j++)
				if (dist[i][k] != INF && dist[k][j] != INF)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

	return dist;
}

int findCenter(vector<vector<int>> g) {
	vector<vector<int>> dist = FloydWarshall(g);

	int v		= g.size();
	int center	= 0;
	int minDist = INF;

	for (int i = 0; i < v; i++) {
		int maxDist = 0;
		for (int j = 0; j < v; j++)
			maxDist = max(maxDist, dist[i][j]);

		if (maxDist < minDist) {
			minDist = maxDist;
			center	= i;
		}
	}

	return center;
}

/*
 * Given an undirected, connected graph G=(V,E), design an algorithm to
 * find a node Vc (the center of the graph) such that the maximum
 * distance from Vc to any other node in the graph is minimized.
 */

int main() {
	cout << findCenter({{0, 1, INF, 1, 5},
						{1, 0, 1, 2, INF},
						{INF, 1, 0, 2, 3},
						{1, 2, 2, 0, 3},
						{5, INF, 3, 3, 0}})
		 << "\n";
	return 0;
}