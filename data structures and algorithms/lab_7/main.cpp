#include <iostream>
#include <functional>

void swap(int& left, int& right);
void print(const int* arr, size_t length);
void shellSort(int* arr, size_t length, bool ascending = true);

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

void shellSort(int* arr, size_t length, bool ascending) {
	auto compare = ascending ?
		(std::function<bool(const int&, const int&)>)[](const int& left, const int& right)
		-> bool { return right < left; } :
		(std::function<bool(const int&, const int&)>)[](const int& left, const int& right)
		-> bool { return right > left; };
	
	size_t step = length / 2;
	while (step > 0) {
		for (size_t i = step; i < length; i++) {
			for (size_t j = i; j >= step; j -= step) {
				if (compare(arr[j - step], arr[j])) swap(arr[j], arr[j - step]);
				else break;
			}
		}
		step /= 2;
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

		shellSort(arr, N);

		std::cout << "После сортировки: ";
		print(arr, N);
	}
}