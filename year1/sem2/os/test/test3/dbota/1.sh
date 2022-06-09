#!/bin/bash

if [ $# -ne 1 ];then
   echo "Un numar"
fi

for x in $(seq $1);do
  touch "./1/file_$x.txt"
  y=$((x + 5))
  echo $x $y
  sed -n "${x},${y}p" "passwd.fake" > "./1/file_$x.txt"
done
