#!/bin/bash

while [ 0 ];do
  read -p "Name: " name

  if [ -f $name ];then
    exit 1
  fi
done
