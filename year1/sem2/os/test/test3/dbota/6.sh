#!/bin/bash

if [ $# -eq 0 ];then
  echo "Un argument"
fi

for argument in $@;do
  if [ -f $argument ];then
    chars=$(wc -c "$argument"| cut -d" " -f1)
    lines=$(wc -l "$argument"| cut -d" " -f1)
    name=$(echo $argument | awk -F/ '{print $NF}')
    echo $name $chars $lines
  elif [ -d $argument ];then
    files=$(ls -l $argument | wc -l)
    files=$((files - 1))
    echo $argument $files
  fi
done
