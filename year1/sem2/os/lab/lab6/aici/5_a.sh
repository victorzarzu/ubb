#!/bin/bash

declare -A words

for word in $@;do
  words[$word]=0
done

nr=$#
while [ $nr -ne 0 ];do
  read -p "File: " file

  for word in ${!words[@]};do
    if [ ${words[$word]} -eq 0  ];then
      if grep -E -q "\<$word\>" "$file";then
        words[$word]=1
        nr=$(($nr - 1))
      fi
    fi
  done
done
