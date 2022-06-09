#!/bin/bash

if [ $# -ne 1 ];then
  echo "Un fisier"
  exit 1
elif ! [ -f $1 ];then
  echo "Un fisier"
  exit 1
fi

string=""
for user in $(cat $1);do
  string="$string,$user@scs.ubbcluj.ro" 
done

string=$(echo $string | sed -E "s/^,//")
echo $string
