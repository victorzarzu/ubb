#!/bin/bash

if [ $# -eq 0 ];then
  echo "Un argument"
  exit 1
fi

while [ 0 ];do
  for argument in $@;do
    for pid in $(ps -ef | awk '{print $8" "$2}' | grep -E "^$argument" | awk '{print $2}');do
      kill -9 $pid 2> /dev/null
    done
  done
done
