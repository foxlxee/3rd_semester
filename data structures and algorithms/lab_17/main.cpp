#include <iostream>
#include <sstream>
#include <stack>

// Класс, представляющий узел бинарного дерева
class BinaryTreeNode {
public:
	// Конструктор, который устанавливает все указатели равными nullptr
	BinaryTreeNode(int data = 0) : m_data(data), m_leftNode(nullptr), m_rightNode(nullptr) {}

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

	// Конструктор, устанавливающий корень
	BinaryTree(BinaryTreeNode* root) : m_root(root) {}

	// Деструктор
	~BinaryTree() {
		deallocPostOrderTraversal(m_root);
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

	// Метод, который удаляет узел из дерева
	bool remove(int data) {
		bool result = false;
		m_root = remove(m_root, data, &result);
		return result;
	}

	// Метод, который возвращает true если элемент существует
	bool search(BinaryTreeNode* node, int value) {
		if (node == nullptr) return false;
		if (node->data() == value) return true;

		bool leftResult = search(node->leftNode(), value);
		if (leftResult) return true;

		bool rightResult = search(node->rightNode(), value);
		return rightResult;
	}

	// Метод, возвращающий корень
	BinaryTreeNode* root() {
		return m_root;
	}

	// Прямой обход
	void traversePreOrder(BinaryTreeNode* node) {
		if (node == nullptr) return;

		std::cout << node->data() << ' ';
		traversePreOrder(node->leftNode());
		traversePreOrder(node->rightNode());
	}

	// Центральный обход
	void traverseInOrder(BinaryTreeNode* node) {
		if (node == nullptr) return;

		traverseInOrder(node->leftNode());
		std::cout << node->data() << ' ';
		traverseInOrder(node->rightNode());
	}

	// Концевой обход
	void traversePostOrder(BinaryTreeNode* node) {
		if (node == nullptr) return;

		traversePostOrder(node->leftNode());
		traversePostOrder(node->rightNode());
		std::cout << node->data() << ' ';
	}
private:
	BinaryTreeNode* m_root; // Корень дерева

	void deallocPostOrderTraversal(BinaryTreeNode* root) {
		if (root != nullptr) {
			deallocPostOrderTraversal(root->leftNode());
			deallocPostOrderTraversal(root->rightNode());
			delete root;
		}
	}

	BinaryTreeNode* remove(BinaryTreeNode* root, int data, bool* exists) {
		if (root == nullptr) return nullptr;
		else if (data < root->data()) root->setLeftNode(remove(root->leftNode(), data, exists));
		else if (data > root->data()) root->setRightNode(remove(root->rightNode(), data, exists));
		else {
			if (!*exists) *exists = true;

			// Случай, когда у узла нет потомков
			if (root->leaf()) {
				delete root;
				root = nullptr;
			}
			// Случай, когда у узла один потомок
			else if (root->leftNode() == nullptr) {
				BinaryTreeNode *temp = root;
				root = root->rightNode();
				delete temp;
			} else if (root->rightNode() == nullptr) {
				BinaryTreeNode *temp = root;
				root = root->leftNode();
				delete temp;
			}
			// Случай, когда у узла два потомока
			else {
				BinaryTreeNode *temp = root->rightNode();
				for (; temp->leftNode() != nullptr; temp = temp->leftNode()) {}
				root->setData(temp->data());
				root->setRightNode(remove(root->rightNode(), temp->data(), exists));
			}
		}
		return root;
	}
};

// Класс, который создаёт дерево по строке
class BinaryTreeParser {
public:
	// Метод, который возвращает дерево
	static BinaryTree* parse(std::string str) {
		BinaryTreeNode* root = getNode(str, 0, str.length() - 1);
		if (root == nullptr) return nullptr;
		return new BinaryTree(root);
	}

