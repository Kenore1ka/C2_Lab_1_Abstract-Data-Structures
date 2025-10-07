#pragma once

#include <string>
#include <fstream>

// Узел бинарного дерева (ключ хранится в виде строки)
struct Node {
    std::string key;
    Node* left;
    Node* right;

    explicit Node(const std::string& k)
        : key(k), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();

    // Основные операции
    void insert(const std::string& key);
    bool search(const std::string& key);
    void print(); // BFS-вывод

    // Работа с файлами
    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);

    // Проверка, является ли дерево полным (full)
    bool isFull() const;

    // Обходы дерева
    void printInorder();   // Левый — Корень — Правый
    void printPreorder();  // Корень — Левый — Правый
    void printPostorder(); // Левый — Правый — Корень
    void printBFS();       // Уровень за уровнем (BFS)

private:
    Node* root;

    // Вспомогательные функции
    void deleteTree(Node* node);
    bool isFullNode(Node* node) const;

    // Рекурсивные обходы
    void inorder(Node* node);
    void preorder(Node* node);
    void postorder(Node* node);
};

// Интерфейс командной строки
void runBinaryTree(int argc, char* argv[]);
