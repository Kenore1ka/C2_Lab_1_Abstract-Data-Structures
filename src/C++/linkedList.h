#pragma once

#include <string>

// Узел односвязного списка.
struct ListNode {
    std::string data;     // Данные, хранящиеся в узле.
    ListNode* next;       // Указатель на следующий узел.
};

// Односвязный список с указателями на начало и конец.
class LinkedList {
public:
    ListNode* head;       // Указатель на первый элемент списка.
    ListNode* tail;       // Указатель на последний элемент списка.

    // Методы для работы с односвязным списком.
    void init();                          // Инициализирует пустой список.
    void addToHead(const std::string& value);  // Добавить элемент в начало.
    void addToTail(const std::string& value);  // Добавить элемент в конец.
    void removeFromHead();                // Удалить элемент с головы.
    void removeFromTail();                // Удалить элемент с хвоста.
    void removeByValue(const std::string& value); // Удалить по значению.
    bool search(const std::string& value); // Поиск по значению.
    void print();                         // Вывод элементов списка.
    void destroy();                       // Очистка списка.
    void loadFromFile(const std::string& fileName); // Загрузка из файла.
    void saveToFile(const std::string& fileName);   // Сохранение в файл.
};

// Запуск списка с использованием командной строки.
void runLinkedList(int argc, char* argv[]);