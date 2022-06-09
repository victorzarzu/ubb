#!/bin/bash

files=""
while [ 0 ];do
  all_found=1
  read -p "Fisier: " fisier
  if [ -f $fisier ];then
    files="$files $fisier"
    for cuv in $*;do
      if ! grep -E -q "\b$cuv\b" $files;then
        all_found=0
      fi   
    done 
    if [ $all_found -eq 1 ];then
        exit 0
    fi
  fi
done
