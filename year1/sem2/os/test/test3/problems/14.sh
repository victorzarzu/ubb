#!/bin/bash

if [ $# -eq 0 ];then
  echo "Cel putin un nume de proces!"
  exit 1
fi

while [ 0 ];do
  for process in $@;do
    for pid in $(pgrep "\<$process");do
      kill -9 $pid 
    done

    sleep 3
  done
done
