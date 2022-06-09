#!/bin/bash

if [ $# -eq 0 ];then
  echo "Un argument"
  exit 1
fi

for argument in $@;do
  if [ -f $argument ] && echo $argument | grep -E -q ".c$";then
    grep -E "^#include <.*>$" $argument | sed -E "s/^#include <(.*)>$/\1/g"
  fi
done | sort | uniq > output_9.txt
