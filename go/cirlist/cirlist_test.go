// Q: How to reuse equal across list tests?
package cirlist

import (
	"testing"
)

func TestNew(t *testing.T) {
	list := New[string]()
	if list.head.next != list.head || list.len != 0 {
		t.Errorf("expecting circular refence of head and length of 0")
	}

	names := []string{"alice", "bob", "cathy"}
	list = New(names...)

	node := list.head.next
	for i, name := range names {
		if node.data != name {
			t.Errorf("expecting name %v at position %v, got %v", name, i, node.data)
		}
		node = node.next
	}
	if node != list.head {
		t.Errorf("expecting head, got %v", node)
	}
	if list.len != len(names) {
		t.Errorf("expecting length of %v, got %v", len(names), list.len)
	}
}

func TestSortInsert(t *testing.T) {
	list := New[string]()
	unsorted := []string{"alice", "donna", "cathy", "alice", "bob"}
	sorted := []string{"alice", "alice", "bob", "cathy", "donna"}
	for _, name := range unsorted {
		list.SortedInsert(name)
	}

	node := list.head.next
	for _, name := range sorted {
		if node.data != name {
			t.Errorf("expecting name %v, got %v", name, node.data)
		}
		node = node.next
	}
	if node != list.head {
		t.Errorf("expecting back to head, got %v", node)
	}
}
