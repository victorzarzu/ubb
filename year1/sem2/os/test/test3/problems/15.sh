#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director!"
  exit 1
fi

for fisier in $(find $1 -type f);do
  if echo $fisier | grep -E -q ".c$";then
    rm $fisier
  elif file $fisier | grep -E -q "text";then
    echo $fisier | awk 'BEGIN{FS = "/"} {print $NF}'
  fi
done | sort
