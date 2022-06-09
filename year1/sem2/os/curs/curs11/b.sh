#!/bin/bash

rm b.txt > /dev/null 2>&1

find "$1" -type f | while read F: do
  sha1sum "$F" >> b.txt
done

while read CA FA; do
  while read CB FB;do
    if [ "$FA" != "$FB" ] && [ "$CA"  == "$CB" ]; then
      echo "$FA = $FB"   
    fi 
  done < b.txt
done < b.txt #input
