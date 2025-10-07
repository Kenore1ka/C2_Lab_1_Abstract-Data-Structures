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
	case 'M': // DynamicArray
		runDynamicArray(fileName, query)
	case 'L': // Single linked list
		runLinkedList(fileName, query)
	case 'D': // Doubly linked list
		runLLinkedList(fileName, query)
	case 'Q': // Queue
		runQueue(fileName, query)
	case 'S': // Stack
		runStack(fileName, query)
	default:
		fmt.Fprintln(os.Stderr, "Unknown query type.")
	}
}

// go build -o ../build/dbms main.go array.go linkedList.go dlinkedList.go queue.go stack.go 