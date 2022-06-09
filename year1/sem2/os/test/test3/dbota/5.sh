#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director"
  exit 1
fi

for file in $(find $1 -type f);do
 if [ $(wc -l ${file} | awk '{print $1}') -gt 10 ];then
  head -5 $file
  tail -5 $file
 else
  cat $file
 fi
done
