package linklist

import "golang.org/x/exp/constraints"

// FrontCreateFrom create a List from s by inserting node before first node.
//
// Q#1: how to distinguish between a list that contain only one node whose data is
// emtpy and a list that only contain head node?
//
// A: a head node equals Node{nil, nil}, where as an empty node equals Node
// {<zerovalue>, nil}
//
// Q#2: then what if the <zerovalue> of data is nil?
//
// A: we use `var l List`, list is a *Node, a pointer, hence its zero value can
// be nil, a nil Node pointer denotes a nil list.
func FrontNewFrom[T constraints.Ordered](s []T) *List[T] {
	var front *Node[T]
	len := 0
	for _, v := range s {
		x := &Node[T]{data: v}
		if front == nil {
			front = x
		} else {
			x.next = front
			front = x
		}
		len++
	}
	return &List[T]{head: front, len: len}
}

// RearCreateFrom create a List from s by appending new node after rear.
func RearNewFrom[T constraints.Ordered](s []T) *List[T] {
	var front, rear *Node[T]
	len := 0
	for _, v := range s {
		x := &Node[T]{data: v}
		if front == nil {
			front = x
			rear = x
		} else {
			rear.next = x
			rear = x
		}
		len++
	}
	return &List[T]{head: front, len: len}
}
