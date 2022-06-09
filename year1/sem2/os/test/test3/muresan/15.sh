#!/bin/bash

if [ $# -eq 0 ] || ! [ -d $1 ];then
  echo Un director
  exit 1
fi

for file in $(ls $1);do
  if echo $file | grep -E -q "\.c$";then
    rm "$1/$file"
  else
    echo $file
  fi
done | sort 
