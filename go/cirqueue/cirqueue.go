package cirqueue

import "errors"

// Q is an circular queue.
type Q[T any] struct {
	data        []T
	len         int
	front, rear int
}

var (
	errFull = errors.New("queue is full")
	errEmpty = errors.New("queue is empty")
)

// New create a Q which can hold n elements.
func New[T any](n uint) *Q[T] {
	// NOTE: to distinguish empty/full check, rear always point to a vacant
	// position, so we need n+1 positions.
	return &Q[T]{data: make([]T, n+1), len: int(n+1)}
}

// IsEmpty check whether q is empty.
func (q *Q[T]) IsEmpty() bool {
	return q.front == q.rear
}

// IsFull check whether q is full.
func (q *Q[T]) IsFull() bool {
	return ((q.rear+1) % q.len) == q.front
}

// Enqueue append new element of data x into q.
func (q *Q[T]) Enqueue(x T) error {
	if q.IsFull() {
		return errFull
	}
	q.data[q.rear] = x
	q.rear = (q.rear + 1) % q.len
	return nil
}

// Dequeue return next element in q, FIFO style.
func (q *Q[T]) Dequeue() (T, error) {
	var x T
	if q.IsEmpty() {
		return x, errEmpty
	}
	x = q.data[q.front]
	q.front = (q.front+1) % q.len
	return x, nil
}

// Front return next element in q, FIFO style, without removing it.
func (q *Q[T]) Front() (T, error) {
	var x T
	if q.IsEmpty() {
		return x, errEmpty
	}
	return q.data[q.front], nil
}