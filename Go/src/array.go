package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// DynamicArray — простая реализация динамического массива строк
type DynamicArray struct {
	data     []string
	capacity int
}

func (a *DynamicArray) Init(initialCapacity int) {
	if initialCapacity <= 0 {
		initialCapacity = 8
	}
	a.data = make([]string, 0, initialCapacity)
	a.capacity = initialCapacity
}

func (a *DynamicArray) resizeIfNeeded() {
	if len(a.data) == a.capacity {
		newCap := a.capacity * 2
		if newCap == 0 {
			newCap = 2
		}
		newData := make([]string, len(a.data), newCap)
		copy(newData, a.data)
		a.data = newData
		a.capacity = newCap
	}
}

func (a *DynamicArray) Add(value string) {
	a.resizeIfNeeded()
	a.data = append(a.data, value)
}

func (a *DynamicArray) Insert(index int, value string) {
	if index < 0 || index > len(a.data) {
		return
	}
	a.resizeIfNeeded()
	a.data = append(a.data, "")           // расширяем
	copy(a.data[index+1:], a.data[index:]) // сдвиг в право
	a.data[index] = value
}

func (a *DynamicArray) Remove(index int) {
	if index < 0 || index >= len(a.data) {
		return
	}
	copy(a.data[index:], a.data[index+1:])
	a.data = a.data[:len(a.data)-1]
}

func (a *DynamicArray) Get(index int) string {
	if index < 0 || index >= len(a.data) {
		return ""
	}
	return a.data[index]
}

func (a *DynamicArray) Set(index int, value string) {
	if index < 0 || index >= len(a.data) {
		return
	}
	a.data[index] = value
}

func (a *DynamicArray) Length() int {
	return len(a.data)
}

func (a *DynamicArray) Print() {
	for i := 0; i < len(a.data); i++ {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(a.data[i])
	}
	fmt.Println()
}

func (a *DynamicArray) LoadFromFile(fileName string) error {
	file, err := os.Open(fileName)
	if err != nil {
		// если файла нет — оставляем пустой массив (как поведение C++: файл мог отсутствовать)
		return err
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	// сканируем по словам (по умолчанию Scanner.Split(bufio.ScanWords)), чтобы повторять поведение C++ >> operator
	for scanner.Scan() {
		a.Add(scanner.Text())
	}
	return scanner.Err()
}

func (a *DynamicArray) SaveToFile(fileName string) error {
	f, err := os.Create(fileName)
	if err != nil {
		return err
	}
	defer f.Close()
	w := bufio.NewWriter(f)
	for _, s := range a.data {
		_, _ = w.WriteString(s + "\n")
	}
	return w.Flush()
}

// runDynamicArray — выполняет команды для массива, интерфейс совместим с исходным.
func runDynamicArray(fileName string, fullQuery string) {
	arr := DynamicArray{}
	arr.Init(10)
	_ = arr.LoadFromFile(fileName) // игнорируем ошибку: возможно файл отсутствует

	// разделяем команду и аргументы
	parts := strings.SplitN(fullQuery, " ", 2)
	command := parts[0]
	arg := ""
	if len(parts) > 1 {
		arg = parts[1]
	}

	switch command {
	case "MPUSH":
		arr.Add(arg)
		if err := arr.SaveToFile(fileName); err != nil {
			fmt.Fprintln(os.Stderr, "Save error:", err)
		}
	case "MINSERT":
		// формат: "<index> <value>"
		sub := strings.SplitN(arg, " ", 2)
		if len(sub) != 2 {
			return
		}
		idx, err := strconv.Atoi(sub[0])
		if err != nil {
			return
		}
		arr.Insert(idx, sub[1])
		_ = arr.SaveToFile(fileName)
	case "MDEL":
		idx, err := strconv.Atoi(arg)
		if err != nil {
			return
		}
		arr.Remove(idx)
		_ = arr.SaveToFile(fileName)
	case "MSET":
		sub := strings.SplitN(arg, " ", 2)
		if len(sub) != 2 {
			return
		}
		idx, err := strconv.Atoi(sub[0])
		if err != nil {
			return
		}
		arr.Set(idx, sub[1])
		_ = arr.SaveToFile(fileName)
	case "MLEN":
		fmt.Println(arr.Length())
	case "MPRINT":
		arr.Print()
	case "MGET":
		idx, err := strconv.Atoi(arg)
		if err != nil {
			return
		}
		fmt.Println(arr.Get(idx))
	default:
		fmt.Fprintln(os.Stderr, "Неизвестная команда:", command)
	}
}
