#include <iostream>
#include <vector>
using namespace std;

int min (int a, int b) {
    return a < b ? a : b;
}

int minCoinNumber (int target, vector<int> coins) {
    //same principle as rod cutting. Add what's left to the previous 'best' solution
    int n = coins.size();
    vector<int> coinNums(target + 1, target + 1); // at worst, you will need target coins to make target
    coinNums[0] = 0;  // 0 coins needed to make 0

    for (int i = 1; i <= target; i++)   // for each target value
        for (int j = 0; j < n; j++)    // for each coin
            if (coins[j] <= i)          // if the coin is less than or equal to the target
                coinNums[i] = min(coinNums[i], coinNums[i - coins[j]] + 1); // add the coin to the previous best solution

    return (coinNums[target] <= target) ? coinNums[target] : -1;
}

int main() {
    cout << minCoinNumber (11, {1, 2, 5}) << "\n";
    return 0;
}
