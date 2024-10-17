#include "avlTree.h"

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

int AVLTree::getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::rotateLeft(Node* node) {
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;

    return temp;
}

Node* AVLTree::rotateRight(Node* node) {
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;

    return temp;
}

Node* AVLTree::rebalance(Node* node) {
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

Node* AVLTree::insertNode(Node* node, const string& key) {
    if (node == nullptr) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    }

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    return rebalance(node);
}

void AVLTree::insert(const string& key) { root = insertNode(root, key); }

Node* AVLTree::removeNode(Node* node, const string& key) {
    if (node == nullptr) {
        return node;
    }

    if (key < node->key) {
        node->left = removeNode(node->left, key);
    } else if (key > node->key) {
        node->right = removeNode(node->right, key);
    } else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = node->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        node->key = temp->key;
        node->right = removeNode(node->right, temp->key);
    }

    if (node == nullptr) {
        return node;
    }

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    return rebalance(node);
}

void AVLTree::remove(const string& key) { root = removeNode(root, key); }

bool AVLTree::search(const string& key) {
    Node* node = root;
    while (node != nullptr) {
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            return true;
        }
    }
    return false;
}

void AVLTree::printNode(Node* node) {
    if (node != nullptr) {
        printNode(node->left);
        cout << node->key << " ";
        printNode(node->right);
    }
}

void AVLTree::print() {
    printNode(root);
    cout << endl;
}

void AVLTree::saveNode(Node* node, ofstream& file) {
    if (node != nullptr) {
        saveNode(node->left, file);
        file << node->key << endl;
        saveNode(node->right, file);
    }
}

void AVLTree::saveToFile(const string& fileName) {
    ofstream file(fileName);
    if (file.is_open()) {
        saveNode(root, file);
        file.close();
    } else {
        cout << "Не удалось открыть файл для записи." << endl;
    }
}

void AVLTree::loadNode(ifstream& file) {
    string key;
    while (file >> key) {
        insert(key);
    }
}

void AVLTree::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        loadNode(file);
        file.close();
    } else {
        cout << "Не удалось открыть файл для чтения." << endl;
    }
}

void runAVLTree(int argc, char* argv[]) {
    AVLTree tree;

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

    tree.loadFromFile(fileName);

    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);
        query = query.substr(pos + 1);
    } else {
        command = query;
    }

    if (command == "TINSERT") {
        tree.insert(query);
        tree.saveToFile(fileName);
    } else if (command == "TREMOVE") {
        tree.remove(query);
        tree.saveToFile(fileName);
    } else if (command == "TSEARCH") {
        cout << (tree.search(query) ? "true" : "false") << endl;
    } else if (command == "PRINT") {
        tree.print();
    }
}