#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director!"
  exit 1
fi

for file in $(find $1);do
  if [ -L $file ] && ! [ -e $file ];then
    echo $file
  fi
done
