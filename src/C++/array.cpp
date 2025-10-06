#include "array.h"

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

// Инициализирует динамический массив с заданной начальной ёмкостью
void DynamicArray::init(int initialCapacity) {
    data = new string[initialCapacity]; // Выделение памяти под массив строк
    size = 0;                           // Текущий размер массива
    capacity = initialCapacity;         // Начальная ёмкость массива
}

// Изменяет ёмкость массива, увеличивая или уменьшая её
void DynamicArray::resize(int newCapacity) {
    string* newData = new string[newCapacity]; // Новый массив с новой ёмкостью
    for (int i = 0; i < size; i++) {           // Копирование существующих данных
        newData[i] = data[i];
    }
    delete[] data;                             // Удаление старого массива
    data = newData;                            // Замена на новый массив
    capacity = newCapacity;                    // Обновление ёмкости
}

// Добавляет новый элемент в конец массива
void DynamicArray::add(const string& value) {
    if (size == capacity) {               // Проверка, требуется ли увеличение ёмкости
        resize(capacity * 2);             // Удвоение ёмкости при необходимости
    }
    data[size++] = value;                 // Добавление нового элемента и увеличение размера
}

// Вставляет элемент в заданную позицию, сдвигая остальные элементы
void DynamicArray::insert(int index, const string& value) {
    if (index < 0 || index > size) {      // Проверка на корректность индекса
        return;                           // Выход из функции, если индекс некорректен
    }
    if (size == capacity) {               // Проверка, требуется ли увеличение ёмкости
        resize(capacity * 2);
    }
    for (int i = size; i > index; i--) {  // Сдвиг элементов вправо
        data[i] = data[i - 1];
    }
    data[index] = value;                  // Вставка нового элемента
    size++;                               // Увеличение размера
}

// Удаляет элемент из массива по индексу и сдвигает остальные элементы
void DynamicArray::remove(int index) {
    if (index < 0 || index >= size) {     // Проверка на корректность индекса
        return;
    }
    for (int i = index; i < size - 1; i++) { // Сдвиг элементов влево
        data[i] = data[i + 1];
    }
    size--;                              // Уменьшение размера массива
}

// Возвращает элемент по индексу, или пустую строку, если индекс некорректен
string DynamicArray::get(int index) {
    if (index < 0 || index >= size) {     // Проверка на корректность индекса
        return "";
    }
    return data[index];                   // Возвращение элемента
}

// Устанавливает значение элемента по индексу
void DynamicArray::set(int index, const string& value) {
    if (index < 0 || index >= size) {     // Проверка на корректность индекса
        return;
    }
    data[index] = value;                  // Установка нового значения
}

// Возвращает текущий размер массива
int DynamicArray::length() { return size; }

// Выводит все элементы массива на экран
void DynamicArray::print() {
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

// Освобождает выделенную память при завершении работы с массивом
void DynamicArray::destroy() { delete[] data; }

// Загружает данные из файла в массив, добавляя строки построчно
void DynamicArray::loadFromFile(const string& fileName) {
    ifstream file(fileName);              // Открытие файла для чтения
    string value;
    while (file >> value) {               // Чтение значений из файла построчно
        add(value);                       // Добавление значения в массив
    }
    file.close();                         // Закрытие файла
}

// Сохраняет содержимое массива в файл, записывая каждую строку в отдельную строку файла
void DynamicArray::saveToFile(const string& fileName) {
    ofstream file(fileName);              // Открытие файла для записи
    for (int i = 0; i < size; i++) {
        file << data[i] << endl;          // Запись каждого элемента на новую строку
    }
    file.close();                         // Закрытие файла
}

// Выполняет команды над динамическим массивом на основе аргументов командной строки
void runDynamicArray(int argc, char* argv[]) {
    DynamicArray arr;
    arr.init(10);                         // Инициализация массива с начальной ёмкостью 10

    string fileName;
    string query;

    for (int i = 1; i < argc; i++) {      // Обработка аргументов командной строки
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            fileName = argv[i + 1];       // Получение имени файла из аргумента
            i++;
        } else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[i + 1];          // Получение запроса из аргумента
            i++;
        }
    }

    arr.loadFromFile(fileName);           // Загрузка данных из файла в массив

    // Извлечение команды и параметров из запроса
    string command;
    size_t pos = query.find(' ');
    if (pos != string::npos) {
        command = query.substr(0, pos);   // Команда до первого пробела
        query = query.substr(pos + 1);    // Остальная часть запроса
    } else {
        command = query;                  // Если в запросе только команда
    }

    // Выполнение команды над массивом
    if (command == "MPUSH") {
        arr.add(query);                   // Добавление элемента в конец
        arr.saveToFile(fileName);         // Сохранение изменений в файл
    } else if (command == "MINSERT") {
        size_t pos = query.find(' ');
        int index = stoi(query.substr(0, pos));
        string value = query.substr(pos + 1);
        arr.insert(index, value);         // Вставка элемента по индексу
        arr.saveToFile(fileName);         // Сохранение изменений в файл
    } else if (command == "MDEL") {
        int index = stoi(query);
        arr.remove(index);                // Удаление элемента по индексу
        arr.saveToFile(fileName);         // Сохранение изменений в файл
    } else if (command == "MSET") {
        size_t pos = query.find(' ');
        int index = stoi(query.substr(0, pos));
        string value = query.substr(pos + 1);
        arr.set(index, value);            // Установка нового значения по индексу
        arr.saveToFile(fileName);         // Сохранение изменений в файл
    } else if (command == "MLEN") {
        cout << arr.length() << endl;     // Вывод текущего размера массива
    } else if (command == "MPRINT") {
        arr.print();                      // Вывод всех элементов массива
    } else if (command == "MGET") {
        int index = stoi(query);
        cout << arr.get(index) << endl;   // Вывод элемента по индексу
    }

    arr.destroy();                        // Освобождение памяти после выполнения команд
}
