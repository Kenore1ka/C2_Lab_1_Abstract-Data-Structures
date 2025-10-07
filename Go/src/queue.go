package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// QueueNode — узел очереди
type QueueNode struct {
	data string
	next *QueueNode
}

// Queue — очередь FIFO
type Queue struct {
	front *QueueNode
	rear  *QueueNode
}

func (q *Queue) Init() {
	q.front = nil
	q.rear = nil
}

func (q *Queue) Enqueue(value string) {
	newNode := &QueueNode{data: value, next: nil}
	if q.rear != nil {
		q.rear.next = newNode
	}
	q.rear = newNode
	if q.front == nil {
		q.front = q.rear
	}
}

func (q *Queue) Dequeue() {
	if q.front == nil {
		return
	}
	temp := q.front
	q.front = q.front.next
	if q.front == nil {
		q.rear = nil
	}
	_ = temp
}

func (q *Queue) Print() {
	first := true
	for cur := q.front; cur != nil; cur = cur.next {
		if !first {
			fmt.Print(" ")
		}
		first = false
		fmt.Print(cur.data)
	}
	fmt.Println()
}

func (q *Queue) Destroy() {
	q.front = nil
	q.rear = nil
}

func (q *Queue) LoadFromFile(fileName string) error {
	f, err := os.Open(fileName)
	if err != nil {
		return err
	}
	defer f.Close()
	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		q.Enqueue(scanner.Text())
	}
	return scanner.Err()
}

func (q *Queue) SaveToFile(fileName string) error {
	f, err := os.Create(fileName)
	if err != nil {
		return err
	}
	defer f.Close()
	w := bufio.NewWriter(f)
	for cur := q.front; cur != nil; cur = cur.next {
		_, _ = w.WriteString(cur.data + "\n")
	}
	return w.Flush()
}

func runQueue(fileName string, fullQuery string) {
	q := Queue{}
	q.Init()
	_ = q.LoadFromFile(fileName)

	parts := strings.SplitN(fullQuery, " ", 2)
	command := parts[0]
	arg := ""
	if len(parts) > 1 {
		arg = parts[1]
	}

	switch command {
	case "QPUSH":
		q.Enqueue(arg)
		_ = q.SaveToFile(fileName)
	case "QPOP":
		q.Dequeue()
		_ = q.SaveToFile(fileName)
	case "QPRINT":
		q.Print()
	default:
		fmt.Fprintln(os.Stderr, "Unknown queue command:", command)
	}

	q.Destroy()
}
