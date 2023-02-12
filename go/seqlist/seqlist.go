package seqlist

import "fmt"

// Seqlist implements a sequence list using generic slice.
type Seqlist[T comparable] []T

// New return a new Seqlist.
func New[T comparable]() *Seqlist[T] {
	return new(Seqlist[T])
}

// Len return l's length.
func (l *Seqlist[T]) Len() int {
	return len(*l)
}

// Get return element at index i.
//
// Q1: I want to return (nil, error) when given invalid index i, and return
// (T, error) if success, it that possible? like a union return type:
//
// 		func (l *Seqlist[T]) Get(i int) (T|nil, error)
//
// A1: Union return type is not possible in golang, just do what you have done,
// use the zero value (in this case that of a pointer). It's conventional to let
// the client side to check the error code and do what they have to do.
func (l *Seqlist[T]) Get(i int) (T, error) {
	var v T
	if i < 0 || i > l.Len()-1 {
		return v, fmt.Errorf("invalid position %d", i)
	}
	return (*l)[i], nil
}

// Locate find the position of the first element who is equal to x.
func (l *Seqlist[T]) Locate(x T) (int, error) {
	for i, v := range *l {
		if v == x {
			return i, nil
		}
	}
	return 0, fmt.Errorf("not found")
}

// Insert insert x into l at position i.
func (l *Seqlist[T]) Insert(i int, x T) error {
	if i < 0 || i > l.Len() {
		return fmt.Errorf("invalid position %d", i)
	}

	// Q2: in order to modify the slice in place, I used *l as receiver, but
	// all those (*l) make me uncomfortable, is there a better way to acheive
	// this?
	//
	// A2: doesn't really seem like a problem. the pointer to l saves you a bit,
	// you're always talking about the same slice "header".

	*l = append((*l), *new(T))
	copy((*l)[i+1:], (*l)[i:])
	(*l)[i] = x

	return nil
}
