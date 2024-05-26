#include <iostream>
#include <vector>
using namespace std;
 
bool subsetSum(vector<int> values, int sum) {
    int n = values.size();
    vector<vector<bool>> mat(n + 1, vector<bool>(sum + 1, false));
 
    // i = pointer to item weights/values (1 to n)
    // w = every possible sum from 0 to sum

    // mat[i][j] = true if subset with sum j can
    // be attained using the first `i` items
 
    // if 0 items in the list and the sum is non-zero
    for (int j = 1; j <= sum; j++)
        mat[0][j] = false;
 
    // if the sum is zero
    for (int i = 0; i <= n; i++)
        mat[i][0] = true;
 
    for (int i = 1; i <= n; i++) // consider a new value each time
        for (int j = 1; j <= sum; j++) // for every possible sum
            if (values[i - 1] > j) // if the value of this new time is greater than this particular sum, don't include it
                mat[i][j] = mat[i - 1][j];
            else // find the subset with sum `j` by excluding or including the i'th item
                mat[i][j] = (mat[i - 1][j]) or (mat[i - 1][j - values[i - 1]]); // latter = value at sum - value of this item
 
    return mat[n][sum];
}
 
int main() {
    cout << subsetSum({3, 34, 4, 12, 5, 2}, 9) << "\n";
    return 0;
}