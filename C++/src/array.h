#pragma once

#include <string>

// Структура, представляющая динамический массив строк
struct DynamicArray {
    std::string* data;    // Указатель на массив строк
    int size;             // Текущий размер массива (число элементов)
    int capacity;         // Ёмкость массива (максимальное число элементов, которое массив может хранить)

    void init(int initialCapacity);               // Инициализация массива с заданной ёмкостью
    void resize(int newCapacity);                 // Изменение ёмкости массива
    void add(const std::string& value);           // Добавление элемента в конец массива
    void insert(int index, const std::string& value); // Вставка элемента в заданную позицию
    void remove(int index);                       // Удаление элемента по индексу
    std::string get(int index);                   // Получение элемента по индексу
    void set(int index, const std::string& value); // Установка значения элемента по индексу
    int length();                                 // Возвращение текущего размера массива
    void print();                                 // Вывод всех элементов массива на экран
    void destroy();                               // Освобождение памяти, выделенной под массив
    void loadFromFile(const std::string& fileName); // Загрузка элементов массива из файла
    void saveToFile(const std::string& fileName);   // Сохранение элементов массива в файл
};

// Функция, управляющая динамическим массивом на основе командной строки
void runDynamicArray(int argc, char* argv[]);
