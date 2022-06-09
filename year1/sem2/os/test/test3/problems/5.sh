#!/bin/bash

for argument in $@;do
  if [ -f $argument ];then
    wc -c $argument
  fi
done | sort -n
