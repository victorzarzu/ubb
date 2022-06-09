#!/bin/bash

if [ $# -ne 1 ];then
  echo "Un director"
fi

if ! [ -d $1 ];then
  echo "Un director"
fi

for file in $(find $1 -type l);do
  if ! [ -e $file ];then
    echo $file
  fi
done
