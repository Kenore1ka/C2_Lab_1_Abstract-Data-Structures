#include "queue.h"

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

void Queue::init() {
    front = nullptr;
    rear = nullptr;
}

void Queue::enqueue(const string& value) {
    QueueNode* newNode = new QueueNode{value, nullptr};
    if (rear != nullptr) {
        rear->next = newNode;
    }
    rear = newNode;
    if (front == nullptr) {
        front = rear;
    }
}

void Queue::dequeue() {
    if (front == nullptr) {
        return;
    }
    QueueNode* temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete temp;
}

void Queue::print() {
    QueueNode* temp = front;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void Queue::destroy() {
    while (front != nullptr) {
        dequeue();
    }
}

void Queue::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    string value;
    while (file >> value) {
        enqueue(value);
    }
    file.close();
}

void Queue::saveToFile(const string& fileName) {
    ofstream file(fileName);
    QueueNode* temp = front;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

void runQueue(int argc, char* argv[]) {
    Queue queue;
    queue.init();

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

    queue.loadFromFile(fileName);

    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    if (command == "QPUSH") {
        queue.enqueue(query);
        queue.saveToFile(fileName);
    } else if (command == "QPOP") {
        queue.dequeue();
        queue.saveToFile(fileName);
    } else if (command == "PRINT") {
        queue.print();
    }

    queue.destroy();
}