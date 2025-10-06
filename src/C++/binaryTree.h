#pragma once

#include <string>
#include <fstream>

// Узел дерева хранит ключ в виде строки (совместимо с оригинальным репозиторием)
struct Node {
    std::string key;
    Node* left;
    Node* right;
    Node(const std::string& k) : key(k), left(nullptr), right(nullptr) {}
};

// Класс называется AVLTree, чтобы main.cpp не нужно было менять,
// но это простое BST-дерево (вставка без дубликатов, удаление стандартное).
class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();

    void insert(const std::string& key);
    void remove(const std::string& key);
    bool search(const std::string& key);
    void print();                              // Печать дерева (BFS — ширинный обход)
    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);

    // Проверка, является ли дерево "full": каждый узел имеет 0 или 2 ребёнка
    bool isFull() const;

private:
    Node* root;

    // Вспомогательные функции
    Node* insertNode(Node* node, const std::string& key);
    Node* removeNode(Node* node, const std::string& key);
    Node* findMin(Node* node);
    void saveNode(Node* node, std::ofstream& file);
    void loadNode(std::ifstream& file);
    void deleteTree(Node* node);
    bool isFullNode(Node* node) const;
};
 
// Сохранена сигнатура запуска, чтобы main.cpp оставался без изменений
void runBinaryTree(int argc, char* argv[]);
