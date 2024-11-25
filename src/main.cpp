#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "array.h"
#include "avlTree.h"
#include "hashTable.h"
#include "linkedList.h"
#include "llinkedList.h"
#include "queue.h"
#include "stack.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 5) {        // Проверка наличия минимально необходимого количества аргументов.
        return 1;          // Завершение программы с кодом ошибки, если аргументов недостаточно.
    }

    string fileName;
    string query;

    // Парсинг аргументов командной строки для получения имени файла и команды.
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            fileName = argv[i + 1];
            i++; // Пропуск следующего аргумента, так как он уже обработан.
        } else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[i + 1];
            i++; // Пропуск следующего аргумента, так как он уже обработан.
        }
    }

    // Проверка, что оба параметра получены; если нет, завершение с ошибкой.
    if (fileName.empty() || query.empty()) {
        return 1;
    }

    // Выбор функции для запуска на основе первой буквы в команде `query`.
    if (query[0] == 'M') {             // Если команда начинается с 'M', выполняется функция динамического массива.
        runDynamicArray(argc, argv);
    } else if (query[0] == 'L') {      // Если команда начинается с 'L', выполняется функция для связного списка.
        runLinkedList(argc, argv);
    } else if (query[0] == 'LL'){
        runLLinkedList(argc, argv);
    } else if (query[0] == 'Q') {      // Если команда начинается с 'Q', выполняется функция для очереди.
        runQueue(argc, argv);
    } else if (query[0] == 'S') {      // Если команда начинается с 'S', выполняется функция для стека.
        runStack(argc, argv);
    } else if (query[0] == 'H') {      // Если команда начинается с 'H', выполняется функция для хэш-таблицы.
        runHashTable(argc, argv);
    } else if (query[0] == 'T') {      // Если команда начинается с 'T', выполняется функция для AVL-дерева.
        runAVLTree(argc, argv);
    }

    return 0; // Завершение программы.
}
