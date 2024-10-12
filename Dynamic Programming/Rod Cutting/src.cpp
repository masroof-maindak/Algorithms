#include <iostream>
#include <vector>
using namespace std;

int rodCutDP (vector<int> prices) {
    int n = prices.size();
    vector<int> bestPrices (n + 1, 0);

    /* bestPrices[i] = best price for a rod of length i */
    /* price @ length 0 = trivially 0 */

    for (int i = 1; i <= n; i++) {
        int maxPrice = 0;
        for (int j = 0; j < i; j++) {
            int priceOfCut = bestPrices[i - j - 1];
            int priceOfRemainder = prices[j];
            int price = priceOfCut + priceOfRemainder;
            maxPrice = max(maxPrice, price);
        }
        bestPrices[i] = maxPrice;
    }

    return bestPrices[n];
}

int main () {
    cout << rodCutDP({1, 5, 8, 9}) << "\n";
    return 0;
}
