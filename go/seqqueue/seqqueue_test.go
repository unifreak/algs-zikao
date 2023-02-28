package seqqueue

import "testing"

func TestQueue(t *testing.T) {
	q := new(Q[string])
	if _, err := q.Dequeue(); err != errEmpty {
		t.Errorf("expecing errEmpty")
	}

	q.Enqueue("alice")
	q.Enqueue("bob")
	if x, _ := q.Dequeue(); x != "alice" {
		t.Errorf("expecting alice, got %v", x)
	}
	if x, _ := q.Dequeue(); x != "bob" {
		t.Errorf("expecting bob, got %v", x)
	}
}
