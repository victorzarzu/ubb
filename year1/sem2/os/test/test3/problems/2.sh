#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director"
  exit 1
fi

number=0
for file in $(find -type f -name *.c);do
  lines=$(grep -E -v -c "^[ ]*$" $file)
  number=$((number + lines))
done

echo $number
