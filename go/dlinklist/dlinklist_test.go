package dlinklist

import "testing"

func TestNew(t *testing.T) {
	list := New[string]()
	if list.head.next != nil || list.head.prev != nil {
		t.Errorf("expecting empty list's head have nil next,prev pointers")
	}

	list = New([]string{"alice"}...)
	if list.head.next.data != "alice" {
		t.Errorf("expecting alice, got %v", list.head.next)
	}

	names := []string{"alice", "bob", "cathy"}
	list = New(names...)
	if list.len != 3 {
		t.Errorf("expecting list of length 3, got %v", list.len)
	}

	i, j := 0, 1
	for p, q := list.head.next, list.head.next.next; q != nil; p, q = p.next, q.next {
		if q.prev != p {
			t.Errorf("expecting p %v's prev = %v, got %v", p, q, p.prev)
		}
		if p.data != names[i] || q.data != names[j] {
			t.Errorf("expecting p.data = %v, q.data = %v, got %v, %v", names[i], names[j], p.data, q.data)
		}
		i, j = i+1, j+1
	}
}

func TestInsert(t *testing.T) {
	list := New([]string{"alice"}...)
	alice := list.head.next

	list.Insert("bob", alice)
	bob := alice.prev
	if bob.data != "bob" || bob.prev != list.head || bob.next != alice {
		t.Errorf("expecting bob(%v)'prev is head, next is alice, got %v, %v", bob.data, bob.prev, bob.next)
	}
}

func TestDelete(t *testing.T) {
	list := New([]string{"alice", "bob", "cathy"}...)
	bob := list.Delete(list.head.next.next)
	if bob != "bob" {
		t.Errorf("expecting deleted bob, got %v", bob)
	}
	if list.head.next.next.data != "cathy" {
		t.Errorf("expecting cathy, got %v", list.head.next.next.data)
	}
}
