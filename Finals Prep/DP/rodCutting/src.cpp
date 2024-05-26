#include <iostream>
#include <vector>

using namespace std;

int rodCutDP (vector<int> prices) {
    int n = prices.size();
    vector<int> bestPrices (n + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        int maxPrice = 0;
        for (int j = 0; j < i; j++) {
            int priceOfCut = bestPrices[i - j - 1]; // price of cut until this index
            int priceOfRemainder = prices[j];   // price of piece left after cut
            int price = priceOfCut + priceOfRemainder;
            maxPrice = max(maxPrice, price);
        }
        bestPrices[i] = maxPrice;
    }

    return bestPrices[n];
}

int main () {
    // vector<int> prices {1, 5, 8, 9, 10, 17, 17, 20};
    vector<int> prices {1, 5, 8, 9};
    int ans = rodCutDP(prices);
    cout << ans << endl;
    return 0;
}
