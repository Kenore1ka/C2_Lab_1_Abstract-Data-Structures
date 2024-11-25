#include "linkedList.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

// Структура узла списка
struct ListNode {
    string data;
    ListNode* next;
};

class LinkedList {
private:
    ListNode* head; // Указатель на голову списка
    ListNode* tail; // Указатель на хвост списка

public:
    // Инициализация списка
    void init() {
        head = nullptr;
        tail = nullptr;
    }

    // Добавление нового элемента в начало
    void addToHead(const string& value) {
        ListNode* newNode = new ListNode{value, head};
        head = newNode;
        if (tail == nullptr) {
            tail = head;
        }
    }

    // Добавление нового элемента в конец
    void addToTail(const string& value) {
        ListNode* newNode = new ListNode{value, nullptr};
        if (tail != nullptr) {
            tail->next = newNode;
        }
        tail = newNode;
        if (head == nullptr) {
            head = tail;
        }
    }

    // Удаление элемента с головы
    void removeFromHead() {
        if (head == nullptr) {
            return;
        }
        ListNode* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
    }

    // Удаление элемента с хвоста
    void removeFromTail() {
        if (tail == nullptr) {
            return;
        }
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        ListNode* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }
        delete tail;
        tail = temp;
        tail->next = nullptr;
    }

    // Удаление узла по значению
    void removeByValue(const string& value) {
        if (head == nullptr) {
            return;
        }
        if (head->data == value) {
            removeFromHead();
            return;
        }
        ListNode* temp = head;
        while (temp->next != nullptr) {
            if (temp->next->data == value) {
                ListNode* nodeToRemove = temp->next;
                temp->next = temp->next->next;
                if (nodeToRemove == tail) {
                    tail = temp;
                }
                delete nodeToRemove;
                return;
            }
            temp = temp->next;
        }
    }

    // Поиск элемента по значению
    bool search(const string& value) {
        ListNode* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Вывод всех элементов списка
    void print() {
        ListNode* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Очистка списка
    void destroy() {
        while (head != nullptr) {
            removeFromHead();
        }
    }

    // Загрузка элементов из файла
    void loadFromFile(const string& fileName) {
        ifstream file(fileName);
        string value;
        while (file >> value) {
            addToTail(value);
        }
        file.close();
    }

    // Сохранение элементов списка в файл
    void saveToFile(const string& fileName) {
        ofstream file(fileName);
        ListNode* temp = head;
        while (temp != nullptr) {
            file << temp->data << endl;
            temp = temp->next;
        }
        file.close();
    }
};

// Функция запуска работы со списком, обработка команд из аргументов командной строки
void runLinkedList(int argc, char* argv[]) {
    LinkedList list;
    list.init();

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

    list.loadFromFile(fileName);

    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    if (command == "LPUSH") {
        list.addToHead(query);  // Добавление элемента в начало списка
        list.saveToFile(fileName);
    } else if (command == "LAPPEND") {
        list.addToTail(query);  // Добавление элемента в конец списка
        list.saveToFile(fileName);
    } else if (command == "LREMOVEHEAD") {
        list.removeFromHead();  // Удаление элемента с головы списка
        list.saveToFile(fileName);
    } else if (command == "LREMOVETAIL") {
        list.removeFromTail();  // Удаление элемента с конца списка
        list.saveToFile(fileName);
    } else if (command == "LREMOVE") {
        list.removeByValue(query);  // Удаление элемента по значению
        list.saveToFile(fileName);
    } else if (command == "LSEARCH") {
        cout << (list.search(query) ? "true" : "false") << endl;    // Поиск элемента по значению
    } else if (command == "LPRINT") {
        list.print();
    }

    list.destroy();
}