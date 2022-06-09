#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director"
  exit 1
fi

for file in $(find $1 -type f);do
  if file $file | grep -E -q "text";then
    size=$(wc -c $file | cut -d" " -f1)
    perms=$(ls -l $file | sed -E "s/^.(.{9}).*$/\1/g")
    uniqs=$(cat $file | sort | uniq | wc -l)
    echo $file $size $perms $uniqs
  fi
done
