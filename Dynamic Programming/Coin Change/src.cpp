#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

int min(int a, int b) { return a < b ? a : b; }

int minCoinNumber(int target, vector<int> coins) {
	vector<int> coinCount(target + 1, INT_MAX);

	coinCount[0] = 0; /* 0 coins needed to make 0 ('base case') */

	/* For each target value, starting from 1 (0 is already solved) */
	for (int i = 1; i <= target; i++)
		/* For each coin value */
		for (int coinVal : coins)
			/* If the value is less than or equal to THIS target */
			if (coinVal <= i)
				/* Add the coin to the previous best solution */
				coinCount[i] = min(coinCount[i], coinCount[i - coinVal] + 1);

	return coinCount[target];
	/* if the value at the target's index is still target+1, it means the target
	 * value is not possible */
}

int main() {
	cout << minCoinNumber(11, {1, 2, 5}) << "\n";
	return 0;
}
