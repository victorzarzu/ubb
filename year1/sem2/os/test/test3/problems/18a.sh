#!/bin/bash

if [ $# -eq 0 ];then
  echo "Cel putin un argument"
  exit 1
fi

declare -A words

for word in $@;do
  words[$word]=0
done

while [ 0 ];do
  all_found=true 
  read -p "File: " file
  if [ -f $file ];then
    for word in ${!words[@]};do
      if [ ${words[$word]} -eq 0 ];then
        if grep -E -q "\<$word\>" $file;then
          words[$word]=1      
        else
          all_found=false
        fi
      fi
    done
  else
    all_found=false
  fi

  if $all_found;then
    exit 0
  fi

done
