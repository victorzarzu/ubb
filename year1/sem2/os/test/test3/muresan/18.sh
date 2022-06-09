#!/bin/bash

if [ $# -eq 0 ];then
  echo "Cel putin un argument!"
  exit 1
fi

found_all=false
file_string=""
while ! $found_all;do
  found_all=true
  read -p "File: " file

  if [ -f $file ];then
    file_string="$file $file_string"
    for argument in $@;do
      if ! grep -E -q "\<$argument\>" $file_string;then
        found_all=false
        break
      fi
    done
  else
    found_all=false
  fi
done
