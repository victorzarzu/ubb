#!/bin/bash

while [ 0 ];do
  read file
  if [ "$file" == "stop" ];then
    exit 0
  elif [ -f "$file" ];then
    head -1 $file | wc -w
  fi
done
