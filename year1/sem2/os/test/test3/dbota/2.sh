#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un numar"
  exit 1
fi

for file in $(find $1 -type f);do
  cat $file | head -3
  echo "" 
done
