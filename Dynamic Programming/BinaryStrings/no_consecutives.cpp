/* Develop a dynamic programming algorithm to compute the total number of binary
 * strings of length N such that no two consecutive bits in the string are
 * both 1. For instance, if N = 3, the algorithm should return 5, corresponding
 * to the strings: 000, 001, 010, 100, and 101.
 */

/* Higher efficiency will be rewarded with additional credit. */

/* (a) Clearly specify the subproblems you will define to construct the
 * solution. */

/* (b) Derive the recurrence relation that connects these subproblems and leads
 * to the final answer. */

/* Hint: Define subproblems based on the value of the last bit. Count the binary
 * strings that end at 0 and 1 separately. Define recurrence relations for both
 * counts. */

#include <iostream>
#include <vector>

using namespace std;

size_t count_strings(size_t n) {
	vector<size_t> a(n), b(n);
	a[0] = b[0] = 1;

	for (int i = 1; i < n; i++) {
		a[i] = a[i - 1] + b[i - 1];
		b[i] = a[i - 1];
	}

	return a[n - 1] + b[n - 1];
}

int main() {
	cout << count_strings(10) << endl;
	return 0;
}
