#include <iostream>
#include <vector>

using namespace std;

int lengthOfLIS(vector<int> a) {
	int n = a.size(), ret = 1;
	vector<int> lisss(n, 1);

	if (n < 0)
		return 0;

	/* No reason to do it in reverse, this just popped into my head first */
	for (int i = n - 2; i >= 0; i--) {
		for (int j = n - 1; j > i; j--)
			if (a[i] < a[j])
				lisss[i] = max(lisss[i], 1 + lisss[j]);
		ret = max(ret, lisss[i]);
	}

	return ret;
}

int lengthOfLDIS(vector<int> a) {
	int n = a.size(), ret = 1;
	vector<int> ldiss(n, 1);

	if (n == 0)
		return 0;

	for (int i = n - 2; i >= 0; i--) {
		for (int j = n - 1; j > i; j--)
			if (2 * a[i] < a[j])
				ldiss[i] = max(ldiss[i], 1 + ldiss[j]);
		ret = max(ret, ldiss[i]);
	}

	return ret;
}

int main() {
	cout << lengthOfLIS({10, 22, 9, 33, 21, 50, 41, 60, 80}) << "\n";
	cout << lengthOfLDIS({10, 22, 9, 45, 21, 50, 41, 60, 91}) << "\n";
	return 0;
}
