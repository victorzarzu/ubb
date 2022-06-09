#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director"
  exit 1
fi

sum=0
for file in $(find $1 -type f);do
  octeti=$(wc -c $file | awk '{print $1}')
  sum=$((sum + octeti))
done

echo $sum
