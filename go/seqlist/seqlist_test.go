package seqlist

import (
	"testing"
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
}
