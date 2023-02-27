// Taken from https://go.dev/blog/when-generics
package seqstack

import (
	"errors"
	"fmt"
)

// Stack is a sequence stack.
type Stack[T any] []T

var (
	errOverflow  = errors.New("stack overflow")
	errUnderflow = errors.New("stack underflow")
)

// New create a new Stack from s.
func New[T any](s ...T) *Stack[T] {
	stack := make(Stack[T], 0, len(s))
	stack = append(stack, s...)
	return &stack
}

// IsEmpty report whether s is empty.
func (s *Stack[T]) IsEmpty() bool {
	return len(*s) == 0
}

// Push push x in s.
func (s *Stack[T]) Push(x T) {
	*s = append(*s, x)
}

// Pop retrieve the last pushed element from s.
func (s *Stack[T]) Pop() (T, error) {
	var x T
	if s.IsEmpty() {
		return x, errUnderflow
	}
	x, *s = (*s)[len(*s)-1], (*s)[:len(*s)-1]
	return x, nil
}

// Top retrieve last pushed element without deleting from s.
func (s *Stack[T]) Top() (T, error) {
	var x T
	if s.IsEmpty() {
		return x, errUnderflow
	}
	return (*s)[len(*s)-1], nil
}

// IsBalancedExpr check whether an expression's parenthesis is balanced.
func IsBalancedExpr(expr string) bool {
	s := New[rune]()
	for _, r := range expr {
		if r == '(' {
			s.Push(r)
		}
		if r == ')' {
			if _, err := s.Pop(); err == errUnderflow {
				return false
			}
		}
	}
	return s.IsEmpty()
}

// IsSymmetry check whether word is symmetry.
func IsSymmetry(word string) bool {
	s := New[rune]()
	w := []rune(word) // count rune, not byte.
	for i := 0; i < len(w)/2; i++ {
		s.Push(w[i])
	}
	for i := (len(w) + 1) / 2; i < len(w); i++ {
		if r, err := s.Pop(); err == errUnderflow || r != w[i] {
			return false
		}
	}
	return true
}

// Dec2Base convert decimal number N to specified base.
func Dec2Base(N uint, base uint) (string, error) {
	s := New[uint]()
	if N == 0 {
		return "0", nil
	}
	for N != 0 {
		s.Push(N % base)
		N = N / base
	}
	var result string
	for !s.IsEmpty() {
		digit, err := s.Pop()
		if err != nil {
			return "", err
		}
		result += fmt.Sprintf("%x", digit)
	}
	return result, nil
}
