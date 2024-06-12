#include <iostream>
#include <functional>

void swap(int& left, int& right);
void print(const int* arr, size_t length);
void quickSort(int* arr, size_t length, bool ascending = true);
void sort(int* arr, int start, int end, std::function<bool(const int&, const int&)>& compare);

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

void quickSort(int* arr, size_t length, bool ascending) {
	auto compare = ascending ?
		(std::function<bool(const int&, const int&)>)[](const int& left, const int& right)
		-> bool { return right > left; } :
		(std::function<bool(const int&, const int&)>)[](const int& left, const int& right)
		-> bool { return right < left; };

	sort(arr, 0, length - 1, compare);
}

void sort(int* arr, int start, int end, std::function<bool(const int&, const int&)>& compare) {
	if (start < end) {
		int current = start;
		for (int i = start + 1; i <= end; i++) {
			if (compare(arr[i], arr[start])) {
				swap(arr[++current], arr[i]);
			}
		}

		swap(arr[start], arr[current]);

		sort(arr, start, current - 1, compare);
		sort(arr, current + 1, end, compare);
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

		quickSort(arr, N);

		std::cout << "После сортировки: ";
		print(arr, N);
	}
}