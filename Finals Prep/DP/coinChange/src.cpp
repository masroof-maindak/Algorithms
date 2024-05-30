#include <iostream>
#include <vector>
using namespace std;

int min (int a, int b) {
    return a < b ? a : b;
}

int minCoinNumber (int target, vector<int> coins) {
    //same principle as rod cutting. Add what's left to the previous 'best' solution
    vector<int> coinNum(target + 1, target + 1); // at worst, you will need 'target' coins to make target
    coinNum[0] = 0;  // 0 coins needed to make 0 ('base case')

    for (int i = 1; i <= target; i++)  // for each target value, starting from 1 (0 is already solved)
        for (int coinVal : coins)     // for each coin value
            if (coinVal <= i)          // if the value is less than or equal to the target
                coinNum[i] = min(coinNum[i], coinNum[i - coinVal] + 1); // add the coin to the previous best solution
            //coinNum[100] = min(coinNum[100], coinNum[98] + 1)
    
    return (coinNum[target] <= target) ? coinNum[target] : -1; 
    // if the value at the target's index is still target+1, it means the target value is not possible
}

int main() {
    cout << minCoinNumber (11, {1, 2, 5}) << "\n";
    return 0;
}
