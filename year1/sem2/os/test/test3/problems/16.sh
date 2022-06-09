#!/bin/bash

for file in $(find $1);do
  if [ -f $file ] && ls -l $file | grep -E -q "^-(.w.){3}";then
    echo $file
    chmod u-w,g-w,o-w $file
  fi
done
