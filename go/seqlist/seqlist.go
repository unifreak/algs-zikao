package seqlist

import (
	"fmt"

	"golang.org/x/exp/constraints"
)

// Seqlist implements a sequence list using generic slice.
type Seqlist[T constraints.Ordered] []T

// New return a new Seqlist.
func New[T constraints.Ordered]() *Seqlist[T] {
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
//	func (l *Seqlist[T]) Get(i int) (T|nil, error)
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

// Delete delete and return element at position i.
func (l *Seqlist[T]) Delete(i int) (T, error) {
	var x T
	if i < 0 || i > l.Len() {
		return x, fmt.Errorf("invalid position %d", i)
	}

	x = (*l)[i]
	copy((*l)[i:], (*l)[i+1:])
	*l = (*l)[:l.Len()-1]

	return x, nil
}

// Reverse reverse elements in l.
func (l *Seqlist[T]) Reverse() {
	for i, j := 0, l.Len()-1; i < j; i, j = i+1, j-1 {
		(*l)[i], (*l)[j] = (*l)[j], (*l)[i]
	}
}

// MaxMin find the positions of both max and min elements in l.
func (l *Seqlist[T]) MaxMin() (int, int) {
	if l.Len() == 0 {
		return 0, 0
	}

	var max, min = 0, 0
	var maxV, minV = (*l)[0], (*l)[0]

	for i, v := range *l {
		if v > maxV {
			max, maxV = i, v
		}
		if v < minV {
			min, minV = i, v
		}
	}

	return max, min
}

// Union put elements from b which is not in a into a.
func (a *Seqlist[T]) Union(b *Seqlist[T]) {
	for _, v := range (*b) {
		if _, err := a.Locate(v); err != nil {
			a.Insert(a.Len(), v)
		}
	}
}

// Purge remove duplicating elements from l.
func (l *Seqlist[T]) Purge() {
	for i, x := range (*l) {
		// NOTE: we cannot simply do a
		//
		// 		for j, y := range (*l)[i+1:] { ... }
		//
		// the inner loop will trigger a "out of range" error. Changing slice's
		// length cannot be picked up by for loop, the iteration count is defined
		// before loop.
		for j := i+1; j < l.Len(); {
			if (*l)[j] == x {
				l.Delete(j)
			} else {
				j++
			}
		}
	}
}