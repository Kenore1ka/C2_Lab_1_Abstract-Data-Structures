#pragma once

#include <string>

struct QueueNode {
    std::string data;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;

    void init();
    void enqueue(const std::string& value);
    void dequeue();
    void print();
    void destroy();
    void loadFromFile(const std::string& fileName);
    void saveToFile(const std::string& fileName);
};

void runQueue(int argc, char* argv[]);