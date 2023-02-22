// TODO:
//   - make the List create by user using new() without a valid head sensible.
//     currently a List with nil head will break methods.
package linklist

import (
	"fmt"

	"golang.org/x/exp/constraints"
)

type Node[T constraints.Ordered] struct {
	data T
	next *Node[T]
}

type List[T constraints.Ordered] struct {
	head *Node[T]
	len  int
}

// NewFrom create a List from s by appending.
func NewFrom[T constraints.Ordered](s []T) *List[T] {
	// invariant:
	// first node is always zero valued node.
	// rear always point to last node.
	head := new(Node[T])
	rear := head
	len := 0 // head count 1
	for _, v := range s {
		x := &Node[T]{data: v}
		rear.next = x
		rear = x
		len++
	}

	return &List[T]{head: head, len: len}
}

// Len return length of l.
func (l *List[T]) Len() int {
	return l.len
}

// Get return the nth(0-based) node in list.
func (l *List[T]) Get(pos int) (*Node[T], error) {
	if pos < 0 || pos > l.Len()-1 {
		return nil, fmt.Errorf("Position error")
	}

	x := l.head.next
	for i := 0; i < pos; i++ {
		x = x.next
	}

	return x, nil
}

// Locate return the first node whose data matches t.
func (l *List[T]) Locate(x T) *Node[T] {
	for p := l.head.next; p != nil; p = p.next {
		if p.data == x {
			return p
		}
	}
	return nil
}

// Insert insert new node with data at position pos.
func (l *List[T]) Insert(pos int, data T) error {
	// NOTE: we cannot restrict pos as error if pos > l.Len-1, becuase when l is
	// empty (contain only head node and Len is 0), we should allow insertion
	// at pos 0.
	if pos < 0 {
		return fmt.Errorf("Position error")
	}

	p := l.head
	for i := 0; i < pos && p != nil; i++ {
		p = p.next
	}

	/// now p is either at the position we intended to insert at (i == pos
	//  stopped loop), or doesn't exists (p == nil stopped loop).
	if p == nil {
		return fmt.Errorf("Position error")
	}

	x := Node[T]{data: data}
	x.next = p.next
	p.next = &x
	l.len++
	return nil
}

// Empty report whether l is empty.
func (l *List[T]) Empty() bool {
	return l.head == nil || l.Len() == 0
}

// Delete delete node at pos and return its data.
func (l *List[T]) Delete(pos int) (T, error) {
	var x T
	if l.Empty() {
		return x, fmt.Errorf("List is empty")
	}
	if pos < 0 || pos > l.Len()-1 {
		return x, fmt.Errorf("Position error")
	}

	p := l.head
	for i := 0; i < pos; i++ {
		p = p.next
	}

	x = p.next.data
	p.next = p.next.next
	l.len--
	return x, nil
}

// Split seperate node at odd position in l and return the odd list.
func (l *List[T]) Split() *List[T] {
	odd := NewFrom([]T{})
	rear := odd.head
	for p := l.head.next; p != nil; p = p.next {
		// we process p and p.next at once. becuase p is at even position, if
		// p.next exists, it must be at odd position.
		if p.next != nil {
			// remove next node (x) from l.
			x := p.next
			p.next = x.next
			l.len--

			// add x into odd.
			x.next = rear.next
			rear.next = x
			rear = x
			odd.len++
		}
	}
	return odd
}

// Merge merge two sorted list a and b into one.
func Merge[T constraints.Ordered](a, b *List[T]) (*List[T], error) {
	if !a.Sorted() || !b.Sorted() {
		return nil, fmt.Errorf("List must be sorted")
	}

	t := NewFrom([]T{})
	rear := t.head
	pa, pb := a.head.next, b.head.next
	for pa != nil && pb != nil {
		if pa.data <= pb.data {
			rear.next = pa
			rear = pa
			pa = pa.next
		} else {
			rear.next = pb
			rear = pb
			pb = pb.next
		}
		t.len++
	}

	// append what's left from either a or b.
	if pa == nil {
		rear.next = pb
	}
	if pb == nil {
		rear.next = pa
	}

	for rear.next != nil {
		t.len++
		rear = rear.next
	}
	return t, nil
}

// Sorted report whether l is sorted increasely.
func (l *List[T]) Sorted() bool {
	for p := l.head.next; p.next != nil; p = p.next {
		if p.next.data < p.data {
			return false
		}
	}
	return true
}
