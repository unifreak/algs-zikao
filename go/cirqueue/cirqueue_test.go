package cirqueue

import "testing"

func TestNew(t *testing.T) {
	q := New[string](0)
	if !q.IsEmpty() || !q.IsFull() {
		t.Errorf("expecting zero length q is empty and full")
	}

	q = New[string](1)
	if !q.IsEmpty() || q.IsFull() {
		t.Errorf("expecting q of length 1 is empty and not full")
	}
}

func TestQueue(t *testing.T) {
	q := New[string](3)
	q.Enqueue("alice")
	q.Enqueue("bob")
	q.Enqueue("cathy")
	if err := q.Enqueue("donna"); err != errFull {
		t.Errorf("expecting errFull, got %v", err)
	}
	if x, _ := q.Front(); x != "alice" {
		t.Errorf("expecting front is alice, got %v", x)
	}
	if x, _ := q.Dequeue(); x != "alice" {
		t.Errorf("expecting dequeued alice, got %v", x)
	}
	if x, _ := q.Dequeue(); x != "bob" {
		t.Errorf("expecting dequeued bob, got %v", x)
	}
	if err := q.Enqueue("donna again"); err == errFull {
		t.Errorf("expecting enqueue donna without error")
	}
	if x, _ := q.Front(); x != "cathy" {
		t.Errorf("expecting front is cathy")
	}
}
