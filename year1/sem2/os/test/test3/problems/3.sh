#!/bin/bash

for argument in $@;do
  if [ -f $argument ];then
    echo $argument is a file
  elif [ -d $argument ];then
    echo $argument is a directory
  elif echo $argument | grep -E -q "^[0-9]+$";then
    echo $argument is a a number
  else
    echo $argument is something
  fi
done
