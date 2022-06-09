#!/bin/bash

if [ $# -eq 0 ] || ! [ -d $1 ];then
  echo "Un director"
  exit 1
fi

prev=$(ls -l "$1" | wc -l)
awk -v pre=$prev '{print 1}' 1.sh
while [ 0 ];do
  now=$(ls -l "$1" | wc -l)
  if [ $prev -ne $now ];then
    echo "Schimbare"
  fi

  prev=$now
  sleep 1
done
