#!/bin/bash

if [ -f "exit_9.txt" ];then
  rm "exit_9.txt"
fi
touch "exit_9.txt"

for file in $@;do
  if [ -f $file ] && echo $file | grep -E -q ".c$";then
    #grep -o -E "^#include <.+>$" $file | sed -E "s/#include <(.+)>/\1/g"
    awk '$0 ~ /^#include <.+>$/{print $0}' $file | sed -E "s/#include <(.+)>/\1/g"
  fi 
done | sort | uniq >> "exit_9.txt"
