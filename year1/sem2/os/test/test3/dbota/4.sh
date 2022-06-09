#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director"
  exit 1
fi 

for fisier in $(find -type f);do
  if grep -E -q "\<[0-9]{5,}\>" $fisier;then
    echo $fisier 
  fi
done
