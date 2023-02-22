package linklist

import (
	"testing"

	"golang.org/x/exp/constraints"
)

func TestNoHeadNewFrom(t *testing.T) {
	type T = string

	z := Node[T]{}
	alice := Node[T]{data: "alice"}
	bob := Node[T]{data: "bob"}
	cathy := Node[T]{data: "cathy"}

	tests := []struct {
		in          []string
		front, rear []Node[T]
	}{
		{
			[]string{},
			[]Node[T]{},
			[]Node[T]{},
		},
		{
			[]string{""},
			[]Node[T]{z},
			[]Node[T]{z},
		},
		{
			[]string{"alice", "bob", "cathy"},
			[]Node[T]{cathy, bob, alice},
			[]Node[T]{alice, bob, cathy},
		},
	}

	for _, test := range tests {
		l1 := FrontNewFrom((test.in))
		assertEqualNoHead(t, l1, test.front)

		l2 := RearNewFrom(test.in)
		assertEqualNoHead(t, l2, test.rear)
	}
}

func assertEqualNoHead[T constraints.Ordered](t *testing.T, l *List[T], s []Node[T]) {
	if len(s) != l.Len() {
		t.Errorf("expecting length of %v, got %v", len(s), l.Len())
	}
	n := l.head
	for _, x := range s {
		if x.data != (*n).data {
			t.Errorf("expectiong node %v, got %v", x, n)
			break
		}
		n = n.next
	}
}
