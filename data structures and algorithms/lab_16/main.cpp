#include <iostream>
#include <stack>

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

	// Не рекурсивный прямой обход
	void traversePreOrderNonRecursive(BinaryTreeNode* node) {
		if (node == nullptr) return;

		std::stack<BinaryTreeNode*> stack;
		stack.push(node);

		while (!stack.empty()) {
			BinaryTreeNode* currentNode = stack.top();
			stack.pop();

			std::cout << currentNode->data() << ' ';

			if (currentNode->rightNode() != nullptr) stack.push(currentNode->rightNode());
			if (currentNode->leftNode() != nullptr) stack.push(currentNode->leftNode());
		}
	}
private:
	BinaryTreeNode* m_root; // Корень дерева
};

int main() {
	setlocale(LC_ALL, "Russian");

	BinaryTree* binaryTree = new BinaryTree;
	binaryTree->insert(10);
	binaryTree->insert(5);
	binaryTree->insert(1);
	binaryTree->insert(15);
	binaryTree->insert(20);
	binaryTree->insert(15);
	binaryTree->insert(13);
	binaryTree->insert(25);
	binaryTree->insert(30);

	std::cout << "Не рекурсивный прямой обход: ";
	binaryTree->traversePreOrderNonRecursive(binaryTree->root());

	delete binaryTree;
}