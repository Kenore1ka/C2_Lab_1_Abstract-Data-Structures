#include "linkedList.h"
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

// Инициализация списка.
void LinkedList::init() {
    head = nullptr;
    tail = nullptr;
}

// Добавление нового элемента в начало.
void LinkedList::addToHead(const string& value) {
    ListNode* newNode = new ListNode{value, head, nullptr};
    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;
    if (tail == nullptr) {
        tail = head;
    }
}

// Добавление нового элемента в конец.
void LinkedList::addToTail(const string& value) {
    ListNode* newNode = new ListNode{value, nullptr, tail};
    if (tail != nullptr) {
        tail->next = newNode;
    }
    tail = newNode;
    if (head == nullptr) {
        head = tail;
    }
}

// Удаление элемента с головы.
void LinkedList::removeFromHead() {
    if (head == nullptr) {
        return;
    }
    ListNode* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
}

// Удаление элемента с хвоста.
void LinkedList::removeFromTail() {
    if (tail == nullptr) {
        return;
    }
    ListNode* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
}

// Удаление узла по значению.
void LinkedList::removeByValue(const string& value) {
    ListNode* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            } else {
                head = temp->next;
            }
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            } else {
                tail = temp->prev;
            }
            delete temp;
            return;
        }
        temp = temp->next;
    }
}

// Поиск элемента по значению.
bool LinkedList::search(const string& value) {
    ListNode* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Вывод всех элементов списка.
void LinkedList::print() {
    ListNode* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Очистка списка.
void LinkedList::destroy() {
    while (head != nullptr) {
        removeFromHead();
    }
}

// Загрузка элементов из файла.
void LinkedList::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    string value;
    while (file >> value) {
        addToTail(value);
    }
    file.close();
}

// Сохранение элементов списка в файл.
void LinkedList::saveToFile(const string& fileName) {
    ofstream file(fileName);
    ListNode* temp = head;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

// Функция запуска работы со списком, обработка команд из аргументов командной строки.
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
