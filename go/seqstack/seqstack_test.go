package seqstack

import (
	"strconv"
	"testing"
)

func TestStack(t *testing.T) {
	s1 := New[string]()
	if !s1.IsEmpty() {
		t.Errorf("expecting stack empty")
	}

	s1.Push("alice")
	if s1.IsEmpty() {
		t.Errorf("expecting stack not empty")
	}
	if x, err := s1.Pop(); err != nil || x != "alice" {
		t.Errorf("expecting popped alice, got %v with error %v", x, err)
	}
	if x, err := s1.Pop(); err != errUnderflow || x != "" {
		t.Errorf("expecting underflow error, got x %v with error %v", x, err)
	}

	names := []string{"alice", "bob"}
	s2 := New(names...)
	if s2.IsEmpty() {
		t.Errorf("expecting stack not empty")
	}
	if x, err := s2.Top(); x != "bob" {
		t.Errorf("expecting top is bob, got %v with error %v", x, err)
	}
	if x, err := s2.Pop(); x != "bob" {
		t.Errorf("expecting popped bob, got %v with error %v", x, err)
	}
}

func TestIsBalancedExpr(t *testing.T) {
	for _, tt := range []struct {
		expr   string
		expect bool
	}{
		{"", true},
		{"(", false},
		{"a()a", true},
		{"a+b*(c)-d)", false},
		{"(()))(", false},
		{"a(a(b))c", true},
		{"(a+b)*c(-d)", true},
	} {
		if got := IsBalancedExpr(tt.expr); tt.expect != got {
			t.Errorf("expecting balanced %v for expr %v, got %v", tt.expect, tt.expr, got)
		}
	}
}

func TestIsSymmetry(t *testing.T) {
	for _, tt := range []struct {
		word   string
		expect bool
	}{
		{"", true},
		{"a", true},
		{"世", true},
		{"Hello, 世界", false},
		{"Hello, 世界世 ,olleH", true},
	} {
		if got := IsSymmetry(tt.word); tt.expect != got {
			t.Errorf("expecting IsSymmetryWord(%v)=%v, got %v", tt.word, tt.expect, got)
		}
	}
}

func TestDec2Base(t *testing.T) {
	for _, tt := range []struct {
		dec    uint
		base   uint
		expect string
	}{
		{0, 8, strconv.FormatUint(0, 8)},
		{3553, 8, strconv.FormatUint(3553, 8)},
		{3553, 2, strconv.FormatUint(3553, 2)},
		{100, 16, strconv.FormatUint(100, 16)},
		{0xff, 16, strconv.FormatUint(0xff, 16)},
	} {
		if got, _ := Dec2Base(tt.dec, tt.base); got != tt.expect {
			t.Errorf("expecting Dec2Base(%v, %v)=%v, got %v", tt.dec, tt.base, tt.expect, got)
		}
	}
}
