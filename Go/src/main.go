package main

import (
	"fmt"
	"os"
)

func usageAndExit() {
	fmt.Fprintf(os.Stderr, "Usage: %s --file <filename> --query <QUERY>\n", os.Args[0])
	os.Exit(1)
}

func main() {
	if len(os.Args) < 5 {
		usageAndExit()
	}

	var fileName, query string
	for i := 1; i < len(os.Args); i++ {
		if os.Args[i] == "--file" && i+1 < len(os.Args) {
			fileName = os.Args[i+1]
			i++
		} else if os.Args[i] == "--query" && i+1 < len(os.Args) {
			query = os.Args[i+1]
			i++
		}
	}

	if fileName == "" || query == "" {
		usageAndExit()
	}

	switch query[0] {
	case 'M': // Динамический массив
		runDynamicArray(fileName, query)
	case 'L': // Односвязный список
		runLinkedList(fileName, query)
	case 'D': // Двусвязный список
		runLLinkedList(fileName, query)
	case 'Q': // Очередь
		runQueue(fileName, query)
	case 'S': // Стек
		runStack(fileName, query)
	default:
		fmt.Fprintln(os.Stderr, "Неизвестная команда.")
	}
}

// go build -o ../build/dbms main.go array.go linkedList.go dlinkedList.go queue.go stack.go 