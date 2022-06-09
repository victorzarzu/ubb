#!/bin/bash

for size_usage in $(cat df.fake | awk 'NR > 1{print $2","$(NF - 1)","$NF}');do
  space=$(echo $size_usage | cut -d, -f1 | sed -E "s/M$//")
  usage=$(echo $size_usage | cut -d, -f2 | sed -E "s/%$//")
  file=$(echo $size_usage | cut -d, -f3)
  if [ $space -lt 1024 ] || [ $usage -gt 80 ];then
    echo $file
  fi
done
