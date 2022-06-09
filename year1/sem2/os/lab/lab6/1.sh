#!/bin/bash

if [ $# -ne 1 ] || !(echo $1 | grep -E -q "^[0-9]+$");then
  echo "Exact un argument numar"
fi

var=$1
declare -i X
for X in $(seq 1 $1); do
  touch "1_fis/file_${1}.txt"
  Y=$((X + 5))
  sed -E -n "${X},${Y}p" passwd.fake > "1_fis/file_${X}.txt"
done
