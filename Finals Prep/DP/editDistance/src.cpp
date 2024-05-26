#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minDistance(string x, string y) {
    int m = x.size(), n = y.size();
    vector<vector<int>> mat(m+1, vector<int>(n+1));

    if (m == 0)
        return n;

    if (n == 0)
        return m;

    for (int i = 1; i <= m; i++)
        mat[i][0] = i;

    for (int j = 1; j <= n; j++)
        mat[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i-1] == y[j-1])
                mat[i][j] = mat[i-1][j-1];
            else
                mat[i][j] = min({mat[i-1][j], mat[i][j-1], mat[i-1][j-1]}) + 1;
        }
    }

    return mat[m][n];
}

int main () {
    cout << minDistance("a", "ab") << "\n";
    return 0;
}
