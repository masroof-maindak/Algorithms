#include <iostream>
#include <vector>
using namespace std;

int maxValue(vector<int> weights, vector<int> values, int cap) {
	int n = weights.size();
	vector<vector<int>> mat(n + 1, vector<int>(cap + 1, 0));

	/*
	 * i = pointer to item weights/values (1 to n)
	 * w = every possible capacity from 0 to cap
	 *
	 * mat[i][w] = maximum value that can be obtained
	 * with the first i items, and a capacity of w
	 */

	for (int i = 1; i <= n; i++) {
		for (int w = 0; w <= cap; w++) {

			/*
			 * IDEA: if item i-1 fits inside capacity w then it MIGHT play a
			 * part in determining the max value
			 */

			int prevVal = mat[i - 1][w];

			if (weights[i - 1] <= w) {
				int newVal = values[i - 1] + mat[i - 1][w - weights[i - 1]];
				mat[i][w]  = max(newVal, prevVal);
			} else {
				mat[i][w] = prevVal;
			}
		}
	}

	return mat[n][cap];
}

int main() {
	cout << maxValue({3, 1, 3, 4, 2}, {2, 2, 4, 5, 3}, 7)
		 << "\n"; // 10
	return 0;
}
