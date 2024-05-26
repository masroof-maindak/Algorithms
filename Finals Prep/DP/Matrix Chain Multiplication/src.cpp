#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;

int minOperationNumber(vector<int> dimensions) {
    int n = dimensions.size();
    vector<vector<int>> minMults(n, vector<int>(n, 0));
    // minMults[i][j] = min number of multiplications to multiply the chain from A_i ... A_j

    for (int chainSize = 2; chainSize < n; chainSize++) {
        for (int i = 1; i < n - chainSize + 1; i++) {
            // 'chain' = A_i ... A_j
            int j = i + chainSize - 1; 
            minMults[i][j] = INT_MAX;

            // Split at every index along the chain created above and update cost if needed
            for (int k = i; k <= j - 1; k++) {
                int subchainsCost = minMults[i][k] + minMults[k+1][j];  // cost of multiplying the two subchains comprising this chain
                int splitCost = dimensions[i-1] * dimensions[k] * dimensions[j]; // cost of multipliying the two matrices at the split
                int cost = subchainsCost + splitCost;
                minMults[i][j] = min(minMults[i][j], cost);
            }
        }
    }

    // Return the minimum number of multiplications needed to multiply the chain from matrix #1 to matrix #n-1
    return minMults[1][n-1];
}

int main() {
    cout << minOperationNumber({5, 4, 6, 2, 7}) << "\n";
    return 0;
}