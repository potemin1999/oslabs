#! /bin/bash

echo "Compiling..."
echo
gcc ex3.c -o ex3 | grep "note:"
echo
echo "Starting..."
./ex3

