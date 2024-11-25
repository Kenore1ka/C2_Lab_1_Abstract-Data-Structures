#include "stack.h"

#include <cstring> // Для strcmp
#include <fstream> // Для работы с файлами
#include <iostream>

using namespace std;

// Инициализация стека. Устанавливает указатель вершины стека в nullptr.
void Stack::init() { 
    top = nullptr; 
}

// Добавление элемента в стек.
void Stack::push(const string& value) {
    // Создаем новый узел стека.
    StackNode* newNode = new StackNode{value, nullptr};
    // Если стек пуст, новый узел становится вершиной стека.
    if (top == nullptr) {
        top = newNode;
    } else {
        // Иначе, находим последний элемент стека.
        StackNode* temp = top;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        // Новый узел становится следующим после последнего элемента.
        temp->next = newNode;
    }
}

// Удаление элемента из стека.
void Stack::pop() {
    // Если стек пуст, ничего не делаем.
    if (top == nullptr) {
        return;
    }
    // Если в стеке только один элемент, удаляем его.
    if (top->next == nullptr) {
        delete top;
        top = nullptr;
    } else {
        // Иначе, находим предпоследний элемент стека.
        StackNode* temp = top;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        // Удаляем последний элемент.
        delete temp->next;
        temp->next = nullptr;
    }
}

// Вывод содержимого стека в консоль.
void Stack::print() {
    StackNode* temp = top;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Освобождение памяти, занимаемой стеком.
void Stack::destroy() {
    while (top != nullptr) {
        pop(); // Последовательно удаляем элементы из стека.
    }
}

// Загрузка стека из файла.
void Stack::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    string value;
    // Читаем строки из файла и добавляем их в стек.
    while (file >> value) {
        push(value);
    }
    file.close();
}

// Сохранение стека в файл.
void Stack::saveToFile(const string& fileName) {
    ofstream file(fileName);
    StackNode* temp = top;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}


// Функция для управления стеком через командную строку.
void runStack(int argc, char* argv[]) {
    Stack stack;
    stack.init();

    string fileName;
    string query;

    // Разбор аргументов командной строки.
    for (int i = 1; i < argc; i++) {
        // Поиск аргумента --file и имени файла.
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            fileName = argv[i + 1];
            i++; // Пропускаем следующий аргумент (имя файла).
        // Поиск аргумента --query и запроса.
        } else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[i + 1];
            i++; // Пропускаем следующий аргумент (запрос).
        }
    }

    stack.loadFromFile(fileName);

    string command;
    // Разделение запроса на команду и значение.
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    // Выполнение команды.
    if (command == "SPUSH") {
        stack.push(query);
        stack.saveToFile(fileName);
    } else if (command == "SPOP") {
        stack.pop();
        stack.saveToFile(fileName);
    } else if (command == "SPRINT") {
        stack.print();
    }

    stack.destroy();
}