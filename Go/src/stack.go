package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// StackNode — узел стека (сохраним поведение C++: push добавляет в конец списка, pop удаляет с конца)
type StackNode struct {
	data string
	next *StackNode
}

// Stack — стек, реализованный как однонаправленный список с указателем на head ("top")
type Stack struct {
	top *StackNode
}

func (s *Stack) Init() {
	s.top = nil
}

// push добавляет элемент в конец списка (так же как C++ реализация)
func (s *Stack) Push(value string) {
	if s.top == nil {
		s.top = &StackNode{data: value, next: nil}
		return
	}
	cur := s.top
	for cur.next != nil {
		cur = cur.next
	}
	cur.next = &StackNode{data: value, next: nil}
}

// pop удаляет последний элемент
func (s *Stack) Pop() {
	if s.top == nil {
		return
	}
	if s.top.next == nil {
		s.top = nil
		return
	}
	cur := s.top
	for cur.next.next != nil {
		cur = cur.next
	}
	cur.next = nil
}

func (s *Stack) Print() {
	first := true
	for cur := s.top; cur != nil; cur = cur.next {
		if !first {
			fmt.Print(" ")
		}
		first = false
		fmt.Print(cur.data)
	}
	fmt.Println()
}

func (s *Stack) Destroy() {
	s.top = nil
}

func (s *Stack) LoadFromFile(fileName string) error {
	f, err := os.Open(fileName)
	if err != nil {
		return err
	}
	defer f.Close()
	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		s.Push(scanner.Text())
	}
	return scanner.Err()
}

func (s *Stack) SaveToFile(fileName string) error {
	f, err := os.Create(fileName)
	if err != nil {
		return err
	}
	defer f.Close()
	w := bufio.NewWriter(f)
	for cur := s.top; cur != nil; cur = cur.next {
		_, _ = w.WriteString(cur.data + "\n")
	}
	return w.Flush()
}

func runStack(fileName string, fullQuery string) {
	st := Stack{}
	st.Init()
	_ = st.LoadFromFile(fileName)

	parts := strings.SplitN(fullQuery, " ", 2)
	command := parts[0]
	arg := ""
	if len(parts) > 1 {
		arg = parts[1]
	}

	switch command {
	case "SPUSH":
		st.Push(arg)
		_ = st.SaveToFile(fileName)
	case "SPOP":
		st.Pop()
		_ = st.SaveToFile(fileName)
	case "SPRINT":
		st.Print()
	default:
		fmt.Fprintln(os.Stderr, "Неизвестная команда:", command)
	}

	st.Destroy()
}
