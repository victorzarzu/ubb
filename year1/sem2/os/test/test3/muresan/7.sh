#!/bin/bash

if [ -$# -eq 0 ] || [ $(($# % 2)) -eq 1 ];then
  echo "Numar par"
  exit 1
fi

while [ $# -ne 0 ];do
  if [ -f $1 ];then
    if [ $(grep -E -o "\<$2\>" $1 | wc -l) -ge 3 ];then
      echo da $1
    fi
  fi

  shift 2
done
