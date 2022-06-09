#!/bin/bash

if [ $# -eq 0 ] || ! [ -d $1 ];then
  echo Un director
  exit 1
fi

for file in $(find $1 -type l);do
  if ! [ -e $file ];then
    echo $file
  fi
done
