#include "dlinkedList.h"
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

// Инициализация списка.
void DlinkedList::init() {
    head = nullptr;
    tail = nullptr;
}

// Добавление нового элемента в начало.
void DlinkedList::addToHead(const string& value) {
    DlistNode* newNode = new DlistNode{value, head, nullptr};
    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;
    if (tail == nullptr) {
        tail = head;
    }
}

// Добавление нового элемента в конец.
void DlinkedList::addToTail(const string& value) {
    DlistNode* newNode = new DlistNode{value, nullptr, tail};
    if (tail != nullptr) {
        tail->next = newNode;
    }
    tail = newNode;
    if (head == nullptr) {
        head = tail;
    }
}

// Удаление элемента с головы.
void DlinkedList::removeFromHead() {
    if (head == nullptr) {
        return;
    }
    DlistNode* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
}

// Удаление элемента с хвоста.
void DlinkedList::removeFromTail() {
    if (tail == nullptr) {
        return;
    }
    DlistNode* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
}

// Удаление узла по значению.
void DlinkedList::removeByValue(const string& value) {
    DlistNode* temp = head;
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
bool DlinkedList::search(const string& value) {
    DlistNode* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Вывод всех элементов списка.
void DlinkedList::print() {
    DlistNode* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Очистка списка.
void DlinkedList::destroy() {
    while (head != nullptr) {
        removeFromHead();
    }
}

// Загрузка элементов из файла.
void DlinkedList::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    string value;
    while (file >> value) {
        addToTail(value);
    }
    file.close();
}

// Сохранение элементов списка в файл.
void DlinkedList::saveToFile(const string& fileName) {
    ofstream file(fileName);
    DlistNode* temp = head;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

// Функция запуска работы со списком, обработка команд из аргументов командной строки.
void runLLinkedList(int argc, char* argv[]) {
    DlinkedList list;
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

    if (command == "DPUSH") {
        list.addToHead(query);  // Добавление элемента в начало списка
        list.saveToFile(fileName);
    } else if (command == "DAPPEND") {
        list.addToTail(query);  // Добавление элемента в конец списка
        list.saveToFile(fileName);
    } else if (command == "DREMOVEHEAD") {
        list.removeFromHead();  // Удаление элемента с головы списка
        list.saveToFile(fileName);
    } else if (command == "DREMOVETAIL") {
        list.removeFromTail();  // Удаление элемента с конца списка
        list.saveToFile(fileName);
    } else if (command == "DREMOVE") {
        list.removeByValue(query);  // Удаление элемента по значению
        list.saveToFile(fileName);
    } else if (command == "DSEARCH") {
        cout << (list.search(query) ? "true" : "false") << endl;    // Поиск элемента по значению
    } else if (command == "DPRINT") {
        list.print();
    }

    list.destroy();
}
