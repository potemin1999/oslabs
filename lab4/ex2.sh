#! /bin/bash

./ex2 &
#ensure all children were created
sleep 2
#dump and show important part
pstree
count=$( pstree | grep -Po "(?!.*ex2.sh)ex2" | grep -c "ex2")
echo "Running ex2 count : $count"
