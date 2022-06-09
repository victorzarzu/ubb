#!/bin/bash

if [ $# -eq 0 ];then
  echo "Un argument!"
  exit 1
fi

declare -A words

for word in $@;do
  words[$word]=0
done

while [ 0 ];do
  read -p "File: " file
  all_found=true

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
