#include <iostream>

void swap(int& left, int& right);
void print(const int* arr, size_t length);
void heapify(int* arr, size_t length, int i);
void heapSort(int* arr, size_t length);

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

void heapify(int* arr, size_t length, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < length && arr[l] > arr[largest]) largest = l;
	if (r < length && arr[r] > arr[largest]) largest = r;

	if (largest != i) {
		swap(arr[i], arr[largest]);
		heapify(arr, length, largest);
	}
}

void heapSort(int* arr, size_t length) {
	for (int i = length / 2 - 1; i >= 0; i--) heapify(arr, length, i);

	for (int i = length - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
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

		heapSort(arr, N);

		std::cout << "После сортировки: ";
		print(arr, N);
	}
}