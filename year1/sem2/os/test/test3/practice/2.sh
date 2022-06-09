#!/bin/bash

if [ $# -ne 1 ];then
  echo "Un director"
fi

number=0
for file in $(find $1 -type f);do
  if echo $file | grep -E -q "\.c$";then
    if [ $(wc -l $file | awk '{print $1}') -gt 500 ];then
      echo $file
      number=$((number+1))
    fi
  fi
  if [ $number -eq 2 ];then
    exit 0
  fi
done
