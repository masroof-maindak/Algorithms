#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

/* Garbage implementation probably? */
/* Median of medians */
int indexOfMedian(std::vector<int> &nums, int left, int right) {
	if (right - left < 5) {
		std::sort(nums.begin() + left, nums.begin() + right + 1);
		return left + (right - left) / 2;
	}

	for (int i = left; i < right; i += 5) {
		int bucketEndIndex = std::min(i + 4, right);
		int medianOfBucket = indexOfMedian(nums, i, bucketEndIndex);
		/* Place i'th bucket's median at i'th position */
		std::swap(nums[medianOfBucket], nums[left + (i - left) / 5]);
	}

	/* Recursively find median of medians (i.e first 'numOfBuckets' number of
	 * elements) */
	return indexOfMedian(nums, left,
						 left + (int)std::ceil((right - left) / 5.0) - 1);
}

int partition(std::vector<int> &v, int l, int r, bool randPivot) {
	int pi = (randPivot) ? l + rand() % (r - l + 1) : indexOfMedian(v, l, r);
	int p  = v[pi];

	std::swap(v[pi], v[r]);

	int i = l - 1;
	for (int j = l; j < r; j++)
		if (v[j] < p)
			std::swap(v[++i], v[j]);

	std::swap(v[i + 1], v[r]);

	return i + 1;
}

void quicksort(std::vector<int> &v, int l, int r, bool randPivot) {
	if (l < r) {
		int pi = partition(v, l, r, randPivot);
		quicksort(v, l, pi - 1, randPivot);
		quicksort(v, pi + 1, r, randPivot);
	}
}

int main(int argc, char *argv[]) {
	srand(time(0));

	std::vector<int> nums;
	int num;

	std::ifstream numfile("numbers.txt");

	if (!numfile)
		return -1;

	while (numfile >> num)
		nums.push_back(num);

	numfile.close();

	std::string pivotSel = argv[1];

	if (pivotSel == "random")
		quicksort(nums, 0, nums.size() - 1, true);
	else if (pivotSel == "median")
		quicksort(nums, 0, nums.size() - 1, false);

	return 0;
}
