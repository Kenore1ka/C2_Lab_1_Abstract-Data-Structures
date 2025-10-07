#include "binaryTree.h"
#include "array.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    deleteTree(root);
}

void BinaryTree::deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Вставка
void BinaryTree::insert(const string& key) {
    Node* newNode = new Node(key);
    if (!root) {
        root = newNode;
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (!temp->left) {
            temp->left = newNode;
            return;
        } else {
            q.push(temp->left);
        }

        if (!temp->right) {
            temp->right = newNode;
            return;
        } else {
            q.push(temp->right);
        }
    }
}

// Поиск
bool BinaryTree::search(const string& key) {
    if (!root) return false;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp->key == key) return true;

        if (temp->left)  q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }

    return false;
}

// Сохранение
void BinaryTree::saveToFile(const string& fileName) {
    DynamicArray arr;
    arr.init(10);

    if (root) {
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            arr.add(cur->key);
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }

    arr.saveToFile(fileName);
    arr.destroy();
}

// Загрузка
void BinaryTree::loadFromFile(const string& fileName) {
    DynamicArray arr;
    arr.init(10);
    arr.loadFromFile(fileName);

    int n = arr.length();

    deleteTree(root);
    root = nullptr;

    if (n == 0) {
        arr.destroy();
        return;
    }

    Node** nodes = new Node*[n];
    for (int i = 0; i < n; ++i) {
        nodes[i] = new Node(arr.get(i));
        nodes[i]->left = nullptr;
        nodes[i]->right = nullptr;
    }

    for (int i = 0; i < n; ++i) {
        int li = 2 * i + 1;
        int ri = 2 * i + 2;
        if (li < n) nodes[i]->left  = nodes[li];
        if (ri < n) nodes[i]->right = nodes[ri];
    }

    root = nodes[0];
    delete[] nodes;
    arr.destroy();
}

// Проверка full
bool BinaryTree::isFullNode(Node* node) const {
    if (!node) return true;

    bool hasLeft  = (node->left  != nullptr);
    bool hasRight = (node->right != nullptr);

    if (hasLeft && hasRight)
        return isFullNode(node->left) && isFullNode(node->right);

    return !hasLeft && !hasRight;
}

bool BinaryTree::isFull() const {
    return isFullNode(root);
}

// Обходы 
void BinaryTree::inorder(Node* node) {      // Центрированный
    if (!node) return;
    inorder(node->left);
    cout << node->key << " ";
    inorder(node->right);
}

void BinaryTree::preorder(Node* node) {     // В прямом порядке
    if (!node) return;
    cout << node->key << " ";
    preorder(node->left);
    preorder(node->right);
}

void BinaryTree::postorder(Node* node) {    // В обратном порядке
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->key << " ";
}

// Вывод
void BinaryTree::printInorder() {
    cout << "Inorder обход: ";
    inorder(root);
    cout << endl;
}

void BinaryTree::printPreorder() {
    cout << "Preorder обход: ";
    preorder(root);
    cout << endl;
}

void BinaryTree::printPostorder() {
    cout << "Postorder обход: ";
    postorder(root);
    cout << endl;
}

void BinaryTree::printBFS() {
    cout << "BFS обход: ";
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

        if (cur->left)  q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    cout << endl;
}

void runBinaryTree(int argc, char* argv[]) {
    BinaryTree tree;
    string fileName;
    string query;

    for (int i = 1; i < argc; ++i) { // Обработка аргументов командной строки
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            fileName = argv[++i]; // Получение имени файла из аргумента
        } else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[++i]; // Получение запроса из аргумента
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
        tree.insert(arg); // Добавление ключа
        if (!fileName.empty()) tree.saveToFile(fileName);
    } else if (command == "TGET") {
        if (tree.search(arg)) cout << arg << endl; // Поиск ключа
        else cout << "Ключ не найден" << endl;
    } else if (command == "TFULL") {
        cout << (tree.isFull() ? "true" : "false") << endl; // Проверка на полноту
    } else if (command == "TSEARCH") {
        cout << (tree.search(arg) ? "true" : "false") << endl; // Проверка на наличие ключа
    } else if (command == "TINORDER") {
        tree.printInorder();
    } else if (command == "TPREORDER") {
        tree.printPreorder();
    } else if (command == "TPOSTORDER") {
        tree.printPostorder();
    } else if (command == "TBFS") {
        tree.printBFS();
    }
}
