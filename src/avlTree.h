#pragma once

#include <string>

// Определение структуры узла для AVL дерева
struct Node {
    std::string key; // Ключ, хранимый в узле
    int height;      // Высота узла для поддержки балансировки
    Node* left;      // Указатель на левое поддерево
    Node* right;     // Указатель на правое поддерево

    // Конструктор, инициализирующий узел с заданным ключом
    Node(const std::string& key) : key(key), height(1), left(nullptr), right(nullptr) {}
};

// Определение класса AVL дерева
class AVLTree {
   public:
    AVLTree() : root(nullptr) {} // Конструктор AVL дерева, инициализирует пустое дерево

    void insert(const std::string& key);       // Вставляет ключ в дерево
    void remove(const std::string& key);       // Удаляет ключ из дерева
    bool search(const std::string& key);       // Проверяет наличие ключа в дереве
    void print();                              // Выводит все ключи дерева
    void saveToFile(const std::string& fileName); // Сохраняет дерево в файл
    void loadFromFile(const std::string& fileName); // Загружает дерево из файла

   private:
    Node* root; // Корень дерева

    // Вспомогательные функции для внутренней работы AVL дерева
    int getHeight(Node* node);                   // Возвращает высоту узла
    int getBalanceFactor(Node* node);            // Вычисляет баланс-фактор узла
    Node* rotateLeft(Node* node);                // Выполняет левый поворот
    Node* rotateRight(Node* node);               // Выполняет правый поворот
    Node* rebalance(Node* node);                 // Выполняет балансировку дерева
    Node* insertNode(Node* node, const std::string& key); // Вспомогательная функция для вставки
    Node* removeNode(Node* node, const std::string& key); // Вспомогательная функция для удаления
    void printNode(Node* node);                  // Вспомогательная функция для печати
    void saveNode(Node* node, std::ofstream& file); // Вспомогательная функция для сохранения узлов
    void loadNode(std::ifstream& file);          // Вспомогательная функция для загрузки узлов
};

// Функция для запуска AVL дерева с параметрами командной строки
void runAVLTree(int argc, char* argv[]);
