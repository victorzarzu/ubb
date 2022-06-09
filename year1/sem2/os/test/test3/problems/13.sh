#!/bin/bash

prev_user=""
count=0
sum=0
for user_pid in $(ps -ef | awk 'NR > 1 {print $1","$2}');do
  user=$(echo $user_pid | cut -d, -f1)
  pid=$(echo $user_pid | cut -d, -f2)
  if [ "$user" != "$prev_user" ];then
    if [ $count -gt 0 ];then
      echo "Medie pid-uri pentru: "$prev_user" este "$((sum/count))
    fi
    prev_user=$user
    sum=0
    count=0
  fi
  sum=$((sum+pid))
  count=$((count + 1))
done
