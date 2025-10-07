package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// ListNode — узел списка
type ListNode struct {
	data string
	next *ListNode
}

// LinkedList — односвязный список
type LinkedList struct {
	head *ListNode
	tail *ListNode
}

func (l *LinkedList) Init() {
	l.head = nil
	l.tail = nil
}

func (l *LinkedList) AddToHead(value string) {
	newNode := &ListNode{data: value, next: l.head}
	l.head = newNode
	if l.tail == nil {
		l.tail = l.head
	}
}

func (l *LinkedList) AddToTail(value string) {
	newNode := &ListNode{data: value, next: nil}
	if l.tail != nil {
		l.tail.next = newNode
	}
	l.tail = newNode
	if l.head == nil {
		l.head = l.tail
	}
}

func (l *LinkedList) RemoveFromHead() {
	if l.head == nil {
		return
	}
	l.head = l.head.next
	if l.head == nil {
		l.tail = nil
	}
}

func (l *LinkedList) RemoveFromTail() {
	if l.tail == nil {
		return
	}
	if l.head == l.tail {
		l.head = nil
		l.tail = nil
		return
	}
	cur := l.head
	for cur.next != nil && cur.next != l.tail {
		cur = cur.next
	}
	cur.next = nil
	l.tail = cur
}

func (l *LinkedList) RemoveByValue(value string) {
	if l.head == nil {
		return
	}
	if l.head.data == value {
		l.RemoveFromHead()
		return
	}
	prev := l.head
	cur := l.head.next
	for cur != nil {
		if cur.data == value {
			prev.next = cur.next
			if cur == l.tail {
				l.tail = prev
			}
			return
		}
		prev = cur
		cur = cur.next
	}
}

func (l *LinkedList) Search(value string) bool {
	cur := l.head
	for cur != nil {
		if cur.data == value {
			return true
		}
		cur = cur.next
	}
	return false
}

func (l *LinkedList) Print() {
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

func (l *LinkedList) Destroy() {
	l.head = nil
	l.tail = nil
}

// LoadFromFile — читает слова из файла и добавляет в хвост (поведение как у C++ >>)
func (l *LinkedList) LoadFromFile(fileName string) error {
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

func (l *LinkedList) SaveToFile(fileName string) error {
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

// runLinkedList — обрабатывает команды списка
func runLinkedList(fileName string, fullQuery string) {
	list := LinkedList{}
	list.Init()
	_ = list.LoadFromFile(fileName) // если файла нет — получим пустой список

	parts := strings.SplitN(fullQuery, " ", 2)
	command := parts[0]
	arg := ""
	if len(parts) > 1 {
		arg = parts[1]
	}

	switch command {
	case "LPUSH":
		list.AddToHead(arg)
		_ = list.SaveToFile(fileName)
	case "LAPPEND":
		list.AddToTail(arg)
		_ = list.SaveToFile(fileName)
	case "LREMOVEHEAD":
		list.RemoveFromHead()
		_ = list.SaveToFile(fileName)
	case "LREMOVETAIL":
		list.RemoveFromTail()
		_ = list.SaveToFile(fileName)
	case "LREMOVE":
		list.RemoveByValue(arg)
		_ = list.SaveToFile(fileName)
	case "LSEARCH":
		if list.Search(arg) {
			fmt.Println("true")
		} else {
			fmt.Println("false")
		}
	case "LPRINT":
		list.Print()
	default:
		fmt.Fprintln(os.Stderr, "Неизвестная команда:", command)
	}

	list.Destroy()
}
