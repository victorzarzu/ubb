#!/bin/bash

while [ 0 ];do
  read -p "Fisier: " fisier
  if [ -f $fisier ];then
    exit 0
  fi
done
