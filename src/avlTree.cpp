#include "avlTree.h"

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

// Возвращает высоту указанного узла
int AVLTree::getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Вычисляет фактор баланса указанного узла (разницу высот левого и правого поддеревьев)
int AVLTree::getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Выполняет левый поворот относительно указанного узла
Node* AVLTree::rotateLeft(Node* node) {
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;

    // Обновляет высоты узлов после поворота
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;

    return temp; // Возвращает новый корень поддерева
}

// Выполняет правый поворот относительно указанного узла
Node* AVLTree::rotateRight(Node* node) {
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;

    // Обновляет высоты узлов после поворота
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;

    return temp; // Возвращает новый корень поддерева
}

// Восстанавливает баланс дерева, если он нарушен
Node* AVLTree::rebalance(Node* node) {
    int balanceFactor = getBalanceFactor(node);

    // Левое поддерево слишком высокое
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) {
            // Левый-правый случай
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node); // Левый-левый случай
    }

    // Правое поддерево слишком высокое
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) {
            // Правый-левый случай
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node); // Правый-правый случай
    }

    return node; // Возвращает узел без изменений, если баланс в пределах нормы
}

// Вставка ключа в дерево с последующей балансировкой
Node* AVLTree::insertNode(Node* node, const string& key) {
    if (node == nullptr) {
        return new Node(key); // Создает новый узел, если достигнут конец дерева
    }

    if (key < node->key) {
        node->left = insertNode(node->left, key); // Вставка в левое поддерево
    } else if (key > node->key) {
        node->right = insertNode(node->right, key); // Вставка в правое поддерево
    }

    // Обновляет высоту узла
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    return rebalance(node); // Восстанавливает баланс после вставки
}

// Вставляет ключ в дерево
void AVLTree::insert(const string& key) { root = insertNode(root, key); }

// Удаляет узел с заданным ключом и выполняет балансировку
Node* AVLTree::removeNode(Node* node, const string& key) {
    if (node == nullptr) {
        return node; // Узел не найден
    }

    if (key < node->key) {
        node->left = removeNode(node->left, key); // Поиск и удаление в левом поддереве
    } else if (key > node->key) {
        node->right = removeNode(node->right, key); // Поиск и удаление в правом поддереве
    } else {
        // Узел найден. Удаление узла и сохранение связности дерева
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Поиск узла с минимальным значением в правом поддереве
        Node* temp = node->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        // Копирует ключ минимального узла и удаляет его
        node->key = temp->key;
        node->right = removeNode(node->right, temp->key);
    }

    if (node == nullptr) {
        return node; // Если дерево пустое, возвращает nullptr
    }

    // Обновляет высоту узла и балансирует дерево
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    return rebalance(node);
}

// Удаляет ключ из дерева
void AVLTree::remove(const string& key) { root = removeNode(root, key); }

// Выполняет поиск узла с заданным ключом
bool AVLTree::search(const string& key) {
    Node* node = root;
    while (node != nullptr) {
        if (key < node->key) {
            node = node->left; // Переход в левое поддерево
        } else if (key > node->key) {
            node = node->right; // Переход в правое поддерево
        } else {
            return true; // Ключ найден
        }
    }
    return false; // Ключ не найден
}

// Рекурсивная функция для вывода ключей дерева в порядке возрастания
void AVLTree::printNode(Node* node) {
    if (node != nullptr) {
        printNode(node->left);
        cout << node->key << " ";
        printNode(node->right);
    }
}

// Выводит все ключи дерева
void AVLTree::print() {
    printNode(root);
    cout << endl;
}

// Рекурсивно сохраняет ключи дерева в файл
void AVLTree::saveNode(Node* node, ofstream& file) {
    if (node != nullptr) {
        saveNode(node->left, file);
        file << node->key << endl;
        saveNode(node->right, file);
    }
}

// Сохраняет дерево в файл
void AVLTree::saveToFile(const string& fileName) {
    ofstream file(fileName);
    if (file.is_open()) {
        saveNode(root, file);
        file.close();
    } else {
        cout << "Не удалось открыть файл для записи." << endl;
    }
}

// Загружает дерево из файла
void AVLTree::loadNode(ifstream& file) {
    string key;
    while (file >> key) {
        insert(key); // Вставка ключа в дерево
    }
}

// Загружает дерево из файла и добавляет ключи
void AVLTree::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        loadNode(file);
        file.close();
    } else {
        cout << "Не удалось открыть файл для чтения." << endl;
    }
}

// Функция, управляющая деревом AVL на основе командной строки
void runAVLTree(int argc, char* argv[]) {
    AVLTree tree;

    string fileName;
    string query;

    // Обработка аргументов командной строки
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            fileName = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[i + 1];
            i++;
        }
    }

    tree.loadFromFile(fileName); // Загрузка дерева из файла

    // Разбор команды
    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    // Выполнение команды
    if (command == "TINSERT") {
        tree.insert(query);
        tree.saveToFile(fileName);
    } else if (command == "TREMOVE") {
        tree.remove(query);
        tree.saveToFile(fileName);
    } else if (command == "TSEARCH") {
        cout << (tree.search(query) ? "true" : "false") << endl;
    } else if (command == "PRINT") {
        tree.print();
    }
}
