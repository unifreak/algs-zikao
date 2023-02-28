// seqqueue implement a sequence queue.
package seqqueue

import "errors"

// Q is the sequence queue.
type Q[T any] []T

var (
	errEmpty = errors.New("queue is empty")
)

// Enqueue add new element into q.
func (q *Q[T]) Enqueue(x T) {
	*q = append((*q), x)
}

// Dequeue return and remove the front element from q.
func (q *Q[T]) Dequeue() (T, error) {
	var x T
	if len(*q) == 0 {
		return x, errEmpty
	}
	x, *q = (*q)[0], (*q)[1:]
	return x, nil
}
