#pragma once

#include <string>

struct Node {
    std::string key;
    int height;
    Node* left;
    Node* right;

    Node(const std::string& key) : key(key), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
   public:
    AVLTree() : root(nullptr) {}

    void insert(const std::string& key);
    void remove(const std::string& key);
    bool search(const std::string& key);
    void print();
    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);

   private:
    Node* root;

    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rebalance(Node* node);
    Node* insertNode(Node* node, const std::string& key);
    Node* removeNode(Node* node, const std::string& key);
    void printNode(Node* node);
    void saveNode(Node* node, std::ofstream& file);
    void loadNode(std::ifstream& file);
};

void runAVLTree(int argc, char* argv[]);