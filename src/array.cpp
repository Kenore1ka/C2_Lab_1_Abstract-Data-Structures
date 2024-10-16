#include "array.h"

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

void DynamicArray::init(int initialCapacity) {
    data = new string[initialCapacity];
    size = 0;
    capacity = initialCapacity;
}

void DynamicArray::resize(int newCapacity) {
    string* newData = new string[newCapacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void DynamicArray::add(const string& value) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = value;
}

void DynamicArray::insert(int index, const string& value) {
    if (index < 0 || index > size) {
        return;
    }
    if (size == capacity) {
        resize(capacity * 2);
    }
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}

void DynamicArray::remove(int index) {
    if (index < 0 || index >= size) {
        return;
    }
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

string DynamicArray::get(int index) {
    if (index < 0 || index >= size) {
        return "";
    }
    return data[index];
}

void DynamicArray::set(int index, const string& value) {
    if (index < 0 || index >= size) {
        return;
    }
    data[index] = value;
}

int DynamicArray::length() { return size; }

void DynamicArray::print() {
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

void DynamicArray::destroy() { delete[] data; }

void DynamicArray::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    string value;
    while (file >> value) {
        add(value);
    }
    file.close();
}

void DynamicArray::saveToFile(const string& fileName) {
    ofstream file(fileName);
    for (int i = 0; i < size; i++) {
        file << data[i] << endl;
    }
    file.close();
}

void runDynamicArray(int argc, char* argv[]) {
    DynamicArray arr;
    arr.init(10);

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

    arr.loadFromFile(fileName);

    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    if (command == "MPUSH") {
        arr.add(query);
        arr.saveToFile(fileName);
    } else if (command == "MINSERT") {
        size_t pos = query.find(' ');
        int index = stoi(query.substr(0, pos));
        string value = query.substr(pos + 1);
        arr.insert(index, value);
        arr.saveToFile(fileName);
    } else if (command == "MDEL") {
        int index = stoi(query);
        arr.remove(index);
        arr.saveToFile(fileName);
    } else if (command == "MSET") {
        size_t pos = query.find(' ');
        int index = stoi(query.substr(0, pos));
        string value = query.substr(pos + 1);
        arr.set(index, value);
        arr.saveToFile(fileName);
    } else if (command == "MLEN") {
        cout << arr.length() << endl;
    } else if (command == "PRINT") {
        arr.print();
    } else if (command == "MGET") {
        int index = stoi(query);
        cout << arr.get(index) << endl;
    }

    arr.destroy();
}