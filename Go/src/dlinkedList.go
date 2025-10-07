package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// DlistNode — узел двусвязного списка
type DlistNode struct {
	data string
	next *DlistNode
	prev *DlistNode
}

// DlinkedList — двусвязный список
type DlinkedList struct {
	head *DlistNode
	tail *DlistNode
}

func (l *DlinkedList) Init() {
	l.head = nil
	l.tail = nil
}

func (l *DlinkedList) AddToHead(value string) {
	newNode := &DlistNode{data: value, next: l.head, prev: nil}
	if l.head != nil {
		l.head.prev = newNode
	}
	l.head = newNode
	if l.tail == nil {
		l.tail = l.head
	}
}

func (l *DlinkedList) AddToTail(value string) {
	newNode := &DlistNode{data: value, next: nil, prev: l.tail}
	if l.tail != nil {
		l.tail.next = newNode
	}
	l.tail = newNode
	if l.head == nil {
		l.head = l.tail
	}
}

func (l *DlinkedList) RemoveFromHead() {
	if l.head == nil {
		return
	}
	temp := l.head
	l.head = l.head.next
	if l.head != nil {
		l.head.prev = nil
	} else {
		l.tail = nil
	}
	_ = temp
}

func (l *DlinkedList) RemoveFromTail() {
	if l.tail == nil {
		return
	}
	temp := l.tail
	l.tail = l.tail.prev
	if l.tail != nil {
		l.tail.next = nil
	} else {
		l.head = nil
	}
	_ = temp
}

func (l *DlinkedList) RemoveByValue(value string) {
	for cur := l.head; cur != nil; cur = cur.next {
		if cur.data == value {
			if cur.prev != nil {
				cur.prev.next = cur.next
			} else {
				l.head = cur.next
			}
			if cur.next != nil {
				cur.next.prev = cur.prev
			} else {
				l.tail = cur.prev
			}
			return
		}
	}
}

func (l *DlinkedList) Search(value string) bool {
	for cur := l.head; cur != nil; cur = cur.next {
		if cur.data == value {
			return true
		}
	}
	return false
}

func (l *DlinkedList) Print() {
	first := true
	for cur := l.head; cur != nil; cur = cur.next {
		if !first {
			fmt.Print(" ")
		}
		first = false
		fmt.Print(cur.data)
	}
	fmt.Println()
}

func (l *DlinkedList) Destroy() {
	l.head = nil
	l.tail = nil
}

func (l *DlinkedList) LoadFromFile(fileName string) error {
	f, err := os.Open(fileName)
	if err != nil {
		return err
	}
	defer f.Close()
	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		l.AddToTail(scanner.Text())
	}
	return scanner.Err()
}

func (l *DlinkedList) SaveToFile(fileName string) error {
	f, err := os.Create(fileName)
	if err != nil {
		return err
	}
	defer f.Close()
	w := bufio.NewWriter(f)
	for cur := l.head; cur != nil; cur = cur.next {
		_, _ = w.WriteString(cur.data + "\n")
	}
	return w.Flush()
}

func runLLinkedList(fileName string, fullQuery string) {
	list := DlinkedList{}
	list.Init()
	_ = list.LoadFromFile(fileName) // если файла нет — продолжим с пустым списком

	parts := strings.SplitN(fullQuery, " ", 2)
	command := parts[0]
	arg := ""
	if len(parts) > 1 {
		arg = parts[1]
	}

	switch command {
	case "DPUSH":
		list.AddToHead(arg)
		_ = list.SaveToFile(fileName)
	case "DAPPEND":
		list.AddToTail(arg)
		_ = list.SaveToFile(fileName)
	case "DREMOVEHEAD":
		list.RemoveFromHead()
		_ = list.SaveToFile(fileName)
	case "DREMOVETAIL":
		list.RemoveFromTail()
		_ = list.SaveToFile(fileName)
	case "DREMOVE":
		list.RemoveByValue(arg)
		_ = list.SaveToFile(fileName)
	case "DSEARCH":
		if list.Search(arg) {
			fmt.Println("true")
		} else {
			fmt.Println("false")
		}
	case "DPRINT":
		list.Print()
	default:
		fmt.Fprintln(os.Stderr, "Unknown dlinkedlist command:", command)
	}

	list.Destroy()
}
