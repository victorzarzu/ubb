#!/bin/bash

while [ 0 ];do
  read -p "Fisier: " fisier
  if [ $fisier = "stop" ];then
    exit 0
  fi
  if [ -f $fisier ];then
    awk 'NR == 1 {print NF}' $fisier
  fi
done
