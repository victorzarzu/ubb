#!/bin/bash

while [ 0 ];do
  read -p "Fisier: " fisier 
  if [ -f $fisier ] && file $fisier | grep -E -q "text";then
    head -1 $fisier | wc -w #awk '{print NF}'
  fi
done
