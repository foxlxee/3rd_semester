#include <iostream>
#include <string>

// Макросы для вывода сообщений в консоль
#define PRINT_ENTER_STRING std::cout << "Введите строку: "
#define PRINT_STRING_IS_CORRECT std::cout << "Строка существует" << std::endl
#define PRINT_STRING_IS_INCORRECT std::cout << "Строка не существует" << std::endl

// Структура, являющаяся узлом в связном списке и представляющая скобку в введённой строке
struct Bracket {
private:
	static char brackets[]; // Статический массив допустимых скобок

	int m_index; // Индекс скобки в массиве
	int m_type; // Тип скобки, допустимые значения: 0, 1, 2
	bool m_tag; // Метка
	Bracket* m_next; // Указатель на следующий узел
	Bracket* m_previous; // Указатель на предыдущий узел
public:
	// Конструктор принимающий индекс скобки
	Bracket(int index) :
		m_index(index),
		m_tag(false),
		m_type(index >= 3 ? index - 3 : index),
		m_previous(nullptr),
		m_next(nullptr) {}

	// Метод возвращающий индекс скобки
	int index() {
		return m_index;
	}

	// Метод возвращающий тип скобки
	int type() {
		return m_type;
	}

	// Метод, который проверяет является ли данная скобка открытой
	bool isOpened() {
		return m_index < 3;
	}

	// Метод устанавливающий метку
	void setTag(bool tag) {
		m_tag = tag;
	}

	// Метод возвращающий метку
	bool tag() {
		return m_tag;
	}

	// Метод устанавливающий указатель на следующий узел
	void setNext(Bracket* node) {
		m_next = node;
		node->m_previous = this;
	}

	// Метод возвращающий указатель на предыдущий узел
	Bracket* previous() {
		return m_previous;
	}

	// Метод возвращающий указатель на следующий узел
	Bracket* next() {
		return m_next;
	}

	// Статический метод возвращающий индекс скобки в статическом массиве символов
	// Возвращает -1 если символа нет в массиве
	static int getBracketIndex(char c) {
		for (size_t i = 0; i < 6; i++) {
			if (brackets[i] == c) return i;
		}
		return -1;
	}
};
char Bracket::brackets[] = { '(', '{', '[', ')', '}', ']' };

int main() {
	// Устанавливаем русскую локализацию
	setlocale(LC_ALL, "Russian");

	// Запускаем цикл считывающий введенные строки
	while (true) {
		PRINT_ENTER_STRING;

		std::string str;
		std::getline(std::cin, str);

		if (str.length() == 0) continue;

		// Строим связный список
		Bracket* firstNode = nullptr;
		for (size_t i = 0; i < str.length(); i++) {
			int bracketIndex = Bracket::getBracketIndex(str[i]);
			if (bracketIndex == -1) continue;

			Bracket* node = new Bracket(bracketIndex);

			if (firstNode == nullptr) {
				firstNode = node;
				continue;
			}

			Bracket* lastNode = firstNode;
			while (lastNode->next() != nullptr) {
				lastNode = lastNode->next();
			}
			lastNode->setNext(node);
		}

		// Пробегаем связный список и проверяем корректность
		try {
			Bracket* node = firstNode;
			if (node == nullptr) throw std::exception();

			while (true) {
				if (!node->isOpened()) {
					Bracket* previousNode = node->previous();

					while (true) {
						if (previousNode == nullptr) throw std::exception();

						if (previousNode->tag()) {
							previousNode = previousNode->previous();
							continue;
						}
						break;
					}

					if (previousNode->type() != node->type()) throw std::exception();

					previousNode->setTag(true);
					node->setTag(true);
				}

				node = node->next();

				if (node == nullptr) break;
			}

			// Проверяем все ли скобки помечены и очищаем динамическую память
			bool isAllNodesMarked = true;

			node = firstNode;
			do {
				if (!node->tag()) {
					isAllNodesMarked = false;
					break;
				}
				node = node->next();
			} while (node != nullptr);

			node = firstNode;
			do {
				Bracket* nodeToDelete = node;
				node = node->next();
				delete nodeToDelete;
			} while (node != nullptr);
			
			if (!isAllNodesMarked)  throw std::exception();

			PRINT_STRING_IS_CORRECT;

		} catch (std::exception) {
			PRINT_STRING_IS_INCORRECT;
		}
	}
}