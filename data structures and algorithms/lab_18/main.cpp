#include <iostream>

// Класс, представляющий узел бинарного дерева
class BinaryTreeNode {
public:
	// Конструктор, который устанавливает все указатели равными nullptr
	BinaryTreeNode(int data = 0) : m_data(data), m_leftNode(nullptr), m_rightNode(nullptr) {}
	
	// Деструктор, который запускает удаление всех потомков по цепочке
	~BinaryTreeNode() {
		if (m_leftNode != nullptr) delete m_leftNode;
		if (m_rightNode != nullptr) delete m_rightNode;
	}

	// Метод, устанавливающий данные
	void setData(int data) {
		m_data = data;
	}

	// Метод, устанавливающий левого потомка
	void setLeftNode(BinaryTreeNode* node) {
		m_leftNode = node;
	}

	// Метод, устанавливающий правого потомка
	void setRightNode(BinaryTreeNode* node) {
		m_rightNode = node;
	}

	// Метод, возвращающий true если узел не имеет потомков
	bool leaf() {
		return m_leftNode == nullptr && m_rightNode == nullptr;
	}

	// Метод, возвращающий данные
	int data() {
		return m_data;
	}

	// Метод, возвращающий левого потомка
	BinaryTreeNode* leftNode() {
		return m_leftNode;
	}

	// Метод, возвращающий правого потомка
	BinaryTreeNode* rightNode() {
		return m_rightNode;
	}
private:
	int m_data; // Данные
	BinaryTreeNode* m_leftNode; // Левый потомок
	BinaryTreeNode* m_rightNode; // Правый потомок
};

// Класс, представляющий бинарное дерево поиска
class BinaryTree {
public:
	// Конструктор
	BinaryTree() : m_root(nullptr) {}

	// Деструктор
	~BinaryTree() {
		if (m_root != nullptr) delete m_root;
	}

	// Метод, который добавляет новый узел в дерево
	BinaryTreeNode* insert(int value) {
		// Если нет корня, создаём его и выходим
		if (m_root == nullptr) {
			m_root = new BinaryTreeNode(value);
			return m_root;
		}

		// Если есть корень, создаём указатель на него
		BinaryTreeNode* node = m_root;

		// Указатель на узел для вставки
		BinaryTreeNode* nodeToInsert = nullptr;

		// Пробегаем узлы, сравнивая значение которое вставляем, со значением узла
		while (true) {
			// Если значение меньше значения текущего узла проверяем есть ли узел слева, если нет создаём его,
			// иначе берём ссылку на узел слева и переходим на следующую итерацию цикла
			if (value < node->data()) {
				if (node->leftNode() == nullptr) {
					nodeToInsert = new BinaryTreeNode(value);
					node->setLeftNode(nodeToInsert);
					return nodeToInsert;
				}

				node = node->leftNode();
				continue;
			}

			// Если значение больше или равно значению текущего узла проверяем есть ли узел справа, если нет создаём его,
			// иначе берём ссылку на узел справа и переходим на следующую итерацию цикла
			if (node->rightNode() == nullptr) {
				nodeToInsert = new BinaryTreeNode(value);
				node->setRightNode(new BinaryTreeNode(value));
				return nodeToInsert;
			}

			node = node->rightNode();
		}
	}

	// Метод, возвращающий корень
	BinaryTreeNode* root() {
		return m_root;
	}

	// Рекурсивный метод, который выводит все элементы дерева, начиная с определённого узла
	void iterate(BinaryTreeNode* node) {
		// Проходим влево до упора
		if (node->leftNode() != nullptr) {
			iterate(node->leftNode());
		}

		// Дошли до упора, выводим значение
		std::cout << node->data() << ' ';

		// Если у узла есть правый потомок, делаем с ним тоже самое
		if (node->rightNode() != nullptr) {
			iterate(node->rightNode());
		}
	}

	// Рекурсивный метод, используемый для сортировки массива
	void sort(BinaryTreeNode* node, int* arrToSort, int* startIndex) {
		// Проходим влево до упора
		if (node->leftNode() != nullptr) {
			sort(node->leftNode(), arrToSort, startIndex);
		}

		// Записываем значение в массив и увеличиваем текущий индекс,
		// память под который выделена в методе вызвавшем текущую рекурсию
		int currentIndex = *startIndex;
		arrToSort[currentIndex] = node->data();
		*startIndex = ++currentIndex;

		// Если у узла есть правый потомок, делаем с ним тоже самое
		if (node->rightNode() != nullptr) {
			sort(node->rightNode(), arrToSort, startIndex);
		}
	}
private:
	BinaryTreeNode* m_root; // Корень дерева
};

// Функция, которая сортирует массив используя бинарное дерево поиска
void binaryTreeSort(int* arr, size_t length) {
	BinaryTree* binaryTree = new BinaryTree();

	for (size_t i = 0; i < length; i++) {
		binaryTree->insert(arr[i]);
	}

	int startIndex = 0;
	binaryTree->sort(binaryTree->root(), arr, &startIndex);

	delete binaryTree;
}

// Функция, которая выводит все элементы массива
void print(const int* arr, size_t length) {
	for (size_t i = 0; i < length; i++) {
		std::cout << arr[i];
		if (i != length - 1) std::cout << ' ';
	}
	std::cout << std::endl;
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

		binaryTreeSort(arr, N);

		std::cout << "После сортировки: ";
		print(arr, N);
	}
}