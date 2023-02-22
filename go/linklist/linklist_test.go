package linklist

import (
	"testing"

	"golang.org/x/exp/constraints"
)

func TestNewFrom(t *testing.T) {
	type T = string
	var head Node[T]

	z := Node[T]{}
	alice := Node[T]{data: "alice"}
	bob := Node[T]{data: "bob"}
	cathy := Node[T]{data: "cathy"}

	tests := []struct {
		in     []string
		expect []Node[T]
	}{
		{
			[]string{},
			[]Node[T]{head},
		},
		{
			[]string{""},
			[]Node[T]{head, z},
		},
		{
			[]string{"alice", "bob", "cathy"},
			[]Node[T]{head, alice, bob, cathy},
		},
	}

	for _, test := range tests {
		list := NewFrom(test.in)
		assertEqual(t, list, test.expect)
	}
}

func assertEqual[T constraints.Ordered](t *testing.T, list *List[T], s []Node[T]) {
	if len(s)-1 != list.Len() {
		t.Errorf("expecting length of %v, got %v", len(s), list.Len())
	}
	p := list.head
	for _, x := range s {
		if p == nil || x.data != (*p).data {
			t.Errorf("expectiong node %v, got %v", x, p)
			break
		}
		p = p.next
	}
}

func TestGet(t *testing.T) {
	list := NewFrom([]int{5, 3, 3, 42})
	node, err := list.Get(-1)
	if err == nil {
		t.Errorf("expecting error, got %v", err)
	}

	node, err = list.Get(1)
	if (*node).data != 3 {
		t.Errorf("expectiong node data 3, got %v", (*node).data)
	}
}

func TestLocate(t *testing.T) {
	list := NewFrom([]string{"alice", "bob", "bob", ""})

	got := list.Locate("bob")
	if got.data != "bob" {
		t.Errorf("expecting bob, got %v", got)
	}

	got = list.Locate("")
	if got == nil || got.data != "" {
		t.Errorf("expecting empty, got %v", got)
	}

	got = list.Locate("cathy")
	if got != nil {
		t.Errorf("expecting nil, got %v", got)
	}
}

func TestInsert(t *testing.T) {
	list := NewFrom([]string{})

	err1 := list.Insert(-1, "")
	err2 := list.Insert(1, "")
	if err1 == nil || err2 == nil {
		t.Errorf("expecing error, got nil")
	}

	list.Insert(0, "alice")
	alice, err := list.Get(0)
	if err != nil || alice.data != "alice" {
		t.Errorf("expecting alice, got %v with error %v", alice, err)
	}

	list.Insert(1, "bob")
	list.Insert(1, "cathy")
	bob, _ := list.Get(2)
	if bob.data != "bob" {
		t.Errorf("expecting bob, got %v", bob)
	}

	cathy, _ := list.Get(1)
	if cathy.data != "cathy" {
		t.Errorf("expecting cathy, got %v", cathy)
	}
}

func TestDelete(t *testing.T) {
	list := NewFrom([]string{})

	_, err := list.Delete(0)
	if err == nil {
		t.Errorf("expecting err, got nil")
	}

	list2 := NewFrom([]string{"alice", "bob", "bob"})
	alice, err := list2.Delete(0)
	if err != nil || alice != "alice" {
		t.Errorf("expecting alice, got %v with error %v", alice, err)
	}

	bob, err := list2.Delete(0)
	if err != nil || bob != "bob" {
		t.Errorf("expecting bob, got %v with error %v", bob, err)
	}

	if list2.Len() != 1 {
		t.Errorf("expecting list2 is now of length 1, got length %v", list2.Len())
	}
}

func TestSplit(t *testing.T) {
	list := NewFrom([]string{})
	odd := list.Split()
	if !list.Empty() || !odd.Empty() {
		t.Errorf("expecting both list to be empty, got %v, %v", list, odd)
	}

	list = NewFrom([]string{""})
	odd = list.Split()
	if list.Len() != 1 || odd.Len() != 0 {
		t.Errorf("expecting list to be length of 1 and odd length of 0, got %v %v", list.Len(), odd.Len())
	}

	list = NewFrom([]string{"alice", "bob", "cathy", "donna"})
	odd = list.Split()

	alice, _ := list.Get(0)
	cathy, _ := list.Get(1)
	if alice.data != "alice" || cathy.data != "cathy" {
		t.Errorf("expecting alice at 0, cathy at 1 in list, got %v, %v", alice, cathy)
	}

	bob, _ := odd.Get(0)
	donna, _ := odd.Get(1)
	if bob.data != "bob" || donna.data != "donna" {
		t.Errorf("expecting bob at 0, donna at 1 inst odd, got %v, %v", bob, donna)
	}
}

func TestMerge(t *testing.T) {
	l1 := NewFrom([]string{"bob", "alice"})
	l2 := NewFrom([]string{"alice", "bob", "bob"})
	l3 := NewFrom([]string{"alice", "cathy", "donna"})

	l4, err := Merge(l1, l2)
	if err == nil {
		t.Errorf("expecting error reporting unsorted list, got nil")
	}

	l4, err = Merge(l2, l3)
	var head Node[string]
	alice := Node[string]{data: "alice"}
	bob := Node[string]{data: "bob"}
	cathy := Node[string]{data: "cathy"}
	donna := Node[string]{data: "donna"}
	assertEqual(t, l4, []Node[string]{head, alice, alice, bob, bob, cathy, donna})
}
