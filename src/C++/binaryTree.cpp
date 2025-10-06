#include "binaryTree.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

/*
 Конструктор: инициализирует пустое дерево (root = nullptr).
*/
BinaryTree::BinaryTree() : root(nullptr) {}

/*
 Деструктор: освобождает память, удаляя все узлы.
*/
BinaryTree::~BinaryTree() {
    deleteTree(root);
}

/*
 deleteTree: рекурсивно удаляет поддерево, начиная с node.
*/
void BinaryTree::deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

/*
 insert: публичный метод для вставки ключа в BST.
 Дубликаты не вставляются.
*/
void BinaryTree::insert(const string& key) {
    root = insertNode(root, key);
}

/*
 insertNode: рекурсивная вставка в BST.
 Если ключ уже существует, возвращает тот же узел (без вставки).
 Возвращает новый корень поддерева.
*/
Node* BinaryTree::insertNode(Node* node, const string& key) {
    if (node == nullptr) {
        return new Node(key);
    }
    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    } else {
        // дубликат — ничего не делаем
    }
    return node;
}

/*
 remove: публичный метод удаления ключа из дерева.
*/
void BinaryTree::remove(const string& key) {
    root = removeNode(root, key);
}

/*
 findMin: находит узел с минимальным ключом в поддереве.
*/
Node* BinaryTree::findMin(Node* node) {
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}

/*
 removeNode: рекурсивное удаление узла с данным ключом.
 Возвращает новый корень поддерева.
*/
Node* BinaryTree::removeNode(Node* node, const string& key) {
    if (!node) return node;

    if (key < node->key) {
        node->left = removeNode(node->left, key);
    } else if (key > node->key) {
        node->right = removeNode(node->right, key);
    } else {
        // найден узел для удаления
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        } else {
            // оба поддерева существуют: заменяем на минимальный в правом
            Node* succ = findMin(node->right);
            node->key = succ->key;
            node->right = removeNode(node->right, succ->key);
        }
    }
    return node;
}

/*
 search: поиск ключа в дереве (итеративно).
 Возвращает true если найден, иначе false.
*/
bool BinaryTree::search(const string& key) {
    Node* cur = root;
    while (cur) {
        if (key < cur->key) cur = cur->left;
        else if (key > cur->key) cur = cur->right;
        else return true;
    }
    return false;
}

/*
 print: выводит дерево в одну строку — BFS (level-order),
 ключи разделяются пробелом, в конце перевод строки.
*/
void BinaryTree::print() {
    if (!root) {
        cout << endl;
        return;
    }
    queue<Node*> q;
    q.push(root);
    bool first = true;
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (!first) cout << " ";
        cout << cur->key;
        first = false;
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    cout << endl;
}

/*
 saveNode: сохраняет узлы в файл в порядке inorder (по возрастанию),
 каждое ключ — на отдельной строке.
*/
void BinaryTree::saveNode(Node* node, ofstream& file) {
    if (!node) return;
    saveNode(node->left, file);
    file << node->key << endl;
    saveNode(node->right, file);
}

/*
 saveToFile: сохраняет дерево в файл (inorder).
*/
void BinaryTree::saveToFile(const string& fileName) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл для записи." << endl;
        return;
    }
    saveNode(root, file);
    file.close();
}

/*
 loadNode: читает ключи из потока и вставляет их в дерево (по одной строке/токену).
*/
void BinaryTree::loadNode(ifstream& file) {
    string key;
    while (file >> key) {
        insert(key);
    }
}

/*
 loadFromFile: загружает дерево из файла (каждая запись — ключ).
*/

void BinaryTree::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл для чтения." << endl;
        return;
    }
    loadNode(file);
    file.close();
}

/*
 isFullNode: рекурсивная проверка свойства "full" для поддерева.
 Возвращает true если каждый узел поддерева имеет 0 или 2 детей.
*/
bool BinaryTree::isFullNode(Node* node) const {
    if (!node) return true;
    bool l = (node->left != nullptr);
    bool r = (node->right != nullptr);
    if (l && r) {
        return isFullNode(node->left) && isFullNode(node->right);
    } else if (!l && !r) {
        return true;
    } else {
        return false;
    }
}

/*
 isFull: публичная оболочка для проверки, является ли дерево full.
*/
bool BinaryTree::isFull() const {
    return isFullNode(root);
}

/*
 runBinaryTree: функция интерфейса командной строки (как в оригинальном проекте).
 Поддерживаем команды:
  - TINSERT <key>   : вставить ключ и сохранить в файл
  - TDEL <key> / TREMOVE <key> : удалить ключ и сохранить в файл
  - TGET <key>      : если ключ есть — вывести его, иначе "Key not found"
  - TFULL           : вывести "true" или "false" в зависимости от isFull()
  - TPRINT          : вывести дерево (BFS)
*/
void runBinaryTree(int argc, char* argv[]) {
    BinaryTree tree;

    string fileName;
    string query;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            fileName = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[i + 1];
            i++;
        }
    }

    if (!fileName.empty()) tree.loadFromFile(fileName);

    string command;
    string arg;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        arg = query.substr(pos + 1);
    } else {
        command = query;
    }

    if (command == "TINSERT") {
        tree.insert(arg);
        if (!fileName.empty()) tree.saveToFile(fileName);
    } else if (command == "TDEL" || command == "TREMOVE") {
        tree.remove(arg);
        if (!fileName.empty()) tree.saveToFile(fileName);
    } else if (command == "TGET") {
        if (tree.search(arg)) cout << arg << endl;
        else cout << "Key not found" << endl;
    } else if (command == "TFULL") {
        cout << (tree.isFull() ? "true" : "false") << endl;
    } else if (command == "TPRINT") {
        tree.print();
    } else if (command == "TSEARCH") {
        // backward compatibility: TSEARCH уже раньше использовалась
        cout << (tree.search(arg) ? "true" : "false") << endl;
    }
}
