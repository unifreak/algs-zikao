package linkqueue

import "testing"

func TestQueue(t *testing.T) {
	q := New[string]()
	if !q.IsEmpty() {
		t.Errorf("expecting new queue's front and rear point to head")
	}

	q.Enqueue("alice")
	q.Enqueue("bob")
	if x, err := q.Front(); x != "alice" || err != nil {
		t.Errorf("expecting q.Front()=alice, got %v with error %v", x, err)
	}
	if x, err := q.Dequeue(); x != "alice" || err != nil {
		t.Errorf("expecting q.Dequeue()=alice, got %v with error %v", x, err)
	}
	if x, err := q.Dequeue(); x != "bob" || err != nil {
		t.Errorf("expecting q.Dequeue()=bob, got %v with error %v", x, err)
	}

	if x, err := q.Dequeue(); err != errEmpty {
		t.Errorf("expecting errEmpty, got %v with error %v", x, err)
	}
	if !q.IsEmpty() {
		t.Errorf("expecting empty queue's front and rear point to head")
	}
}

