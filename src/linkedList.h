#pragma once

#include <string>

// Узел списка, содержащий данные и указатель на следующий узел.
struct ListNode {
    std::string data;     // Данные, хранящиеся в узле.
    ListNode* next;       // Указатель на следующий узел.
};

// Связный список, содержащий указатели на первый и последний узлы, а также методы для управления списком.
struct LinkedList {
    ListNode* head;       // Указатель на первый элемент списка.
    ListNode* tail;       // Указатель на последний элемент списка.

    // Функции инициализации и управления списком
    void init();                          // Инициализирует пустой список.
    void addToHead(const std::string& value);  // Добавляет узел со значением `value` в начало списка.
    void addToTail(const std::string& value);  // Добавляет узел со значением `value` в конец списка.
    void removeFromHead();                // Удаляет узел с головы списка.
    void removeFromTail();                // Удаляет узел с конца списка.
    void removeByValue(const std::string& value); // Удаляет первый узел с указанным значением.
    bool search(const std::string& value); // Ищет узел по значению, возвращает true, если найдено.
    void print();                         // Печатает все узлы списка.
    void destroy();                       // Удаляет все узлы списка и освобождает память.
    void loadFromFile(const std::string& fileName); // Загружает данные в список из файла.
    void saveToFile(const std::string& fileName);   // Сохраняет данные списка в файл.
};

// Функция для запуска списка с аргументами командной строки.
void runLinkedList(int argc, char* argv[]);
