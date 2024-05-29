#include <iostream>
#include <vector>
using namespace std;

bool subsetSum(vector<int> values, int sum) {
    int n = values.size();
    vector<vector<bool>> mat(n + 1, vector<bool>(sum + 1, false));

    /*
        i = pointer to item weights/values (1 to n)
        j = every possible sum from 0 to s

        mat[i][j] = true if subset with sum j can
        be attained using the first `i` items
    */

    // sum = 0 is always possible (by simply not including the item)
    for (int i = 0; i <= n; i++)
        mat[i][0] = true;

    for (int i = 1; i <= n; i++) // consider a new value (item) each time
        for (int j = 1; j <= sum; j++) // for every possible sum

             // if the value of this new item is greater than this particular sum, don't include it (copy over last subset's result)
            if (values[i-1] > j)
                mat[i][j] = mat[i-1][j];
            
            // find the subset with sum `j` by excluding or including the i'th item (whichever is possible)
            else
                mat[i][j] = (mat[i-1][j]) or (mat[i-1][j - values[i-1]]); 
                // former = value at sum, excluding this item
                // latter = value at sum - value of this item

    return mat[n][sum];
}

int main() {
    cout << subsetSum({3, 34, 4, 12, 5, 2}, 9) << "\n";
    return 0;
}