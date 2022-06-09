#!/bin/bash

if [ $# -eq 0 ];then
  echo "Cel putin un fisier"
  exit 1
fi

for argument in $@;do
  if [ -f $argument ];then
    wc -c $argument
  fi
done | sort -n -r -k1,1
