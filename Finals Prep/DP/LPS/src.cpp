#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int longestCommonSubsequence(string x, string y) {
    int m = x.size(), n = y.size();
    vector<vector<int>> mat (m+1, vector<int>(n+1, 0));

    for (int i = m-1; i >= 0; i--)
        for (int j = n-1; j >= 0;j--)
            if (x[i] == y[j])   //if equal, LCS size increases
                mat[i][j] = 1 + mat[i+1][j+1];
            else                //if not equal, it remains as is              
                mat[i][j] = max(mat[i][j+1], mat[i+1][j]);

    return mat[0][0];
}

// Longest Palindromic Subsequence
int LPS (string s) {
    // LPS(s) = LCS(s, reverse(s))
    string rev = s;
    reverse(rev.begin(), rev.end());
    return longestCommonSubsequence(s, rev);
}

int main() {
    cout << LPS("bbab") << "\n";
    return 0;
}