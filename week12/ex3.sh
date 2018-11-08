#! /bin/bash

gcc copy.c $1 -o copy
echo "" >> ex3.txt
echo "$1" >> ex3.txt
(time ./copy /bin/bash /tmp/week_12_copy_test) |& tee -a ex3.txt
