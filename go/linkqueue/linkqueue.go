// linkqueue is a linked queue.
package linkqueue

import (
	"errors"
)

// Node is linked queue node.
type Node[T any] struct {
	data T
	next *Node[T]
}

// Q is the linked queue.
type Q[T any] struct {
	front, rear *Node[T]
}

var (
	errEmpty = errors.New("queue is empty")
)

// New create new linked queue.
func New[T any]() *Q[T] {
	head := new(Node[T])
	return &Q[T]{head, head}
}

// IsEmpty check whether the linked queue q is empty.
func (q *Q[T]) IsEmpty() bool {
	return q.front == q.rear
}

// Enqueue add a new node with data x into linked queue q.
func (q *Q[T]) Enqueue(x T) {
	n := &Node[T]{data: x}
	q.rear.next = n
	q.rear = n
}

// Dequeue remove and return data of the front node.
func (q *Q[T]) Dequeue() (T, error) {
	var x T
	if q.IsEmpty() {
		return x, errEmpty
	}

	// One way to dequeue the front node is like:
	//
	// 	n := q.front.next
	// 	q.front.next = n.next
	// 	if n == q.rear {
	// 		q.rear = q.head
	// 	}
	// 	return n.data, nil
	//
	// As you can see, the above logic to remove front node requiring us to
	// check for whehter there is only one node left. We can eliminate this
	// check by move front to next node, so the next node becomes new head, like:

	q.front = q.front.next
	return q.front.data, nil
}

// Front return data of the front node without removing it from queue.
func (q *Q[T]) Front() (T, error) {
	var x T
	if q.IsEmpty() {
		return x, errEmpty
	}
	return q.front.next.data, nil
}