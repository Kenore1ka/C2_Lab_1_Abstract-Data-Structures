#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "array.h"
#include "avlTree.h"
#include "hashTable.h"
#include "linkedList.h"
#include "queue.h"
#include "stack.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 5) {
        return 1;
    }

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

    if (fileName.empty() || query.empty()) {
        return 1;
    }

    if (query[0] == 'M') {
        runDynamicArray(argc, argv);
    } else if (query[0] == 'L') {
        runLinkedList(argc, argv);
    } else if (query[0] == 'Q') {
        runQueue(argc, argv);
    } else if (query[0] == 'S') {
        runStack(argc, argv);
    } else if (query[0] == 'H') {
        runHashTable(argc, argv);
    } else if (query[0] == 'T') {
        runAVLTree(argc, argv);
    }

    return 0;
}