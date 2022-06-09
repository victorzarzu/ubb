#!/bin/bash

if [ $# -eq 0 ] || ! [ -d $1 ];then
  echo "Un director!"
  exit 1
fi

for file in $(find $1 -type f -perm 755);do
  echo "Fisier: " $file
  read -p "da sau nu: " raspuns
  if [ $raspuns = "da" ];then
    chmod 744 $file
  fi
done
