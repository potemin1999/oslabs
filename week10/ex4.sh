#! /bin/bash

gcc ex4.c -o ex4
mkdir ./tmp
echo "" > ./tmp/file1
echo "" > ./tmp/file2
ln ./tmp/file1 ./tmp/link1
./ex4
