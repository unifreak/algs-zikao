package seqlist

import (
	"testing"

	"golang.org/x/exp/constraints"
)

func TestSeqlist(t *testing.T) {
	l := New[string]()
	if l.Len() != 0 {
		t.Errorf("expecting new list's len is 0, got %d", l.Len())
	}
	if _, err := l.Get(0); err == nil {
		t.Errorf("expecting error, got nil error")
	}

	l.Insert(0, "hello")
	l.Insert(1, "world")
	l.Insert(2, "hello")
	l.Insert(1, "again")
	if i, _ := l.Locate("again"); i != 1 {
		t.Errorf("expecting 'again' at index 1, but located at %d", i)
	}
	if l.Len() != 4 {
		t.Errorf("expecting length == 4, got %d", l.Len())
	}

	x, _ := l.Delete(2)
	if x != "world" {
		t.Errorf("expecting deleted 'hello', got %s", x)
	}
	if l.Len() != 3 {
		t.Errorf("expecting length after deletion to be 3, got %d", l.Len())
	}
}

func TestReverse(t *testing.T) {
	type V = int
	tc := []struct {
		in     []V
		expect []V
	}{
		{[]V{}, []V{}},
		{[]V{1}, []V{1}},
		{[]V{1, 2}, []V{2, 1}},
		{[]V{1, 2, 3, 4, 5}, []V{5, 4, 3, 2, 1}},
	}

	for _, c := range tc {
		l := New[V]()
		fill(l, c.in)

		l.Reverse()
		if !equal([]V(*l), c.expect) {
			t.Errorf("expecting l to be %v, got %v", c.expect, l)
		}
	}
}

func fill[T constraints.Ordered](l *Seqlist[T], s []T) {
	for _, v := range s {
		l.Insert(l.Len(), v)
	}
}

func equal[T constraints.Ordered](a, b []T) bool {
	if len(a) != len(b) {
		return false
	}
	for i, v := range a {
		if b[i] != v {
			return false
		}
	}
	return true
}

func TestMaxMin(t *testing.T) {
	type V = float32
	tc := []struct {
		in         []V
		max, min   int
		maxV, minV V
	}{
		{[]V{}, 0, 0, 0, 0},
		{[]V{0, 0}, 0, 0, 0, 0},
		{[]V{5, 5.0, 1, -2.3, 2.3, -2.3}, 0, 3, 5, -2.3},
	}

	for _, c := range tc {
		l := New[V]()
		fill(l, c.in)

		max, min := l.MaxMin()

		maxV, _ := l.Get(max)
		if max != c.max || maxV != c.maxV {
			t.Errorf(
				"expecting max value %v at position %v, got %v at position %v",
				c.maxV, c.max, maxV, max)
		}

		minV, _ := l.Get(min)
		if min != c.min || minV != c.minV {
			t.Errorf(
				"expecting min value %v at position %v, got %v at position %v",
				c.minV, c.min, minV, min)
		}
	}
}

func TestUnion(t *testing.T) {
	type V = string
	tc := []struct {
		a, b, expect []V
	}{
		{[]V{}, []V{}, []V{}},
		{[]V{}, []V{""}, []V{""}},
		{
			[]V{"", "hello"},
			[]V{"world", "world", "", "bye"},
			[]V{"", "hello", "world", "bye"},
		},
	}

	for _, c := range tc {
		a := New[V]()
		fill(a, c.a)
		b := New[V]()
		fill(b, c.b)

		a.Union(b)
		if !equal([]V(*a), c.expect) {
			t.Errorf("expecting %v, got %v", c.expect, a)
		}
	}
}

func TestPurge(t *testing.T) {
	type V = string
	tc := []struct{
		in, expect []V
	}{
		{[]V{}, []V{}},
		{[]V{"", ""}, []V{""}},
		{[]V{"hello", "", "world", "", "", "hello"}, []V{"hello", "", "world"}},
	}

	for _, c := range tc {
		l := New[V]()
		fill(l, c.in)
		l.Purge()
		if !equal([]V(*l), c.expect) {
			t.Errorf("expecting %v, got %v", c.expect, l)
		}
	}
}