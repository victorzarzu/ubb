#!/bin/bash

for user in $(awk -F: '{print $1}' /etc/passwd | head -200);do
  if [ "$user" != "root" ];then
    ips=$(last $user | head -n -2 | awk '{print $3}' | sort | uniq)
    if [ -n "$ips" ];then
      echo "$ips" > "19_output/$user"
    fi
  fi
done
