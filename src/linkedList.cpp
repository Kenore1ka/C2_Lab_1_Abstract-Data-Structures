#include "linkedList.h"

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

void LinkedList::init() {
    head = nullptr;
    tail = nullptr;
}

void LinkedList::addToHead(const string& value) {
    ListNode* newNode = new ListNode{value, head};
    head = newNode;
    if (tail == nullptr) {
        tail = head;
    }
}

void LinkedList::addToTail(const string& value) {
    ListNode* newNode = new ListNode{value, nullptr};
    if (tail != nullptr) {
        tail->next = newNode;
    }
    tail = newNode;
    if (head == nullptr) {
        head = tail;
    }
}

void LinkedList::removeFromHead() {
    if (head == nullptr) {
        return;
    }
    ListNode* temp = head;
    head = head->next;
    delete temp;
    if (head == nullptr) {
        tail = nullptr;
    }
}

void LinkedList::removeFromTail() {
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

void LinkedList::removeByValue(const string& value) {
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

void LinkedList::print() {
    ListNode* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void LinkedList::destroy() {
    while (head != nullptr) {
        removeFromHead();
    }
}

void LinkedList::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    string value;
    while (file >> value) {
        addToTail(value);
    }
    file.close();
}

void LinkedList::saveToFile(const string& fileName) {
    ofstream file(fileName);
    ListNode* temp = head;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }
    file.close();
}

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
        list.addToHead(query);
        list.saveToFile(fileName);
    } else if (command == "LAPPEND") {
        list.addToTail(query);
        list.saveToFile(fileName);
    } else if (command == "LREMOVEHEAD") {
        list.removeFromHead();
        list.saveToFile(fileName);
    } else if (command == "LREMOVETAIL") {
        list.removeFromTail();
        list.saveToFile(fileName);
    } else if (command == "LREMOVE") {
        list.removeByValue(query);
        list.saveToFile(fileName);
    } else if (command == "LSEARCH") {
        cout << (list.search(query) ? "true" : "false") << endl;
    } else if (command == "PRINT") {
        list.print();
    }

    list.destroy();
}