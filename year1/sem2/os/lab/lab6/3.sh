#!/bin/bash

for file in $(ls);do
  if [ -f $file ] && echo $file | grep -E -q "\.txt$";then
    echo "Fisier " $file 
    
    declare -i len
    len=$(wc -l $file | awk '{print $1}')
    
    if [ $len -le 10 ];then
      cat $file
    else
      head -5 $file
      tail -5 $file
    fi

    echo ""
  fi
done
