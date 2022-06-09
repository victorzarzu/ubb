#!/bin/bash

if [ $# -eq 0 ];then
  echo "Minim un argument"
fi


for file in $@;do
  if [ -f $file ];then
    wc -l -m $file | awk '{print $3,$2,$1}'
  elif [ -d $file ];then
    number=0
    for fil in $(find $file);do
      if [ -f $fil ];then
        number=$(($number + 1))
      fi
    done
    echo $file, $number
  fi
done
