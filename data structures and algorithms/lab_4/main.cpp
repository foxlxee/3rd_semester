#include <iostream>
#include <functional>

void swap(int& left, int& right);
void print(const int* arr, size_t length);
void bubbleSort(int* arr, size_t length, bool ascending = true);

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

void bubbleSort(int* arr, size_t length, bool ascending) {
	auto compare = ascending ?
		(std::function<bool(const int&, const int&)>)[](const int& left, const int& right)
		-> bool { return right < left; } :
		(std::function<bool(const int&, const int&)>)[](const int& left, const int& right)
		-> bool { return right > left; };

	for (int i = 0; i < length - 1; i++) {
		bool swapped = false;
		for (int j = 0; j < length - i - 1; j++) {
			if (compare(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break;
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

		bubbleSort(arr, N);

		std::cout << "После сортировки: ";
		print(arr, N);
	}
}