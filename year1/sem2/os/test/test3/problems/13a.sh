#!/bin/bash

for user in $(ps -ef | awk 'NR > 1{print $1}' | sort | uniq);do
  count=0
  sum=0
  for pid in $(ps -u $user | awk 'NR > 1 {print $1}');do
    sum=$((sum + pid))
    count=$((count + 1))
  done
  if [ $count -ne 0 ];then
    echo Media pid-urilor pentru $user este $((sum/count))
  fi
done
