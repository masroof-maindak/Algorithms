#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Given two strings x and y, return the minimum number of operations required to convert x to y
int minDistance(string x, string y) {
    int m = x.size(), n = y.size();
    vector<vector<int>> mat(m+1, vector<int>(n+1));

    if (m == 0)
        return n;

    if (n == 0)
        return m;

    for (int i = 1; i <= m; i++)
        mat[i][0] = i; // cost to reach end of y

    for (int j = 1; j <= n; j++)
        mat[0][j] = j; // cost to reach end of x

    for (int i = 1; i <= m; i++) { // iterate through x
        for (int j = 1; j <= n; j++) { // iterate through y
            if (x[i-1] == y[j-1]) // if the characters are the same
                mat[i][j] = mat[i-1][j-1]; // no operation needed (no cost/change in length, copy previous value)
            else
                mat[i][j] = min({mat[i-1][j], mat[i][j-1], mat[i-1][j-1]}) + 1;
                /*
                min cost of the three operations:
                    mat[i-1][j] -> delete x[i] (cost at previous row) row corresponds to x
                    mat[i][j-1] -> insert y[j] to x (cost at previous column) column corresponds to y
                    mat[i-1][j-1] -> replace x[i] with y[j] (cost at diagonal) corresponds
                */
        }
    }

    return mat[m][n];
}

int main () {
    cout << minDistance("a", "ab") << "\n";
    return 0;
}
