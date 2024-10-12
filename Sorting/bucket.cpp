#include <algorithm>
#include <iostream>
#include <vector>

void bucketSort(std::vector<int> &arr) {
	int n = arr.size();
	if (n == 0 or n == 1)
		return;

	/* Find max */
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];

	/* Make buckets */
	int num_buckets = max / 10 + 1;
	std::vector<std::vector<int>> buckets(num_buckets);

	/* Place elements */
	for (int x : arr)
		buckets[(x / 10)].push_back(x);

	/* Sort individual buckets */
	for (int i = 0; i < num_buckets; i++)
		std::sort(buckets[i].begin(), buckets[i].end());

	/* Concatenate */
	int index = 0;
	for (int i = 0; i < num_buckets; i++)
		for (int j = 0; j < buckets[i].size(); j++)
			arr[index++] = buckets[i][j];
}

int main() {
	std::vector<int> x = {1, 10, 124, 32, 101, 23, 81, 40, 23, 242};
	bucketSort(x);
	for (int i : x)
		std::cout << i << " ";
	return 0;
}