	// Метод, который создаёт строку по дереву
	// В строку вводится сначала корень потом (левое поддерево) (правое поддерево)
	// X означает что нет узла, например: 50 X (100 (50 X X) (45 X X))
	static std::string toString(BinaryTree* binaryTree) {
		BinaryTreeNode* node = binaryTree->root();

		if (node == nullptr) throw std::exception("У дерева нет корня");

		std::stringstream stream;
		stream << node->data();
		stream << ' ';

		fill(stream, node);
		
		return stream.str();
	}
private:
	// Рекурсивный метод, который возвращает корневой узел
	static BinaryTreeNode* getNode(std::string str, int startIndex, int endIndex) {
		if (startIndex > endIndex) return nullptr;

		// Пропускаем пробельные символы и символ открывающей скобки
		while (str[startIndex] == ' ' || str[startIndex] == '\t' || str[startIndex] == '(') {
			startIndex++;
		}

		// Вычисляем значение узла
		int value = 0;
		while (startIndex <= endIndex && str[startIndex] >= '0' && str[startIndex] <= '9') {
			value *= 10;
			value += (str[startIndex] - '0');
			startIndex++;
		}

		// Пропускаем пробельные символы
		while (str[startIndex] == ' ' || str[startIndex] == '\t') {
			startIndex++;
		}

		// Создаём узел
		BinaryTreeNode* node = new BinaryTreeNode();
		node->setData(value);

		// Вычисляем индекс закрывающей скобки
		int index = -1;
		if (startIndex <= endIndex && str[startIndex] == '(') {
			std::stack<char> stack;
			for (int i = startIndex; i <= endIndex; i++) {
				if (str[i] == '(') stack.push(str[i]);
				else if (str[i] == ')') {
					if (stack.top() == '(') {
						stack.pop();
						if (stack.empty()) {
							index = i;
							break;
						}
					}
				}
			}
		}

		// Если индекс существует, создаём поддеревья
		if (index != -1) {
			node->setLeftNode(getNode(str, startIndex + 1, index - 1));
			node->setRightNode(getNode(str, index + 1, endIndex - 1));
		}

		// Возвращаем узел
		return node;
	}

	// Рекурсивный метод, который заполняет строку
	static void fill(std::stringstream& stream, BinaryTreeNode* node) {
		if (node->leftNode() != nullptr) {
			stream << '(';
			stream << node->leftNode()->data();
			if (!node->leaf()) stream << ' ';
			fill(stream, node->leftNode());
			stream << ')';
			stream << ' ';
		} else {
			stream << "X ";
		}

		if (node->rightNode() != nullptr) {
			stream << '(';
			stream << node->rightNode()->data();
			if (!node->leaf()) stream << ' ';
			fill(stream, node->rightNode());
			stream << ')';
			return;
		} else {
			stream << " X ";
			return;
		}

		stream << ' ';
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	/* Пример ввода с помощью строки
	// Дерево создаётся с помощью линейно-скобочной записи
	// Сначала идёт корень, потом в скобках (левое поддерево) (правое поддерево)
	BinaryTree* binaryTree = BinaryTreeParser::parse("69 (45 (100) (200))");

	std::cout << "Центральный обход: ";
	binaryTree->traverseInOrder(binaryTree->root());
	std::cout << std::endl;

	std::cout << BinaryTreeParser::toString(binaryTree);
	*/

	BinaryTree* binaryTree = new BinaryTree();

	std::cout << "Введите\n\t1 чтобы добавить узел\n\t2 чтобы удалить узел\n\t3 чтобы найти узел\n\t4 чтобы вывести дерево\n\t5 чтобы выйти";
	std::cout << std::endl;

	// Меню
	while (true) {
		int key;
		std::cin >> key;

		switch (key) {
			// Добавление узла
			case 1:
				std::cout << "Добавление узла: ";
				std::cin >> key;
				binaryTree->insert(key);
				std::cout << "Узел добавлен" << std::endl;
				break;
			// Удаление узла
			case 2:
				std::cout << "Удаление узла: ";
				std::cin >> key;
				std::cout << (binaryTree->remove(key) ?
					"Все узлы с введённым значением удалены" : "Узел не существует");
				break;
			// Поиск узла
			case 3:
				std::cout << "Поиск узла: ";
				std::cin >> key;
				std::cout << (binaryTree->search(binaryTree->root(), key) ?
					"Узел существует" : "Узел не существует");
				break;
			// Вывод дерева
			case 4:
				try {
					std::cout << BinaryTreeParser::toString(binaryTree) << std::endl;
				} catch(std::exception) {
					std::cout << "Нет корня" << std::endl;
				}
				break;
			// Выход
			case 5:
				delete binaryTree;
				return 0;
		}

		std::cout << std::endl;
	}
}