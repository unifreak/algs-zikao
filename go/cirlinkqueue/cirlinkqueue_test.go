package cirlinkqueue

import "testing"

func TestNew(t *testing.T) {
	q := New[string]()
	if !q.IsEmpty() {
		t.Errorf("expecting new queue is empty")
	}
}

func TestQueue(t *testing.T) {
	q := New[string]()
	if _, err := q.Dequeue(); err != errEmpty {
		t.Errorf("expecting errEmpty when dequeu from empty queue")
	}

	q.Enqueue("alice")
	q.Enqueue("bob")
	q.Enqueue("cathy")
	if x, _ := q.Dequeue(); x != "alice" {
		t.Errorf("expecting alice, got %v", x)
	}
	if x, _ := q.Dequeue(); x != "bob" {
		t.Errorf("expecting bob, got %v", x)
	}
	q.Enqueue("donna")
	if x, _ := q.Dequeue(); x != "cathy" {
		t.Errorf("expecting alice, got %v", x)
	}
	if x, _ := q.Dequeue(); x != "donna" {
		t.Errorf("expecting bob, got %v", x)
	}
	if _, err := q.Dequeue(); err != errEmpty {
		t.Errorf("expecting errEmpty, got %v", err)
	}
}
