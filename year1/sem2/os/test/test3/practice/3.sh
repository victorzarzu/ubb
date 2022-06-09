#!/bin/bash

if [ $# -ne 1 ];then
  echo "Un director"
fi

if ! [ -d $1 ];then
  echo "Un director"
fi

for file in $(find $1 -name *.log);do
  mv $file "copy"
  cat "copy" | sort > $file
  rm "copy"
done
