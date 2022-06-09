#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director"
  exit 1
fi

declare -i sum
for file in $(ls $1);do
  if [ -f "$1/$file" ]; then
    size=$(wc -c "$1/$file" | cut -d" " -f1);
    sum=$(($sum + $size));
  fi
done

echo $sum
