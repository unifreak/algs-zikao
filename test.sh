#!/bin/bash

if [ -z "$1" ] || [ $# -ne 1 ]; then
    echo "syntax: test <filename>"
    echo "example"
    echo "-test CirQueue    run CirQueueTest.c to test CirQueue.c"
fi

file="$1"
testfile="$file""Test.c"
if [ -e $testfile ]; then
    echo $testfile
    gcc ./$testfile -o $file"Test"
    ./$file"Test"
else
    echo "test file for $file not found"
fi
