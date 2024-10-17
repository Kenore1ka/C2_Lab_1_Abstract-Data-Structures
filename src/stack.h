#pragma once

#include <string>

struct StackNode {
    std::string data;
    StackNode* next;
};

struct Stack {
    StackNode* top;

    void init();
    void push(const std::string& value);
    void pop();
    void print();
    void destroy();
    void loadFromFile(const std::string& fileName);
    void saveToFile(const std::string& fileName);
};

void runStack(int argc, char* argv[]);