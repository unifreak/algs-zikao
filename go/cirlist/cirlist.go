package cirlist

import (
	"fmt"

	"golang.org/x/exp/constraints"
)

// Node contain actual data and point to next node in cirlink.
type Node[T constraints.Ordered] struct {
	data T
	next *Node[T]
}

// List is a circular linked list.
type List[T constraints.Ordered] struct {
	head *Node[T]
	len  int
}

// New create new cirlink from s.
func New[T constraints.Ordered](s ...T) *List[T] {
	// invariant:
	// rear point to last node
	// last node point to head
	head := &Node[T]{}
	head.next = head
	rear := head
	list := List[T]{head: head}

	for _, v := range s {
		x := &Node[T]{data: v}
		x.next = head
		rear.next = x
		rear = x
		list.len++
	}

	return &list
}

// SortedInsert insert node with data x in increasing order into list l.
func (l *List[T]) SortedInsert(x T) {
	// the trick is using two pointer p and q: q track the position should be
	// inserted into, p track the node before q for easy pointer manipulation.
	p, q := l.head, l.head.next
	// the end of a circular list is reached when meet the l.head again.
	for q != l.head && q.data < x {
		p, q = p.next, q.next
	}

	n := Node[T]{data: x}
	fmt.Printf("inserting %v before %v\n", n, q)
	n.next = q
	p.next = &n
	l.len++
}
