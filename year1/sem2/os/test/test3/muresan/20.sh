#!/bin/bash

if [ $# -eq 0 ];then
  while [ 0 ];do
    ps -ef | awk 'NR > 1{print $1}' | sort | uniq -c | sort -n -r -k1,1

    sleep 1
  done
fi

user_list=""

for user in $@;do
  user_list="-u $user $user_list"
done

while [ 0 ];do
    ps -f ${user_list} | awk 'NR > 1{print $1}' | sort | uniq -c | sort -n -r -k1,1

    sleep 1
  done
