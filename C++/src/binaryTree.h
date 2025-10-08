#pragma once

#include "array.h" // Подключаем ваш DynamicArray
#include <string>

class BinaryTree {
public:
    // Конструктор и деструктор
    BinaryTree();
    ~BinaryTree();

    // Основные операции
    void insert(const std::string& key);
    bool search(const std::string& key);

    // Работа с файлами
    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);

    // Проверка, является ли дерево полным (full)
    // "Полное" (full) дерево - это дерево, в котором каждый узел имеет 0 или 2 потомка.
    // Для дерева, представленного массивом, это означает, что количество узлов должно быть 2^h - 1.
    bool isFull() const;

    // Обходы дерева
    void printInorder();   // Левый — Корень — Правый
    void printPreorder();  // Корень — Левый — Правый
    void printPostorder(); // Левый — Правый — Корень
    void printBFS();       // Уровень за уровнем (обход в ширину)

private:
    DynamicArray nodes; // Хранилище для узлов дерева

    // Вспомогательные рекурсивные функции для обходов, работающие с индексами
    void inorder(int index);
    void preorder(int index);
    void postorder(int index);
};

// Интерфейс командной строки
void runBinaryTree(int argc, char* argv[]);
