#! /bin/bash

ls /usr/bin | grep "gcc" | sort -r > ./ex1.txt
echo "entries of /usr/bin contains <gcc> in name were detected and written to ./ex1.txt"
