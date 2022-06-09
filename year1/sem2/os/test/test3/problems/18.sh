#!/bin/bash

if [ $# -eq 0 ];then
  echo "Cel putin un argument"
  exit 1
fi

all_files=""
all_found=false
while ! $all_found;do
  all_found=true 
  read -p "Fisier: " file
  if [ -f $file ];then
    all_files="$file $all_files"
    for argument in $@;do
      if ! grep -E -q "\<$argument\>" $all_files;then
        all_found=false
      fi
    done
  fi
done
