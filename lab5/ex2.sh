#! /bin/bash

file="ex2.test"
lock_file="${file}.lock"
loop_count=10

write(){
  i=$(tail -n 1 ${file})
  new_i=$[${i}+1] ;
  echo "${new_i}" >> ${file}
}

run(){
 counter=0
 while [ ${counter} -lt ${loop_count} ]; do
  write
  counter=$[${counter}+1]
 done
}

run_syncronized(){
 counter=0
 full_lock_file="$(pwd)/${lock_file}"
 while [ ${counter} -lt ${loop_count} ]; do
   (
    flock 100
    echo "lock get by process $1"
    write
    flock -u 100
   )100>${full_lock_file}
   counter=$[${counter}+1]
 done
}

echo "0" > ${file}
if [ "$1" = "sync" ]; then
 echo "running with lock, writing to file ${file}, lock file ${lock_file}"
 (run_syncronized 1)&
 run_syncronized 2
else
 echo "running without lock, writing to file ${file}"
 run&
 run
fi

