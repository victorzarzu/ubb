#!/bin/bash

if [ $# -ne 1 ];then
  echo "Un director"
  exit 1
elif ! [ -d $1 ];then
  echo "Un director"
  exit 1
fi

for file in $(find $1);do
  var=$(ls -o $file | grep -E "^-.{7}w..*$file$" | awk '{print $1, $NF}')
  if [ -n "$var" ];then
    echo $var
    chmod o-w $file
    ls -o $file | grep -E "$file$" | awk '{print $1, $NF}'
  fi
done
