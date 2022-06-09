#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Neaparat director"
fi


for file in $(ls $1); do
  if [ -f "$1/$file" ];then
    nr=$(grep -E  "[0-9]{5,}" $1/$file | wc -c | awk '{print $1}')
    if [ $nr -gt 0 ];then
      echo $file
    fi
  fi
done
