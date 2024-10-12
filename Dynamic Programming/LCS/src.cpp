#include <iostream>
#include <vector>

using namespace std;

int longestCommonSubsequence(string x, string y) {
	int m = x.size(), n = y.size();
	vector<vector<int>> mat(m + 1, vector<int>(n + 1, 0));

	/* 2d matrix to store the length of LCS */
	/* mat[i][j] = LCS of x[i..m] and y[j..n] */

	/*
	 * IDEA:
	 * If the values at index i and j are equal, we increment the LCS
	 * Else, whatever the previous highest value was, persists
	 */

	for (int i = m - 1; i >= 0; i--)
		for (int j = n - 1; j >= 0; j--)
			if (x[i] == y[j])
				mat[i][j] = 1 + mat[i + 1][j + 1];
			else
				mat[i][j] = max(mat[i][j + 1], mat[i + 1][j]);

	return mat[0][0];
}

int main() {
	cout << longestCommonSubsequence("aab", "xaya") << "\n";
	return 0;
}
