#include <iostream>
#include <vector>

using namespace std;

int rodCutDP(vector<int> prices) {
	int n = prices.size();
	vector<int> bestPrices(n + 1, 0);

	/* bestPrices[i] = best price for a rod of length i */
	/* price @ length 0 = trivially 0 */

	/* for all lengths */
	for (int i = 1; i <= n; i++) {
		int x = 0;

		/* for all divisions within those lengths */
		for (int j = 0; j < i; j++) {
			int cutsPrice		= prices[j];
			int remainderDecomp = bestPrices[i - j - 1];
			x					= max(x, remainderDecomp + cutsPrice);
		}

		bestPrices[i] = x;
	}

	return bestPrices[n];
}

int main() {
	cout << rodCutDP({1, 5, 8, 9}) << "\n";
	return 0;
}
