#include <iostream>

void swap(int& left, int& right);
void print(const int* arr, size_t length);
void merge(int* arr, int left, int mid, int right);
void mergeSort(int* arr, int begin, int end);

void swap(int& left, int& right) {
	int temp = left;
	left = right;
	right = temp;
}

void print(const int* arr, size_t length) {
	for (size_t i = 0; i < length; i++) {
		std::cout << arr[i];
		if (i != length - 1) std::cout << ' ';
	}
	std::cout << std::endl;
}

void merge(int* arr, int left, int mid, int right) {
	int subArrOne = mid - left + 1;
	int subArrTwo = right - mid;

	int* leftArr = new int[subArrOne];
	int* rightArr = new int[subArrTwo];

	for (int i = 0; i < subArrOne; i++) leftArr[i] = arr[left + i];
	for (int j = 0; j < subArrTwo; j++) rightArr[j] = arr[mid + 1 + j];

	int indexOfSubArrOne = 0;
	int indexOfSubArrTwo = 0;
	int indexOfMergedArr = left;

	while (indexOfSubArrOne < subArrOne && indexOfSubArrTwo < subArrTwo) {
		if (leftArr[indexOfSubArrOne] <= rightArr[indexOfSubArrTwo]) {
			arr[indexOfMergedArr] = leftArr[indexOfSubArrOne];
			indexOfSubArrOne++;
		} else {
			arr[indexOfMergedArr] = rightArr[indexOfSubArrTwo];
			indexOfSubArrTwo++;
		}
		indexOfMergedArr++;
	}

	while (indexOfSubArrOne < subArrOne) {
		arr[indexOfMergedArr] = leftArr[indexOfSubArrOne];
		indexOfSubArrOne++;
		indexOfMergedArr++;
	}

	while (indexOfSubArrTwo < subArrTwo) {
		arr[indexOfMergedArr] = rightArr[indexOfSubArrTwo];
		indexOfSubArrTwo++;
		indexOfMergedArr++;
	}

	delete[] leftArr;
	delete[] rightArr;
}

void mergeSort(int* arr, int begin, int end) {
	if (begin >= end) return;

	int mid = begin + (end - begin) / 2;
	mergeSort(arr, begin, mid);
	mergeSort(arr, mid + 1, end);
	merge(arr, begin, mid, end);
}

int main() {
#define N 10
	setlocale(LC_ALL, "Russian");

	while (true) {
		std::cout << "Введите последовательность из " << N << " чисел: ";

		int arr[N];
		for (size_t i = 0; i < N; i++) std::cin >> arr[i];

		std::cout << "До сортировки: ";
		print(arr, N);

		mergeSort(arr, 0, N - 1);

		std::cout << "После сортировки: ";
		print(arr, N);
	}
}