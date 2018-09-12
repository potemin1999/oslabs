#! /bin/bash

i=1
echo "Starting test..."
echo ""
while [ $i -lt 10 ]
do
 ./ex1
 i=$[$i+1]
 echo ""
done
echo "Test done"

