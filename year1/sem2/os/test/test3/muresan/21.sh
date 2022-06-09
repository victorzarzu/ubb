#!/bin/bash

director="./"

if [ $# -eq 1 ] && [ -d $1 ];then
  director="$1"
fi

for fisier in $(ls $director);do
  if [ -f $fisier ];then
    if file $fisier | grep -E -q "text";then
      perms=$(ls -l $fisier | sed -E "s/^-(.{9}).*$/\1/")
      dim=$(wc -c $fisier | awk '{print $1}')
      lines=$(cat $fisier | sort | uniq | wc -l | awk '{print $1}')

      echo $fisier $perms $dim $lines
    fi
  fi
done
