#include <iostream>
#include <vector>
using namespace std;
#define INT_MIN -2147483648

// find the single most profitable transaction
int maxProfit(vector<int>& prices) {
    int ret = INT_MIN, profit = 0, N = prices.size(), temp = 0;
    for (int i = 0; i < N; i++) {
        if (i > 0)
            temp = prices[i] - prices[i-1]; //convert to MSA problem
        profit = max(temp, profit + temp);  //Kadane's algorithm on MSA
        ret = max(ret, profit);
    }
    return ret;
}

// no transaction limit + can buy and sell on the same day
int maxProfit2(vector<int>& prices) {
    int ret = 0, n = prices.size();
    for (int i = 1; i < n; i++)
        if (prices[i] > prices[i-1])    //if price on curr day is higher than prior day
            ret += (prices[i] - prices[i-1]);   //then 'buy & sell,' i.e add the difference to profit
    return ret;
}

int main() {
    vector<int> prices = {7,1,5,3,6,4};
    cout << maxProfit(prices) << "\n";
    cout << maxProfit2(prices) << "\n";
    return 0;
}