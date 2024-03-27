#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

int indexOfMedian (std::vector<int>& nums, int left, int right) {
    if (right - left < 5) {
        std::sort(nums.begin() + left, nums.begin() + right + 1);
        return left + (right - left) / 2;
    }

    for (int i = left; i < right; i += 5) {
        int bucketEndIndex = std::min(i + 4, right);
        int medianOfBucket = indexOfMedian(nums, i, bucketEndIndex);
        std::swap(nums[medianOfBucket], nums[left + (i - left) / 5]);
    }

    return indexOfMedian(nums, left, left + (int)std::ceil((right - left) / 5.0) - 1);
}

int partition(std::vector<int>& nums, int left, int right, bool useRandom) {
    int pivotIndex = (useRandom) ? left + rand() % (right - left + 1) : indexOfMedian(nums, left, right);
    int pivot = nums[pivotIndex];
    std::swap(nums[pivotIndex], nums[right]);
    int i = left - 1;
    for (int j = left; j < right; j++)
        if (nums[j] < pivot)
            std::swap(nums[++i], nums[j]);
    std::swap(nums[i + 1], nums[right]);
    return i + 1;
}

void quicksort(std::vector<int>& nums, int left, int right, bool useRandom) {
    if (left < right) {
        int pivotIndex = partition(nums, left, right, useRandom);
        quicksort(nums, left, pivotIndex - 1, useRandom);
        quicksort(nums, pivotIndex + 1, right, useRandom);
    }
}

int main(int argc, char* argv[]) {
    srand(time(0));

    std::ifstream numfile("numbers.txt");
    std::vector<int> nums;
    int num;
    while (numfile >> num)
        nums.push_back(num);
    numfile.close();

    std::string pivotMethod = argv[1];

    if (pivotMethod == "random")
        quicksort(nums, 0, nums.size() - 1, true);
    else if (pivotMethod == "median")
        quicksort(nums, 0, nums.size() - 1, false);

    return 0;
}
