#include "stack.h"

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

void Stack::init() { top = nullptr; }

void Stack::push(const string& value) {
    StackNode* newNode = new StackNode{value, top};
    top = newNode;
}

void Stack::pop() {
    if (top == nullptr) {
        return;
    }
    StackNode* temp = top;
    top = top->next;
    delete temp;
}

void Stack::print() {
    StackNode* temp = top;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void Stack::destroy() {
    while (top != nullptr) {
        pop();
    }
}

void Stack::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    string value;
    while (file >> value) {
        push(value);
    }
    file.close();
}

void Stack::saveToFile(const string& fileName) {
    ofstream file(fileName);
    StackNode* temp = top;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

void runStack(int argc, char* argv[]) {
    Stack stack;
    stack.init();

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

    stack.loadFromFile(fileName);

    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    if (command == "SPUSH") {
        stack.push(query);
        stack.saveToFile(fileName);
    } else if (command == "SPOP") {
        stack.pop();
        stack.saveToFile(fileName);
    } else if (command == "PRINT") {
        stack.print();
    }

    stack.destroy();
}