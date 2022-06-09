#!/bin/bash

users=""
if [ $# -eq 0 ];then
  while [ 0 ];do
    ps -ef | awk 'NR > 1{print $1}' | sort | uniq -c | sort -n -r
    sleep 1
  done
else
  for user in $@;do
    users="-u $user $users" 
  done
fi

while [ 0 ];do
  ps -f $users | awk 'NR > 1{print $1}' | sort | uniq -c | sort -n -r
  sleep 1
done
