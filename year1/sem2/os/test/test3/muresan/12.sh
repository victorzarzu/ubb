#!/bin/bash

if [ $# -eq 0 ] || ! [ -d $1 ];then
  echo Un director
  exit 1
fi

find $1 -type f | awk -F/ '{print $NF}' | sort | uniq -c
