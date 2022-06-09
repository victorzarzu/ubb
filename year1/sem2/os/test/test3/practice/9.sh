#!/bin/bash

if [ $# -ne 1 ];then
  echo "Un director"
elif ! [ -d $1 ];then
  echo "Un director"
fi

for file1 in $(find $1);do
  ajuns=false
  for file2 in $(find $1);do
    if [ "$file1" = "$file2" ];then
      ajuns=true
    fi
    if $ajuns;then
      if test -f "$file1" && test -f "$file2" && test "$file1" != "$file2" ;then
        cod1=$(md5sum $file1 | awk '{print $1}')
        cod2=$(md5sum $file2 | awk '{print $1}')
        if [ "$cod1" = $cod2 ];then
          echo $file1 si $file2
        fi
      fi
    fi
  done
done
