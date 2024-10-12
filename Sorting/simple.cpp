#include <algorithm>
#include <iostream>
#include <vector>

void bubbleSort(std::vector<int> &v) {
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < v.size() - i - 1; j++)
			if (v[j] > v[j + 1])
				std::swap(v[j], v[j + 1]);
}

void selectionSort(std::vector<int> &v) {
	for (int i = 0; i < v.size(); i++) {
		int min = i;
		for (int j = i + 1; j < v.size(); j++)
			if (v[j] < v[min])
				min = j;
		std::swap(v[i], v[min]);
	}
}

void insertionSort(std::vector<int> &v) {
	for (int i = 1; i < v.size(); i++) {
		int key = v[i];
		int j	= i - 1;
		while (j >= 0 and v[j] > key) {
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = key;
	}
}

int main() {
	std::vector<int> x = {1, 10, 124, 32, 101, 23, 81, 40, 23, 242};
	bubbleSort(x);
	for (int i : x)
		std::cout << i << " ";
	return 0;
}
