#include <iostream>
#include <vector>

using namespace std;

int LISSS(vector<int> a) {
	int n = a.size(), ret = 1;
	vector<int> lisss(n, 1);

	/* No reason to do it in reverse, this just popped into my head first */

	/* start from n-1 because lisss[n] is trivially 1 */
	for (int i = n - 1; i >= 0; i--) {

		/* start from the end and check every element until i */
		for (int j = n - 1; j > i; j--)
			/* iff a[i] < a[j] (i.e increasing subsequence) */
			if (a[i] < a[j])
				lisss[i] = max(lisss[i], 1 + lisss[j]);

		/* update global max */
		ret = max(ret, lisss[i]);
	}

	return ret;
}

int main() {
	cout << LISSS({10, 22, 9, 33, 21, 50, 41, 60, 80}) << "\n";
	return 0;
}
