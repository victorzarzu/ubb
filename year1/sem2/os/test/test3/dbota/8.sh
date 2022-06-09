#!/bin/bash

if [ $# -eq 0 ];then
  echo "Cel putin un argument!"
  exit 1
fi

for argument in $@;do
  if [ -f $argument ];then
    cat $argument | sort | uniq -c | sort -n -r | head -1
  fi
done | sort -n -r -k1,1
