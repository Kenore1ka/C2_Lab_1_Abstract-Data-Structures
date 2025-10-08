#include "binaryTree.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// Конструктор: инициализируем DynamicArray
BinaryTree::BinaryTree() {}

// Деструктор: освобождаем память, выделенную для DynamicArray
BinaryTree::~BinaryTree() {}

// Вставка: просто добавляем элемент в конец массива.
// Это автоматически сохраняет свойство полного бинарного дерева.
void BinaryTree::insert(const string& key) {
    nodes.add(key);
}

// Поиск: простой линейный поиск по массиву.
bool BinaryTree::search(const string& key) {
    for (int i = 0; i < nodes.length(); ++i) {
        if (nodes.get(i) == key) {
            return true;
        }
    }
    return false;
}

// Сохранение в файл: делегируем операцию DynamicArray.
void BinaryTree::saveToFile(const string& fileName) {
    nodes.saveToFile(fileName);
}

// Загрузка из файла: очищаем текущие данные и делегируем операцию DynamicArray.
void BinaryTree::loadFromFile(const string& fileName) {
    nodes.clear();  
    nodes.loadFromFile(fileName);
}

// Проверка на то, является ли дерево "full" (каждый узел имеет 0 или 2 потомка)
// Это верно, если количество элементов N равно 2^k - 1 для некоторого k.
// Проверить это можно, выяснив, является ли N+1 степенью двойки.
bool BinaryTree::isFull() const {
    int n = nodes.length();
    if (n == 0) {
        return true; // Пустое дерево считается полным
    }
    // Число является степенью двойки, если (n > 0) && ((n & (n - 1)) == 0)
    int n_plus_1 = n + 1;
    return (n_plus_1 > 0) && ((n_plus_1 & n) == 0);
}

// --- Реализация обходов дерева ---

// Приватная рекурсивная функция для центрированного обхода
void BinaryTree::inorder(int index) {
    if (index >= nodes.length()) return; // Если узла с таким индексом нет

    inorder(2 * index + 1);       // 1. Левое поддерево
    cout << nodes.get(index) << " "; // 2. Корень
    inorder(2 * index + 2);       // 3. Правое поддерево
}

// Публичный метод для запуска центрированного обхода
void BinaryTree::printInorder() {
    cout << "Inorder обход: ";
    if (nodes.length() > 0) {
        inorder(0); // Начинаем с корня (индекс 0)
    }
    cout << endl;
}

// Приватная рекурсивная функция для прямого обхода
void BinaryTree::preorder(int index) {
    if (index >= nodes.length()) return;

    cout << nodes.get(index) << " "; // 1. Корень
    preorder(2 * index + 1);      // 2. Левое поддерево
    preorder(2 * index + 2);      // 3. Правое поддерево
}

// Публичный метод для запуска прямого обхода
void BinaryTree::printPreorder() {
    cout << "Preorder обход: ";
    if (nodes.length() > 0) {
        preorder(0);
    }
    cout << endl;
}

// Приватная рекурсивная функция для обратного обхода
void BinaryTree::postorder(int index) {
    if (index >= nodes.length()) return;

    postorder(2 * index + 1);      // 1. Левое поддерево
    postorder(2 * index + 2);      // 2. Правое поддерево
    cout << nodes.get(index) << " "; // 3. Корень
}

// Публичный метод для запуска обратного обхода
void BinaryTree::printPostorder() {
    cout << "Postorder обход: ";
    if (nodes.length() > 0) {
        postorder(0);
    }
    cout << endl;
}

// Обход в ширину (BFS) для дерева в массиве - это просто печать массива.
void BinaryTree::printBFS() {
    cout << "BFS обход: ";
    nodes.print(); // Используем встроенный метод печати вашего DynamicArray
}

// Функция runBinaryTree остается той же самой и не требует изменений,
// так как публичный интерфейс класса BinaryTree сохранен.
// Её можно оставить в этом файле или вынести в main.cpp, как у вас было.
// Для полноты картины, привожу её здесь.
void runBinaryTree(int argc, char* argv[]) {
    BinaryTree tree;
    string fileName;
    string query;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            fileName = argv[++i];
        } else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[++i];
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
    } else if (command == "TGET") {
        if (tree.search(arg)) cout << arg << endl;
        else cout << "Ключ не найден" << endl;
    } else if (command == "TFULL") {
        cout << (tree.isFull() ? "true" : "false") << endl;
    } else if (command == "TSEARCH") {
        cout << (tree.search(arg) ? "true" : "false") << endl;
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