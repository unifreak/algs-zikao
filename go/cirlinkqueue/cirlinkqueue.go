// cirlinkqueue implement a circular linked queue.
package cirlinkqueue

import "errors"

// Node is the node in queue.
type Node[T any] struct {
	data T
	next *Node[T]
}

// Q is the circular linked queue.
type Q[T any] struct {
	rear *Node[T]
}

var (
	errEmpty = errors.New("queue is empty")
)

// New create new Q.
func New[T any]() *Q[T] {
	rear := &Node[T]{}
	rear.next = rear
	return &Q[T]{rear: rear}
}

// IsEmpty check whether q is empty.
func (q *Q[T]) IsEmpty() bool {
	return q.rear.next == q.rear
}

// Dequeue remove the front node in q and return its data.
func (q *Q[T]) Dequeue() (T, error) {
	var x T
	if q.IsEmpty() {
		return x, errEmpty
	}
	front := q.rear.next.next
	q.rear.next = front
	return front.data, nil
}

// Enqueue add a new node containing data x into q.
func (q *Q[T]) Enqueue(x T) {
	n := &Node[T]{data: x}
	n.next = q.rear.next
	q.rear.next = n
	q.rear = n
}
