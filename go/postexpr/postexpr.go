package postexpr

import (
	"fmt"
	"strings"
	"text/scanner"
	"unifreak/learn/algo/zikao/seqqueue"
)

type expr = seqqueue.Q[string]

func New(in string) expr {
	var s scanner.Scanner
	s.Init(strings.NewReader(in))
	for tok := s.Scan(); tok != scanner.EOF; tok = s.Scan() {
		txt := s.TokenText()
		switch txt {
		case 
		}
		fmt.Printf("%T, %v\n", s.TokenText(), s.TokenText())
	}
	return nil
}

// func parse(tok string) {
// 	if (tok == )
// }
