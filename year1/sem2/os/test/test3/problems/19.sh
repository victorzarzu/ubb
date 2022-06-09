#!/bin/bash

folder="./results"

if [ -d $folder ];then
  rm -rf $folder
fi

mkdir $folder

users=$(cat /etc/passwd | cut -d: -f1)

for user in $users;do
  #ips=$(last $user | head -n -2 | awk '{print $3}' | sort | uniq)
  last $user | head -n -2 | awk '{print $3}' | sort | uniq > "$folder/$user"
  #if [ -n "$ips" ];then
  #  echo "$ips" > "$folder/$user"
  #fi
done
