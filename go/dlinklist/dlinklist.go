package dlinklist

import (
	"golang.org/x/exp/constraints"
)

// Node contains actual data.
type Node[T constraints.Ordered] struct {
	data T
	prev *Node[T]
	next *Node[T]
}

// List is a doubly linked list.
type List[T constraints.Ordered] struct {
	head *Node[T]
	len  int
}

// New create a new doubly linked list from s by appending.
func New[T constraints.Ordered](s ...T) *List[T] {
	list := List[T]{head: &Node[T]{}}
	rear := list.head
	for _, v := range s {
		x := &Node[T]{data: v}
		x.next = rear.next
		x.prev = rear
		rear.next = x
		rear = x
		list.len++
	}

	return &list
}

// Insert add new node containing data before n.
// NOTE: Insert assume n already in l.
func (l *List[T]) Insert(data T, n *Node[T]) {
	x := &Node[T]{data: data}
	x.next = n
	x.prev = n.prev
	n.prev.next = x
	n.prev = x
	l.len++
}

// Delete remove n from l and return n's data.
// NOTE: Delete assume n already in l.
func (l *List[T]) Delete(n *Node[T]) T {
	n.next.prev = n.prev
	n.prev.next = n.next
	l.len--
	return n.data
}