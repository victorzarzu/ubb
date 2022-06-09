#!/bin/bash

if [ $# -ne 1 ] || ! [ -f $1 ];then
  echo "Un fisier"
  exit 1
fi

string=""
for user in $(cat $1);do
  string="$user@scs.ubbcluj.ro,$string"
done

string=$(echo $string | sed -E "s/,$//")

echo $string
