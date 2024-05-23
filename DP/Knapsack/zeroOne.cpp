#include <iostream>
#include <vector>
using namespace std;

int maxValue(vector<int> weights, vector<int> values, int cap) {
    int n = weights.size();
    vector<vector<int>> mat(n + 1, vector<int>(cap + 1, 0));

    // i = pointer to item weights/values (1 to n)
    // w = every possible capacity from 0 to cap

    // mat[i][w] = maximum value that can be obtained
    // with the first i items, and a capacity of w

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= cap; w++) {
            if (weights[i - 1] <= w) { 
                // if item i-1 fits inside capacity w
                // then it might be a contender for the max value

                int includingItem = values[i-1] + mat[i - 1][w - weights[i - 1]]; // value of item i-1 + max value that can fit in the remaining capacity
                int excludingItem = mat[i-1][w]; // max value @ previous capacity

                mat[i][w] = max(includingItem, excludingItem);

            } else {
                // if item i-1 doesn't fit in capacity w
                // then the max value has to be the same as the previous capacity

                mat[i][w] = mat[i - 1][w];
            }
        }
    }

    return mat[n][cap];
}

int main() {
    cout << maxValue({3, 1, 3, 4, 2}, {2, 2, 4, 5, 3}, 7) << "\n"; // Should output 10
    return 0;
}
