#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director"
  exit 1
fi

sum=0
nr=0
for fisier in $(find $1 -type f);do
  if file "$fisier" | grep -E -q "text";then
    lines=$(wc -l $fisier | awk '{print $1}')
    sum=$((sum + lines))
    nr=$((nr + 1))
  fi
done

echo $((sum/nr))
