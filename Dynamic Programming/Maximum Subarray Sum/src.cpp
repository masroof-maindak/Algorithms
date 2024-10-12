#include <climits>
#include <iostream>

using namespace std;

int max(int a, int b) { return (a > b) ? a : b; }

int max(int a, int b, int c) { return max(max(a, b), c); }

int maxCrossingSum(int arr[], int left, int mid, int right) {
	int sum		= 0;
	int leftSum = INT_MIN, rightSum = INT_MIN;

	for (int i = mid; i >= left; i--) {
		sum += arr[i];
		leftSum = max(leftSum, sum);
	}

	sum = 0;
	for (int i = mid; i <= right; i++) {
		sum += arr[i];
		rightSum = max(rightSum, sum);
	}

	return max(leftSum + rightSum - arr[mid], leftSum, rightSum);
}

int divideAndConquer(int arr[], int left, int right) {
	if (left > right)
		return INT_MIN;

	if (left == right)
		return arr[left];

	int mid = (left + right) / 2;

	return max(divideAndConquer(arr, left, mid - 1),
			   divideAndConquer(arr, mid + 1, right),
			   maxCrossingSum(arr, left, mid, right));
}

int kadane(int arr[], int size) {
	int prevLocalMax = 0, globalMax = INT_MIN;

	for (int i = 0; i < size; i++) {
		prevLocalMax = max(arr[i], prevLocalMax + arr[i]);
		globalMax	 = max(prevLocalMax, globalMax);
	}

	return globalMax;
}

int main() {
	int arr[] = {2, 3, 4, 5, 7};
	int size  = sizeof(arr) / sizeof(arr[0]);
	cout << "Maximum contiguous sum is " << divideAndConquer(arr, 0, size - 1)
		 << "\n";
	cout << "Maximum contiguous sum is " << kadane(arr, size) << "\n";
	return 0;
}
