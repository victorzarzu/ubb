#!/bin/bash

while [ 0 ];do
  for program in $@;do
    string=$(ps -ef | grep -E "^([^ ]+[ ]+){7}$program" | awk '{print $2}')

    for pid in $string; do
      kill -9 $pid
    done

    sleep 5
  done
done
