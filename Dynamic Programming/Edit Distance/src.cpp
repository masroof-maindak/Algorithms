#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/* Given two strings x and y, return the minimum number of operations required
 * to convert x to y */
int minDistance(string x, string y) {
	int m = x.size(), n = y.size();
	vector<vector<int>> mat(m + 1, vector<int>(n + 1));

	if (m == 0)
		return n;

	if (n == 0)
		return m;

	/* Cost to reach end of y */
	for (int i = 1; i <= m; i++)
		mat[i][0] = i;

	/* Cost to reach end of x */
	for (int j = 1; j <= n; j++)
		mat[0][j] = j;

	/* Iterate through x */
	for (int i = 1; i <= m; i++) {
		/* Iterate through y */
		for (int j = 1; j <= n; j++) {

			/* if the characters are the same, it's a NOP. If not, the new cost
			 * will be either the cost of deleting x[i] or y[i], or replacing
			 * the former with the latter */

			if (x[i - 1] == y[j - 1])
				mat[i][j] = mat[i - 1][j - 1];
			else
				mat[i][j] =
					min({mat[i - 1][j], mat[i][j - 1], mat[i - 1][j - 1]}) + 1;
		}
	}

	return mat[m][n];
}

int main() {
	cout << minDistance("a", "ab") << "\n";
	return 0;
}
