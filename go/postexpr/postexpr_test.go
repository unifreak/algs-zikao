package postexpr

import "testing"

func TestNew(t *testing.T) {
	for _, tt := range []struct{
		in string
		expect []string
	} {
		{"1", []string{"1"}},
		{"1	+ 	 2", []string{"1", "2", "+"}},
		{"(8+5)*(7-3)", []string{"8", "5", "+", "7", "3", "-", "*"}},
		{"(8 + 62)/2.5 ) * (72-3)", []string{"8", "62", "+", "2.5", "/", "72", "3", "-", "*"}},
	} {
		expr := New(tt.in)
		for _, expect := range(tt.expect) {
			if x, err := expr.Dequeue(); err != nil || x != expect {
				t.Errorf("expecting %v, got %v", expect, x)
			}
		}
	}
}
