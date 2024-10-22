CC = g++                          # Компилятор
CFLAGS = -std=c++11 -Wall -Wextra # Флаги компиляции: используем стандарт C++11 и включаем предупреждения
BUILD_DIR = ../build              # Директория для хранения объектных файлов
TARGET = dbms                     # Название выходного исполняемого файла

SOURCES = $(wildcard *.cpp)                       # Все .cpp файлы в текущей директории
OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES)) # Путь к объектным файлам

all: $(BUILD_DIR) $(OBJECTS) $(TARGET)  # Цель по умолчанию

# Правило для создания директории сборки
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Правило для компиляции .cpp файлов в .o файлы
$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Правило для связывания объектных файлов в исполняемый файл
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BUILD_DIR)/$(TARGET)

# Правило для очистки объектных файлов
clean:
	rm -rf $(BUILD_DIR)/*
