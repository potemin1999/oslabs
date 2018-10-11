#! /bin/bash -i

gcc ex2.c -o ex2
./ex2 &
vmstat 1
pid=$(ps | grep 'ex2' | grep -Eo '^[^ ]+')
kill $pid
exit

