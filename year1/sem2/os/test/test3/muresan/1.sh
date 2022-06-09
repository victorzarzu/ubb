#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director!"
  exit 1
fi

sum=0
for fisier in $(find $1 -type f -name *.c);do
  sum=$((sum + $(grep -E -c -v "^[ ]*$" $fisier))) 
done

echo $sum
