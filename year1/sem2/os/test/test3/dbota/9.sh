#!/bin/bash

if [ $# -ne 1 ] || ! [ -d $1 ];then
  echo "Un director!"
  exit 1
fi

for fisier in $(find $1 -type f);do
  nume=$(echo $fisier | awk -F"/" '{print $NF}')
  if [ $(echo $nume | wc -m) -lt 8 ];then
    echo $nume
    if file $fisier| grep -E -q "text";then
      head -10 $fisier
    fi

    echo ""
  fi 
done
