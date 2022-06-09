#!/bin/bash

for user in $(who | awk '{print $1}' | sort | uniq);do
  name=$(finger | grep -E -m 1 "^$user" | sed -E "s/^[^ ]+[ ]+(.*)([ ]+[*]?p.*)$/\1/g")
  #echo $name $user
  number=$(ps -u $user | awk 'NR > 1{print $0}' | wc -l)
  echo $username $name $number
done
