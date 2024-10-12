#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int minOperationNumber(vector<int> dim) {
	int n = dim.size();
	vector<vector<int>> minMults(n, vector<int>(n, 0));

	/* minMults[i][j] = min number of multiplications to multiply the chain from
	 * A_i ... A_j */

	/* chain of size 0 = N/A, chain of size 1 = 0 mults */
	for (int chainSize = 2; chainSize < n; chainSize++) {
		for (int i = 1; i < n - chainSize + 1; i++) {

			/* 'chain' = A_i ... A_j */
			int j		   = i + chainSize - 1;
			minMults[i][j] = INT_MAX;

			/* Split at every index along the chain created above and update
			 * cost if needed */
			for (int k = i; k <= j - 1; k++) {
				/* cost of multiplying this chain's 2 subchains */
				int subchainCost = minMults[i][k] + minMults[k + 1][j];

				/* cost of multipliying the two matrices at the split */
				int splitCost = dim[i - 1] * dim[k] * dim[j];

				int cost = subchainCost + splitCost;

				/* min(new cost, current cost) */
				minMults[i][j] = min(minMults[i][j], cost);
			}
		}
	}

	/* Return the minimum number of multiplications needed to multiply the chain
	 * from matrix #1 to matrix #n-1 */
	return minMults[1][n - 1];
}

int main() {
	cout << minOperationNumber({5, 4, 6, 2, 7}) << "\n";
	return 0;
}
