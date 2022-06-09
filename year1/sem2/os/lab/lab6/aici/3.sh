#!/bin/bash

string=""
if [ $# -eq 0 ];then
  while [ 0 ];do
    ps -ef | awk '$1 !~ "^UID$" {print $1}' | sort | uniq -c | sort -n -r
    sleep 1
  done
else
  for str in $@;do
    string="-u $str $string"
  done
fi

while [ 0 ];do
  ps -f ${string} | awk '$1 !~ "^UID$" {print $1}' | sort | uniq -c | sort -n -r
  sleep 1
done
