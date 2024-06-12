#include <iostream>
#include <algorithm>
#include <vector>

int main() {
	setlocale(LC_ALL, "Russian");

	std::vector<unsigned int> vector;

	while (true) {
		std::cout << "Введите x: ";

		unsigned int x;
		std::cin >> x;

		if (x == UINT_MAX) continue;

		// Находим все числа от 1 до x, которые можно выразить как произведение множителей 3, 5 и 7
		// в натуральных степенях или в степени 0: { N U {0} }
		for (size_t k = 1; k <= x; k *= 3) {
			for (size_t l = 1; k * l <= x; l *= 5) {
				for (size_t m = 1, result; (result = k * l * m) <= x; m *= 7) {
					vector.push_back(result);
				}
			}
		}

		// Выводим
		if (vector.size() > 0) {
			std::sort(vector.begin(), vector.end());
			for (size_t i = 0; i < vector.size(); i++) {
				std::cout << vector[i];
				if (i != vector.size() - 1) std::cout << ", ";
			}
			vector.clear();
		}

		std::cout << std::endl;
	}
}