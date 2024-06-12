#include <iostream>
#include <fstream>
#include <sstream>

// Класс, который определяет элемент в таблице
class HashTableItem {
public:
	// Конструктор, который принимает ссылку на строку, которая будет скопирована в m_data
	HashTableItem(const std::string& data) : m_data(data) {}

	// Метод, который возвращает константную ссылку на строку
	const std::string& data() {
		return m_data;
	}

	// Метод, который возвращает хеш значение
	int hash() const {
		int hash = 0;

		for (size_t i = 0; i < m_data.length(); i++) {
			hash = (hash << 8) + m_data[i];
			if (i == sizeof(int) - 1) break;
		}

		return hash < 0 ? hash * -1 : hash;
	}
private:
	std::string m_data;
};

// Класс, который определяет хеш таблицу с наложением (открытой адресацией)
class HashTable {
public:
	// Конструктор, который по умолчанию выделяет динамическую память для 8 указателей на объекты класса HashTableItem
	HashTable() : m_length(8), m_arr(new HashTableItem*[m_length] { nullptr }) {}

	// Метод, который вставляет элемент в таблицу
	void insert(HashTableItem* itemToInsert) {
		// Вычисляем индекс в массиве
		size_t index = itemToInsert->hash() % m_length;

		// Проверяем если по этому индексу значение nullptr, записываем туда указатель
		// Иначе у нас коллизия
		if (m_arr[index] == nullptr) {
			m_arr[index] = itemToInsert;
		} else {
			// Обрабатываем коллизию
			for (size_t i = 0; i < m_length; i++) {
				if (m_arr[i] == nullptr) {
					m_arr[i] = itemToInsert;
					break;
				}
			}
		}

		m_amountOfAddedElements++;
		realloc();
	}

	// Метод, который очищает таблицу
	void clear() {
		release();
		m_length = 8;
		m_amountOfAddedElements = 0;
		m_arr = new HashTableItem*[m_length];
	}

	// Метод, который считывает таблицу из файла содержащего текст
	bool loadFromFile(const std::string& filePath) {
		if (m_amountOfAddedElements > 0) clear();

		std::ifstream file;
		file.open(filePath);

		if (!file.is_open()) return false;

		std::string word;
		while (file >> word) {
			insert(new HashTableItem(word));
		}

		return true;
	}

	// Метод, который записывает таблицу в файл
	bool writeToFile(const std::string& filePath) {
		std::ofstream file;
		file.open(filePath);

		if (!file.is_open()) return false;

		file << "Hash table" << std::endl;

		for (size_t i = 0; i < m_length; i++) {
			file << i << ": " << (m_arr[i] == nullptr ? "null" : m_arr[i]->data()) << std::endl;
		}

		file.flush();
		file.close();

		return true;
	}

	// Деструктор
	~HashTable() {
		release();
	}
private:
	size_t m_length; // Длина массива
	size_t m_amountOfAddedElements; // Количество добавленных элементов
	HashTableItem** m_arr; // Указатель на начало массива указателей в динамической памяти

	// Метод, который освобождает всю динамическую память
	void release() {
		for (size_t i = 0; i < m_length; i++) {
			if (m_arr[i] != nullptr) {
				delete m_arr[i];
			}
		}
		delete[] m_arr;
	}

	// Метод, который перевыделяет память если массив заполнен более чем на 90%
	void realloc() {
		if ((float)m_amountOfAddedElements / m_length > 0.9) {
			size_t newLength = m_length * 2;
			HashTableItem** newArr = new HashTableItem*[newLength];

			// Копируем всё
			for (size_t i = 0; i < newLength; i++) {
				newArr[i] = i < m_length ? m_arr[i] : nullptr;
			}

			// Удаляем старый массив
			HashTableItem** arrToDelete = m_arr;
			m_arr = newArr;
			delete[] arrToDelete;

			m_length = newLength;
		}
	}
};

int main() {
	HashTable hashTable;

	hashTable.insert(new HashTableItem("Apple"));
	hashTable.insert(new HashTableItem("Google"));
	hashTable.insert(new HashTableItem("Microsoft"));
	hashTable.insert(new HashTableItem("Xiaomi"));
	hashTable.insert(new HashTableItem("Samsung"));
	hashTable.insert(new HashTableItem("Apple"));
	hashTable.insert(new HashTableItem("Microsoft"));

	hashTable.writeToFile("out.txt");
}