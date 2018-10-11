#! /bin/bash -i

#almost the same script, as in ex2

gcc ex2.c -o ex2
./ex2 &
top -d 1
pid=$(ps | grep 'ex2' | grep -Eo '^[^ ]+')
kill $pid
exit


