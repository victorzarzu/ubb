#!/bin/bash

if [ $# -eq 0 ] || [ $(($# % 3)) -ne 0 ];then
  echo "Multiplu de 3"
  exit 1
fi

while [ $# -ne 0 ];do
  if [ -f $1 ];then
    for line in $(sed -E "s/ /;/g" $1);do
      sum=0
      for cuv in $(echo $line | sed -E "s/;/\n/g");do
        if [ $cuv = $2 ];then
          sum=$((sum + 1))
        fi
      done
      if [ $sum -eq $3 ];then
        echo $line | sed -E "s/;/ /g"
      fi
    done
  fi

  shift 3
done
