#!/bin/bash

for user in $(cat who.fake | awk '{print $1}' | sort | uniq);do
  name=$(finger | grep -E -m 1 "^$user" | sed -E "s/^[^ ]+[ ]+(.*)([ ]+[*]?p.*)$/\1/g")
  number=$(cat ps.fake | grep -E "^$user" | wc -l)
  echo $user $number
done
