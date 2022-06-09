#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director!"
fi

find $1 -type f | awk 'BEGIN{FS = "/"} {print $NF}' | sort -n  | uniq -c 
