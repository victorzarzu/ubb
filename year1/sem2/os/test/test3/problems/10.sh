#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director!\n";
fi

prev=-1
while [ 0 ];do
  now=$(ls $1 | wc -l)
  if [ $prev -ne -1 ] && [ $prev -ne $now ];then
    echo "Schimbare"
  fi
  prev=$now
 
  sleep 1
done
